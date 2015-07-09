/*
**Copyright (c) 2013 Calvin Cheung. All Rights Reserved.
**
**Use of this source code is governed by a BSD-style license.
**
**This is a simple wrapper for WebRTC. I used it in the Video Conference project.
**
**URL:https://github.com/calvingit/WebRTC_Wrapper/
**
**File: LoganVoiceEngineImpl.h
**
**Author: Calvin Cheung, Chinna.
**
**Update Date: 2013-5-21
*/


#ifndef __LOGAN_VOICE_ENGINE_IMPL_H__
#define __LOGAN_VOICE_ENGINE_IMPL_H__


#include <cstdlib>
#include <vector>
#include <process.h>
// #include <wtypes.h>

#include "webrtc_wrapper.h"
#include "pthread.h"
#include "common_types.h"
#include "voe_errors.h"
#include "voe_base.h"
#include "voe_codec.h"
#include "voe_volume_control.h"
#include "voe_audio_processing.h"
#include "voe_file.h"
#include "voe_hardware.h"
#include "voe_network.h"
#include "engine_configurations.h"
#include "voe_neteq_stats.h"
#include "voe_external_media.h"
#include "voe_rtp_rtcp.h"
#include "voe_video_sync.h"
#include "channel_transport.h"
#include "CUDP.h"

using namespace webrtc;
using namespace test;
/*using namespace rtc;*/


const int VOE_API_MAXCHANNELS = 8;
const int RTP_PAYLOAD_NAME_LEN = 32;
const int DEVICE_MAX_LEN = 128;

class LoganTransport :public Transport
{
public:
	virtual int SendPacket(int channel, const void *data, int len);
	virtual int SendRTCPPacket(int channel, const void *data, int len);
	virtual ~LoganTransport() {}
	LoganTransport() {}
};
int LoganTransport::SendPacket(int channel, const void *data, int len)
{
	return 0;
}
int LoganTransport::SendRTCPPacket(int channel, const void *data, int len)
{
	return 0;
}

class LoganRTCPObserver:public VoERTCPObserver
{
public:
	virtual void OnApplicationDataReceived(
		int channel, unsigned char subType,
		unsigned int name, const unsigned char* data,
		unsigned short dataLengthInBytes);
	virtual ~LoganRTCPObserver() {}
	LoganRTCPObserver() {}
};
void LoganRTCPObserver::OnApplicationDataReceived(int channel, unsigned char subType, unsigned int name,
																										const unsigned char* data, unsigned short dataLengthInBytes)
{
	return;
}
/*
class LoganRevThread
{
public:
	~LoganRevThread();
	LoganRevThread(int Channnal, VoEBase *vBasePtr);
	void StartThread();
	void run();
	static unsigned __stdcall RevThread(LPVOID pContent);
private:
	int _iChannal;
	VoEBase *_basePtr;
	CUDP _udpSev;
public:
	HANDLE  _hRevThread;
	HANDLE _hStopThreadEvent;
};
LoganRevThread::LoganRevThread(int Channal, VoEBase *vBasePtr) :_iChannal(Channal), _basePtr(vBasePtr), _hRevThread(NULL), _hStopThreadEvent(NULL)
{
	BOOL bRet = _udpSev.Config(1222, "", FALSE);
	if ( !bRet ) printf("_udpSev.Config Failed!!!\n");
	
	_hStopThreadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if ( NULL == _hStopThreadEvent )
	{
		printf("CreateEvent Failed!!!\n");
	}
}
LoganRevThread::~LoganRevThread()
{
	BOOL bRet = SetEvent(_hStopThreadEvent);
	DWORD dwRet = WaitForSingleObject(_hRevThread, INFINITE);
	return;
}
unsigned __stdcall LoganRevThread::RevThread(LPVOID pContent)
{
	LoganRevThread *pCont = (LoganRevThread *)pContent;
	for (;;)
	{
		DWORD dwRet = WaitForSingleObject(pCont->_hStopThreadEvent, 1);
		if (WAIT_OBJECT_0 == dwRet)
		{
			break;
		}
		pCont->run();
	}
	return 0;
}
void LoganRevThread::StartThread()
{
	_hRevThread = (HANDLE)_beginthreadex(NULL, 0, RevThread, this, 0, NULL);
	if (NULL == _hRevThread)
	{
		printf("_beginthreadex Failed!!!\n");
	}
}

void LoganRevThread::run()
{
	unsigned char *data = NULL;
	int buffLen = 0;
	BOOL bFlag = _udpSev.RecvUdp(data, buffLen);
	if (_basePtr)
	{
		_basePtr->ReceivedPayloadData(_iChannal, data, buffLen);
		free(data);
	}
}

class LoganSendData :public VoiceSendData
{
public:
	virtual void CallbackGetVoiceData(const uint8_t*  payloadData, uint16_t  payloadSize);
	virtual ~LoganSendData(){}
	LoganSendData(char *pAddr);
private:
	CUDP _udpSend;
};
LoganSendData::LoganSendData(char *pAddr)
{
	BOOL bRet = _udpSend.Config(1222, pAddr);
	if (!bRet) printf("_udpSend.Config Failed!!!\n");
}
void LoganSendData::CallbackGetVoiceData(const uint8_t* payloadData, uint16_t payloadSize)
{
	BOOL bRet = _udpSend.SendUdp((unsigned char *)payloadData, payloadSize);
	Sleep(1);
	if (!bRet) printf("_udpSend.SendUdp Failed!!!\n");
	return;
}
*/
class LoganInStream:public InStream
{
public:
    virtual int Read(void *buf,int len);
    LoganReadStreamCallBack pRead;
    virtual ~LoganInStream() {}
    LoganInStream() {} 
};

