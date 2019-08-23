// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ZegoAudioRoomLibrary.generated.h"


UCLASS()
class ZEGOAUDIOROOM_API UZegoAudioRoomLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void Audio_JoinRoom(FString RoomName);

	UFUNCTION(BlueprintCallable)
	static void Audio_SetUserInfo(FString ID, FString Name);
};
