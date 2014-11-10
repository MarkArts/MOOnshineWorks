// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include <string>
#include "Networking.h"
#include "Messages.h"
#include "Socket.h"


ASocket::ASocket(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void ASocket::start(FString name, FString ip, int32 port)
{
	if (!StartUDPReceiver(name, ip, port))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "UDP Socket Listener Created!");
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "UDP Socket Listener Created! Yay!");
}

//Rama's Start UDP Receiver
bool ASocket::StartUDPReceiver(
	const FString& YourChosenSocketName,
	const FString& TheIP,
	const int32 ThePort
	){
	//Rama's CreateUDPConnectionListener
	ListenerSocket = CreateUDPConnectionListener(YourChosenSocketName, TheIP, ThePort);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "CreateUDPConnectionListener called, socket done returning");
	//Not created?
	if (!ListenerSocket)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("StartUDPReceiver>> Listen socket could not be created! ~> %s %d"), *TheIP, ThePort));
		return false;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("StartUDPReceiver>> Listen socket was created ~> %s %d"), *TheIP, ThePort));
	//Start the Listener! //thread this eventually
	GetWorldTimerManager().SetTimer(this, &ASocket::UDPConnectionMaker, 2, true);

	return true;
}
//Format IP String as Number Parts
bool ASocket::FormatIP4ToNumber(const FString& TheIP, uint8(&Out)[4])
{
	//IP Formatting
	TheIP.Replace(TEXT(" "), TEXT(""));

	//IP 4 Parts
	//String Parts
	TArray<FString> Parts;
	TheIP.ParseIntoArray(&Parts, TEXT("."), true);
	if (Parts.Num() != 4)
		return false;

	//String to Number Parts
	for (int32 i = 0; i < 4; ++i)
	{
		Out[i] = FCString::Atoi(*Parts[i]);
	}

	return true;
}
//Rama's Create UDP Connection Listener
FSocket* ASocket::CreateUDPConnectionListener(const FString& YourChosenSocketName, const FString& TheIP, const int32 ThePort, const int32 ReceiveBufferSize)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "CreateUDPConnectionListener called");

	uint8 IP4Nums[4];
	if (!FormatIP4ToNumber(TheIP, IP4Nums))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Invalid IP! Expecting 4 parts separated by .");
		return false;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	//Create Socket
	FIPv4Endpoint Endpoint(FIPv4Address(IP4Nums[0], IP4Nums[1], IP4Nums[2], IP4Nums[3]), ThePort);
	Destination = Endpoint;
	FSocket* ListenSocket = FUdpSocketBuilder(*YourChosenSocketName)
		//PrPleGoo's maker code
		.AsNonBlocking()
		.AsReusable()
		.Build();

	//Set Buffer Size
	int32 NewSize = 0;
	ListenSocket->SetReceiveBufferSize(ReceiveBufferSize, NewSize);

	//Done!
	return ListenSocket;
}

//PrPleGoo's Connection maker
void ASocket::UDPConnectionMaker()
{
	//if there is no ListenerSocket, stop this function
	if (!ListenerSocket) return;
	//if there already is a ConnectionSocket, stop this function
	if (ConnectionSocket) return;
	//Remote address
	//TSharedRef<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	TSharedRef<FInternetAddr> RemoteAddress = Destination.ToInternetAddr();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Attempting connection...");
	if (ListenerSocket->Connect(*RemoteAddress))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Connection attempt succes?");
		if (ConnectionSocket)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Already has a connection, destroying");
			ConnectionSocket->Close();
			ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectionSocket);
		}
		//New Connection receive!
		//ConnectionSocket = ListenerSocket->Accept(*RemoteAddress, TEXT("PrPlegoo UDP Received Socket Connection"));
		ConnectionSocket = ListenerSocket;
		if (ConnectionSocket != NULL)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Connection attempt succes? YUP!");
			//Global cache of current Remote Address
			RemoteAddressForConnection = FIPv4Endpoint(RemoteAddress);
			//SendString("Message received");
			//UE_LOG "Accepted Connection! WOOOHOOOO!!!";
			//can thread this too
			GetWorldTimerManager().SetTimer(this,
			&ASocket::UDPSocketListener, 0.01, true);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Connection attempt succes? Nope :<");
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Connection attempt fail!");
	}
}

//Rama's String From Binary Array
//This function requires 
//		#include <string>
FString ASocket::StringFromBinaryArray(const TArray<uint8>& BinaryArray)
{
	//Create a string from a byte array!
	std::string cstr(reinterpret_cast<const char*>(BinaryArray.GetData()), BinaryArray.Num());
	return FString(cstr.c_str());
}

//Rama's UDP Socket Listener
void ASocket::UDPSocketListener()
{
	//~~~~~~~~~~~~~
	if (!ConnectionSocket) return;
	//~~~~~~~~~~~~~


	//Binary Array!
	TArray<uint8> ReceivedData;

	uint32 Size;
	while (ConnectionSocket->HasPendingData(Size))
	{
		ReceivedData.Init(FMath::Min(Size, 65507u));

		int32 Read = 0;
		ConnectionSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Data Read! %d"), ReceivedData.Num()));
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (ReceivedData.Num() <= 0)
	{
		//No Data Received
		return;
	}
	ParseMessage(ReceivedData);
}

void ASocket::SendString(FString msg)
{
//	MDString Message = MDString();
//	Message.Type = MessageType::TMDString;
//	Message.Name = TEXT("TestName");
//	Message.TestInt = 13;
	//Message.TestString = (uint8*)TCHAR_TO_UTF8(msg.GetCharArray().GetData());
//	Message.String = msg.GetCharArray().GetData();
	//Message.Int = 12;

	//Send(Message);

	//msg = TEXT("dummy text");
	//TCHAR *msgChar = msg.GetCharArray().GetData();
	//int32 size = FCString::Strlen(msgChar);
	//int32 sent = 0;
	//ConnectionSocket->Send((uint8*)TCHAR_TO_UTF8(msgChar), size, sent);
}

bool ASocket::ParseMessage(TArray<uint8> ReceivedData){

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Data Bytes Read ~> %d"), ReceivedData.Num()));

	MBase* Message = reinterpret_cast<MBase*>(ReceivedData.GetData());

	switch ((*Message).Type){
		case MessageType::String:
		{
			//MString* DString = reinterpret_cast<MString*>(ReceivedData.GetData());
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("recived string"));
			break;
		}
		case MessageType::Event:
		{
			MEvent* DEvent = reinterpret_cast<MEvent*>(ReceivedData.GetData());
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("event: %d"), (*DEvent).id));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("x: %d"), (*DEvent).x));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("y: %d"), (*DEvent).y));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("powerLevel: %d"), (*DEvent).powerLevel));
			break;
		}
		default: break;
	}

	return true;
}

void ASocket::SendMEvent(int id, int x, int y, int powerLevel)
{
	MEvent msg = MEvent();
	msg.Type = MessageType::Event;
	msg.id = id;
	msg.x = x;
	msg.y = y;
	msg.powerLevel = powerLevel;

	int send;
	ConnectionSocket->Send((uint8 *)&msg, sizeof(MEvent), send);
}