int LoganInStream::Read(void *buf,int len)
{
    return pRead(buf, len);
}

class LoganOutStream:public OutStream
{
public:
    virtual bool Write(const void *buf,int len);
    LoganWriteStreamCallBack pWrite;

    virtual ~LoganOutStream() {}
    LoganOutStream() {}
};

bool LoganOutStream::Write(const void *buf,int len)
{
    return pWrite(buf, len);
}

class VoiceChanTrans
{
public:
    VoiceChanTrans():channel(-1),pTrans(NULL){}
    void SetEmpty()
    {
        channel = -1;
        pTrans = NULL;
    }
    int channel;
    VoiceChannelTransport * pTrans;
};

class LoganVoiceEngineImpl:public LoganVoiceEngine
{
private:
    VoiceEngine* m_voe;
    VoEBase* base;
    VoECodec* codec;
    VoEVolumeControl* volume;
    VoEAudioProcessing* apm;
    VoENetwork *netw;
    VoEFile *file;
    VoEHardware *hardware;
    VoERTP_RTCP* rtp_rtcp;
    VoEExternalMedia* xmedia;
    VoENetEqStats* neteqst;
    VoEVideoSync* vsync;
//    VoEEncryption* encrypt;

    LoganInStream _inStream;
    LoganOutStream _outStream;
	LoganTransport _transPort;
//	LoganSendData _sendData;
	LoganRTCPObserver _rtcpObserver;

    std::vector<VoiceChanTrans> vec_vct;

public:

    LoganVoiceEngineImpl();
    virtual ~LoganVoiceEngineImpl();

    virtual int LoganVoe_Init();
    virtual void LoganVoe_UnInit();
    virtual int LoganVoe_CreateChannel();
    virtual int LoganVoe_DeleteChannel(int channel);
    virtual int LoganVoe_DeleteAllChannel();

    virtual int LoganVoe_SetSendDestination(int channelId, const char* ip, int port);
    virtual int LoganVoe_SetLocalReceiver(int channelId, int port);

    int LoganVoe_FindIndexOfTrans(int channelid);

    virtual int LoganVoe_GetNumsOfCodec();
   
    virtual int LoganVoe_GetSpecCodec(int index, LoganCodec &lc);
    
    virtual int LoganVoe_SetSendCodec(int channelid, LoganCodec lc);

   
    virtual int LoganVoe_GetNumOfRecordingDevices();
    
