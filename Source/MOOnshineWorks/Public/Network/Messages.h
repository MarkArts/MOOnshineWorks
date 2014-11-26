// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <string>
/**
 * 
 */

class MBase{
public:
	int Type;
};

// Message Enum
enum MessageType{
	RConnection = 1,
	AConnection,
	String,
	Event
};

// request connection
class MRConnection : public MBase
{
public:
	int RequestId;
};

// connection accepted
class MAConnection : public MBase
{
public:
	int AcceptedId;
};

// string
class MString : public MBase
{
public:
	FString String;
};

class MEvent : public MBase
{
public:
	int id;
	int x;
	int y;
	int powerLevel;
};