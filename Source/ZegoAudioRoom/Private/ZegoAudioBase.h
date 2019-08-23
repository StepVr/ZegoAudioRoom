// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

class FAudioRoomBase
{
public:
	~FAudioRoomBase();

	void JoinRoom(FString& RoomName);
	void SetUserInfo(FString ID, FString Name);

protected:
	bool InitAVSDK();
	bool LoadDLL();
	void UnLoadDLL();

private:
	FString UserID;
	FString UserName;

	void* DLLHandle = nullptr;
	bool IsInitSDK = false;
	bool IsInitSDKSuccess = false;
};