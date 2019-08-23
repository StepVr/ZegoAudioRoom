// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
#include "ZegoAudioBase.h"
#include "ZegoAudioCallBack.h"

#include "AudioRoom.h"
#include "AudioRoom-Publisher.h"
#include "AudioRoom-Player.h"
#include "AudioRoom-IM.h"

#include "Engine.h"



using namespace ZEGO;

static unsigned int g_dwAppID_Udp = 4086657532;
static unsigned char g_bufSignKey_Udp[] =
{
	0xe2,0x15,0x26,0x74,0xf7,
	0x10,0x1b,0xe8,0x0a,0x32,
	0x51,0xed,0xb6,0xa6,0xc4,
	0x33,0x29,0xbd,0xc0,0x7b,
	0x30,0xcc,0x9c,0x1f,0x64,
	0x18,0x13,0xa0,0x1e,0x8a,
	0x9e,0x1d
};

FAudioRoomBase::~FAudioRoomBase()
{
	UnLoadDLL();
}

bool FAudioRoomBase::InitAVSDK()
{
	bool Success = false;
	FString Message;

	do 
	{
		if (IsInitSDK)
		{
			Success = true;
			break;
		}

		if (!LoadDLL())
		{
			Message = TEXT("Load Dll Error");
			break;
		}

		//初始化SDK
		FString LogDir = FPaths::ProjectSavedDir() + "/Logs";
		if (!AUDIOROOM::SetLogDir(TCHAR_TO_ANSI(*LogDir)))
		{
			Message = TEXT("SetLogDir Error");
			break;
		}

		AUDIOROOM::SetUseTestEnv(true);
		AUDIOROOM::SetVerbose(true);

		FString CUserName = FPlatformProcess::ComputerName();
		FString CUserID = FString::Printf(TEXT("%u"), GetTypeHash(CUserName));
		if (!AUDIOROOM::SetUser(TCHAR_TO_ANSI(*CUserID), TCHAR_TO_ANSI(*CUserID)))
		//if (!ZEGO::AUDIOROOM::SetUser("123", "456"))
		//if (!ZEGO::AUDIOROOM::SetUser(TCHAR_TO_ANSI(*UserID), TCHAR_TO_ANSI(*UserName)))
		{
			Message = TEXT("SetUser Error");
			break;
		}

		auto CallBack1 = new AudioRoomCallbackPublisherExc();
		if (!ZEGO::AUDIOROOM::SetAudioLivePublisherCallback(CallBack1))
		{
			Message = TEXT("SetAudioLivePublisherCallback Error");
			break;
		}
		auto CallBack2 = new AudioRoomCallbackPlayerExc();
		if (!ZEGO::AUDIOROOM::SetAudioLivePlayerCallback(CallBack2))
		{
			Message = TEXT("SetAudioLivePlayerCallback Error");
			break;
		}
		auto CallBack3 = new AudioRoomCallbackExc();
		if (!ZEGO::AUDIOROOM::SetAudioRoomCallback(CallBack3))
		{
			Message = TEXT("SetAudioRoomCallback Error");
			break;
		}
		auto CallBack4 = new AudioRoomCallbackIMExc();
		if (!ZEGO::AUDIOROOM::SetAudioIMCallback(CallBack4))
		{
			Message = TEXT("SetAudioIMCallback Error");
			break;
		}
		auto CallBack5 = new DeviceStateCallbackExc();
		ZEGO::AUDIOROOM::SetAudioDeviceStateCallback(CallBack5);

		auto CallBack6 = new AudioEngineCallbackExc();
		ZEGO::AUDIOROOM::SetAudioEngineCallback(CallBack6);

		//unsigned char SignKey[33] = "0xe2,0x15,0x26,0x74,0xf7,0x10,0x1b,0xe8,0x0a,0x32,0x51,0xed,0xb6,0xa6,0xc4,0x33,0x29,0xbd,0xc0,0x7b,0x30,0xcc,0x9c,0x1f,0x64,0x18,0x13,0xa0,0x1e,0x8a,0x9e,0x1d";
		if (!ZEGO::AUDIOROOM::InitSDK(g_dwAppID_Udp, g_bufSignKey_Udp, 32))
		{
			Message = TEXT("InitSDK Error");
			break;
		}

		//为了调用OnUserUpdate
		//AUDIOROOM::SetUserStateUpdate(false);
		//AUDIOROOM::SetLatencyMode(AV::ZEGO_LATENCY_MODE_LOW3);
		//AUDIOROOM::EnableDTX(true);

		Success = true;
		IsInitSDKSuccess = true;
	} while (0);

	IsInitSDK = true;

	if (Success)
	{
		UE_LOG(LogTemp, Log, TEXT("ZegoAudioRoom Satrt Success"));
	}
	else
	{
		UnLoadDLL();
		UE_LOG(LogTemp, Log, TEXT("ZegoAudioRoom %s"), *Message);
	}
	return Success;
}

void FAudioRoomBase::JoinRoom(FString& RoomName)
{
	InitAVSDK();

	if (IsInitSDKSuccess)
	{
		//ZEGO::AUDIOROOM::LogoutRoom();
		ZEGO::AUDIOROOM::LoginRoom(TCHAR_TO_ANSI(*RoomName));
	}
}

void FAudioRoomBase::SetUserInfo(FString ID, FString Name)
{
	UserID = ID;
	UserName = Name;
}

bool FAudioRoomBase::LoadDLL()
{
	TArray<FString> DllPaths;
	FString Platform = "x64";
	DllPaths.Add(FPaths::ProjectPluginsDir() + TEXT("ZegoAudioRoom/ThirdParty/lib/") + Platform);
	DllPaths.Add(FPaths::EnginePluginsDir() + TEXT("ZegoAudioRoom/ThirdParty/lib/") + Platform);
	DllPaths.Add(FPaths::EnginePluginsDir() + TEXT("Runtime/ZegoAudioRoom/ThirdParty/lib/") + Platform);

	for (int32 i = 0; i < DllPaths.Num(); i++)
	{
		FPlatformProcess::PushDllDirectory(*DllPaths[i]);
		DLLHandle = FPlatformProcess::GetDllHandle(*(DllPaths[i] + "/ZegoAudioRoom.dll"));
		FPlatformProcess::PopDllDirectory(*DllPaths[i]);
		if (DLLHandle != nullptr)
		{
			break;
		}
	}

	return DLLHandle != nullptr;
}

void FAudioRoomBase::UnLoadDLL()
{
	if (DLLHandle)
	{
		FPlatformProcess::FreeDllHandle(DLLHandle);
		DLLHandle = nullptr;
	}

	if (IsInitSDK)
	{
		//AUDIOROOM::SetAudioRoomCallback(nullptr);
		//AUDIOROOM::SetAudioLivePublisherCallback(nullptr);
		//AUDIOROOM::SetAudioLivePlayerCallback(nullptr);
		//AUDIOROOM::SetAudioDeviceStateCallback(nullptr);
		//AUDIOROOM::SetAudioEngineCallback(nullptr);
		//AUDIOROOM::SetAudioLiveEventCallback(nullptr);
		//AUDIOROOM::SetAudioRecordCallback(nullptr);

		//AUDIOROOM::UnInitSDK();

		IsInitSDK = false;
	}
}
