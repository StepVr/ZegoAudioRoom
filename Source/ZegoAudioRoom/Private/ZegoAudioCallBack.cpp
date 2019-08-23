// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
#include "ZegoAudioCallBack.h"
#include "CoreMinimal.h"


void AudioRoomCallbackExc::OnLoginRoom(int errorCode, const char *pszRoomID)
{
	//if (errorCode == 0)
	//{
	//	UE_LOG(LogTemp,Log,TEXT("ZegoAudioRoom Login session Success"));
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Log, TEXT("ZegoAudioRoom Login session Fail : %d"), errorCode);
	//}
}

void AudioRoomCallbackExc::OnKickout(int reason, const char *pszRoomID)
{

}

void AudioRoomCallbackExc::OnDisconnect(int errorCode, const char *pszRoomID)
{

}

void AudioRoomCallbackExc::OnStreamUpdate(COMMON::ZegoStreamUpdateType type, const COMMON::ZegoStreamInfo& pStreamInfo, const char *pszRoomID)
{

}

void AudioRoomCallbackExc::OnUserUpdate(const COMMON::ZegoUserInfo *pUserInfo, unsigned int userCount, COMMON::ZegoUserUpdateType type)
{

}

void AudioRoomCallbackExc::OnStreamExtraInfoUpdated(COMMON::ZegoStreamInfo *pStreamInfo, unsigned int streamCount, const char *pszRoomID)
{

}

void AudioRoomCallbackExc::OnRecvCustomCommand(const char *pszUserId, const char *pszUserName, const char *pszContent, const char *pszRoomID)
{

}

void AudioRoomCallbackPlayerExc::OnPlayStateUpdate(int stateCode, const COMMON::ZegoStreamInfo& pStreamInfo)
{

}

void AudioRoomCallbackPublisherExc::OnPublishStateUpdate(int stateCode, const char *pszStreamID, const COMMON::ZegoPublishingStreamInfo& oStreamInfo)
{

}

void DeviceStateCallbackExc::OnAudioDeviceStateChanged(AV::AudioDeviceType deviceType, AV::DeviceInfo *deviceInfo, AV::DeviceState state)
{

}

void AudioEngineCallbackExc::OnAudioEngineStart()
{
	//throw std::logic_error("The method or operation is not implemented.");
}

void AudioEngineCallbackExc::OnAudioEngineStop()
{
	//throw std::logic_error("The method or operation is not implemented.");
}
