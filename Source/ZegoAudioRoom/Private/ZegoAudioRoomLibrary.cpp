// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#include "ZegoAudioRoomLibrary.h"
#include "ZegoAudioBase.h"

FAudioRoomBase GAudioRoomBase;
void UZegoAudioRoomLibrary::Audio_JoinRoom(FString RoomName)
{
	GAudioRoomBase.JoinRoom(RoomName);
}

void UZegoAudioRoomLibrary::Audio_SetUserInfo(FString ID, FString Name)
{
	GAudioRoomBase.SetUserInfo(ID,Name);
}
