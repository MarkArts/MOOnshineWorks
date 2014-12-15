// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "DoorKey.h"
#include "KeyHolder.h"

KeyHolder::KeyHolder()
{
	KeyPack.Add(EDoorKey::Type::None);
}

KeyHolder::~KeyHolder()
{
}

bool KeyHolder::HasKey(EDoorKey::Type key) {
	for (auto Itr(KeyPack.CreateIterator()); Itr; Itr++) {
		if (KeyPack[Itr.GetIndex()] == key) {
			return true;
		}
	}
	return false;
}

void KeyHolder::AddKey(EDoorKey::Type key) {
	if (!KeyPack.Contains(key)) {
		KeyPack.Add(key);
	}
}