    virtual int LoganVoe_GetNumOfPlayoutDevices();
    
    virtual int LoganVoe_GetPlayoutDeviceName(int index,char nameUTF8[128], char guidUTF8[128]);
    
    virtual int LoganVoe_GetRecordingDeviceName(int index, char nameUTF8[128], char guidUTF8[128]);
    
    virtual int LoganVoe_SetPlayoutDevice(int idx);
    
    virtual int LoganVoe_SetRecordingDevice(int idx);

    
    virtual int LoganVoe_SetVADStatus(int channelsid, bool b, int mode);
    virtual int LoganVoe_SetAgcStatus(bool b, int mode);
    virtual int LoganVoe_SetEcStatus(bool b, int mode);
    virtual int LoganVoe_SetNsStatus(bool b, int mode);
    virtual int LoganVoe_GetVADStatus(int channelsid, bool &b, int &mode);
    virtual int LoganVoe_GetAgcStatus(bool &b, int &mode);
    virtual int LoganVoe_GetEcStatus(bool &b, int &mode);
    virtual int LoganVoe_GetNsStatus(bool &b, int &mode);

    virtual int LoganVoe_StartReceive(int channelid);
    virtual int LoganVoe_StartPlayout(int channelid);
    virtual int LoganVoe_StartSend(int channelid);
    virtual int LoganVoe_StartRecordingMicrophone(LoganWriteStreamCallBack lwscb);

    virtual int LoganVoe_StartRecordingMicrophone(const char* fileNameUTF8, 
        LoganCodec* codec = NULL);

    virtual int LoganVoe_StartPlayingFileLocally(int channelid,
        LoganReadStreamCallBack lrscb);

    virtual int LoganVoe_StartPlayingFileLocally(int channelid,
        const char fileNameUTF8[1024],
        int samplerate,//(8000, 16000, 32000)
        bool loop = false);

    virtual int LoganVoe_IsPlayingFileLocally(int channel);

    virtual int LoganVoe_StartRecordingPlayout(int channel, const char* fileNameUTF8,
        LoganCodec *codec = NULL);

    virtual int LoganVoe_StartPlayingFileAsMicrophone(
        int channel,
        const char fileNameUTF8[1024],
        int sampleRate,
        bool loop = false ,
        bool mixWithMicrophone = false);

    virtual int LoganVoe_StartPlayingFileAsMicrophone(
        int channel,
        LoganReadStreamCallBack read,
        int sampleRate,
        bool mixWithMicrophone = false);

    virtual int LoganVoe_StopPlayingFileAsMicrophone(int channel);

    virtual int LoganVoe_IsPlayingFileAsMicrophone(int channel);

    virtual int LoganVoe_StopReceive(int channelid);
    virtual int LoganVoe_StopPlayout(int channelid);
    virtual int LoganVoe_StopSend(int channelid);
    virtual int LoganVoe_StopRecordingPlayout(int channel);
    virtual int LoganVoe_StopPlayingFileLocally(int channelid);
    virtual int LoganVoe_StopRecordingMicrophone();

    virtual unsigned int LoganVoe_GetMicVolume();
    virtual unsigned int LoganVoe_GetSpeakerVolume();
    virtual int LoganVoe_SetMicVolume(unsigned int vol);
    virtual int LoganVoe_SetSpeakerVolume(unsigned int vol);
    virtual int LoganVoe_SetInputMute(int channel, bool enable);
    virtual int LoganVoe_GetInputMute(int channel, bool& enabled);
    virtual int LoganVoe_SetSystemOutputMute(bool enable);
    virtual int LoganVoe_GetSystemOutputMute(bool &enabled);
    virtual int LoganVoe_SetSystemInputMute(bool enable);
    virtual int LoganVoe_GetSystemInputMute(bool& enabled);
    virtual int LoganVoe_GetSpeechInputLevel(unsigned int& level);
    virtual int LoganVoe_GetSpeechOutputLevel(int channel, unsigned int& level);

};
#endif //__LOGAN_VOICE_ENGINE_IMPL_H__