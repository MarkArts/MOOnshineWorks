// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include <string>
#include "Networking.h"
#include "Socket.h"


ASocket::ASocket(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void ASocket::start(FString name, FString ip, int32 port)
{
	//IP = 127.0.0.1, Port = 8890 for my Python test case
	if (!StartTCPReceiver(name, ip, port))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "TCP Socket Listener Created!");
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "TCP Socket Listener Created! Yay!");
}

//Rama's Start TCP Receiver
bool ASocket::StartTCPReceiver(
	const FString& YourChosenSocketName,
	const FString& TheIP,
	const int32 ThePort
	){
	//Rama's CreateTCPConnectionListener
	ListenerSocket = CreateTCPConnectionListener(YourChosenSocketName, TheIP, ThePort);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "CreateTCPConnectionListener called, socket done returning");
	//Not created?
	if (!ListenerSocket)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("StartTCPReceiver>> Listen socket could not be created! ~> %s %d"), *TheIP, ThePort));
		return false;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("StartTCPReceiver>> Listen socket was created ~> %s %d"), *TheIP, ThePort));
	//Start the Listener! //thread this eventually
	GetWorldTimerManager().SetTimer(this, &ASocket::TCPConnectionMaker, 2, true);

	return true;
}
//Format IP String as Number Parts
bool ASocket::FormatIP4ToNumber(const FString& TheIP, uint8(&Out)[4])
{
	//IP Formatting
	TheIP.Replace(TEXT(" "), TEXT(""));

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//						   IP 4 Parts

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
//Rama's Create TCP Connection Listener
FSocket* ASocket::CreateTCPConnectionListener(const FString& YourChosenSocketName, const FString& TheIP, const int32 ThePort, const int32 ReceiveBufferSize)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "CreateTCPConnectionListener called");

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
	FSocket* ListenSocket = FTcpSocketBuilder(*YourChosenSocketName)
		//PrPleGoo's maker code
		.AsNonBlocking()
		.AsReusable()
		.Build();
	//rama's listener code
		//.AsReusable()
		//.BoundToEndpoint(Endpoint)
		//.Listening(8);
	
	//Set Buffer Size
	int32 NewSize = 0;
	ListenSocket->SetReceiveBufferSize(ReceiveBufferSize, NewSize);

	//Done!
	return ListenSocket;
}

//PrPleGoo's Connection maker
void ASocket::TCPConnectionMaker()
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
		//ConnectionSocket = ListenerSocket->Accept(*RemoteAddress, TEXT("PrPlegooTCP Received Socket Connection"));
		ConnectionSocket = ListenerSocket;
		if (ConnectionSocket != NULL)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Connection attempt succes? YUP!");
			//Global cache of current Remote Address
			RemoteAddressForConnection = FIPv4Endpoint(RemoteAddress);
			FString msg = TEXT("Message received\n");
			TCHAR *msgChar = msg.GetCharArray().GetData();
			int32 size = FCString::Strlen(msgChar);
			int32 sent = 0;
			ConnectionSocket->Send((uint8*)TCHAR_TO_UTF8(msgChar), size, sent);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Sent after send: %d"), sent));
			//UE_LOG "Accepted Connection! WOOOHOOOO!!!";
			//can thread this too
			GetWorldTimerManager().SetTimer(this,
			&ASocket::TCPSocketListener, 0.01, true);
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
//Rama's TCP Connection Listener
void ASocket::TCPConnectionListener()
{
	//~~~~~~~~~~~~~
	if (!ListenerSocket) return;
	//~~~~~~~~~~~~~

	//Remote address
	TSharedRef<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool Pending;

	// handle incoming connections
	if (ListenerSocket->HasPendingConnection(Pending) && Pending)
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//Already have a Connection? destroy previous
		if (ConnectionSocket)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Already has a connection");
			ConnectionSocket->Close();
			ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectionSocket);
		}
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


		//New Connection receive!
		ConnectionSocket = ListenerSocket->Accept(*RemoteAddress, TEXT("RamaTCP Received Socket Connection"));

		if (ConnectionSocket != NULL)
		{
			//Global cache of current Remote Address
			RemoteAddressForConnection = FIPv4Endpoint(RemoteAddress);

			//UE_LOG "Accepted Connection! WOOOHOOOO!!!";
			//can thread this too
			GetWorldTimerManager().SetTimer(this,
				&ASocket::TCPSocketListener, 0.01, true);
		}
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

//Rama's TCP Socket Listener
void ASocket::TCPSocketListener()
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
		FString msg = TEXT("Message received\n");
		TCHAR *msgChar = msg.GetCharArray().GetData();
		int32 size = FCString::Strlen(msgChar);
		int32 sent = 0;
		ConnectionSocket->Send((uint8*)TCHAR_TO_UTF8(msgChar), size, sent);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Sent after send: %d"), sent));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Data Read! %d"), ReceivedData.Num()));
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (ReceivedData.Num() <= 0)
	{
		//No Data Received
		return;
	}

	//VShow("Total Data read!", ReceivedData.Num());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Data Bytes Read ~> %d"), ReceivedData.Num()));


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//						Rama's String From Binary Array
	const FString ReceivedUE4String = StringFromBinaryArray(ReceivedData);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	//VShow("As String!!!!! ~>", ReceivedUE4String);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("As String Data ~> %s"), *ReceivedUE4String));
}

