// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "AudioRoomCallback.h"
#include "AudioRoomCallback-IM.h"
#include "AudioRoomCallback-Player.h"
#include "AudioRoomCallback-Publisher.h"
#include "AVDefines.h"
#include "RoomDefines.h"

using namespace ZEGO;
class AudioRoomCallbackExc : public AUDIOROOM::IAudioRoomCallback
{
public:
	/**
	登录房间成功回调
	@param errorCode 错误码，0 表示无错误
	@param pszRoomID 房间 ID
	*/
	virtual void OnLoginRoom(int errorCode, const char *pszRoomID);
	virtual void OnKickout(int reason, const char *pszRoomID);
	virtual void OnDisconnect(int errorCode, const char *pszRoomID);
	virtual void OnStreamUpdate(COMMON::ZegoStreamUpdateType type, const COMMON::ZegoStreamInfo& pStreamInfo, const char *pszRoomID);
	virtual void OnUserUpdate(const COMMON::ZegoUserInfo *pUserInfo, unsigned int userCount, COMMON::ZegoUserUpdateType type);
	virtual void OnStreamExtraInfoUpdated(COMMON::ZegoStreamInfo *pStreamInfo, unsigned int streamCount, const char *pszRoomID);
	virtual void OnRecvCustomCommand(const char *pszUserId, const char *pszUserName, const char *pszContent, const char *pszRoomID);
protected:
private:
};
class AudioEngineCallbackExc : public AUDIOROOM::IAudioEngineCallback
{

public:
	virtual void OnAudioEngineStart() override;


	virtual void OnAudioEngineStop() override;

};



class AudioRoomCallbackIMExc : public AUDIOROOM::IAudioIMCallback
{
public:
protected:
private:
};

class AudioRoomCallbackPlayerExc : public AUDIOROOM::IAudioLivePlayerCallback
{
public:
	virtual void OnPlayStateUpdate(int stateCode, const COMMON::ZegoStreamInfo& pStreamInfo);
protected:
private:
};

class AudioRoomCallbackPublisherExc : public AUDIOROOM::IAudioLivePublisherCallback
{
public:
	virtual void OnPublishStateUpdate(int stateCode, const char *pszStreamID, const COMMON::ZegoPublishingStreamInfo& oStreamInfo);
protected:
private:
};

class DeviceStateCallbackExc : public AV::IZegoDeviceStateCallback
{
public:
	virtual void OnAudioDeviceStateChanged(AV::AudioDeviceType deviceType, AV::DeviceInfo *deviceInfo, AV::DeviceState state);
protected:
private:
};

