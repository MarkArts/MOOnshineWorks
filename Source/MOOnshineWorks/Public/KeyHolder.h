// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DoorKey.h"

/**
 * 
 */
class MOONSHINEWORKS_API KeyHolder
{
public:
	KeyHolder();
	~KeyHolder();

	TArray<EDoorKey::Type> KeyPack;

	bool HasKey(EDoorKey::Type key);

	void AddKey(EDoorKey::Type key);
};
