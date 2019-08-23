// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ZegoAudioRoom.h"
#include "ZegoAudioRoomLibrary.h"


#define LOCTEXT_NAMESPACE "FZegoAudioRoomModule"

void FZegoAudioRoomModule::StartupModule()
{
}

void FZegoAudioRoomModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FZegoAudioRoomModule, ZegoAudioRoom)