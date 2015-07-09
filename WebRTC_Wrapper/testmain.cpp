//#ifdef _DEBUG
/*
#include <iostream>


#include "webrtc_wrapper.h"
#include "CUDP.h"

using namespace std;

CUDP _udpTest;
LoganVoiceEngine *lve;
FILE *rfile = NULL;
FILE *wfile = NULL;

void PrintCodecs();
void PrintDevices();
void ChanTransTest();

int _stdcall read(void *buf,int len)
{
    fread(buf,1, len, rfile);

    return len;
}
bool _stdcall write(const void *buf,int len)
{
    fwrite(buf, 1, len, wfile);

    return true;
}

void PrintOptions()
{
    cout << "webrtc wrapper test" <<endl;
    cout << "1. 打印编码器信息"<<endl;
    cout << "2. 打印音频设备信息"<<endl;
    cout << "3. 网络测试"<<endl;
    cout << "0. 结束"<<endl;
    cout << "    请选择测试项目:"<<endl;
}

int main(int argc, char **argv)
{
// 	char* message = "udp packet";
// 
// 	CUDP clSender;
// 	clSender.Config(54321, "192.168.0.100");
// 
// 	while (1) {
// 		clSender.SendUdp(message, strlen(message));
// 		Sleep(2);
// 	}

// 	CUDP clRecv;
// 	clRecv.Config(54321, "", false);
// 	char * data = NULL;
// 	while (1) {
// 		if (clRecv.RecvUdp(data)) {
// 			printf("recv %s\n", data);
// 			free(data);
// 			data = NULL;
// 		}
// 
// 		else
// 			break;
// 	}
// 	return 0;
    PrintOptions();
    int i = -1;
    cin >> i;
    while (i != 0)
    {
        switch(i)
        {
        case 1:PrintCodecs();break;
        case 2:PrintDevices();break;
        case 3:ChanTransTest();break;
        default:break;
        }
        
        PrintOptions();
        cin >> i;
    }

    return 0;
}

void PrintCodecs()
{
    lve = LoganVoiceEngine::Create();
    LoganCodec cinst;
    for (int i = 0; i < lve->LoganVoe_GetNumsOfCodec(); i++) {
        lve->LoganVoe_GetSpecCodec(i, cinst);

        if (strncmp(cinst.plname, "ISAC", 4) == 0 && cinst.plfreq == 32000) {
            printf("%i. ISAC-swb pltype:%i plfreq:%i channels:%i\n", i, cinst.pltype,
                cinst.plfreq, cinst.channels);
        } else if (strncmp(cinst.plname, "ISAC", 4) == 0 && cinst.plfreq == 48000) {
            printf("%i. ISAC-fb pltype:%i plfreq:%i channels:%i\n", i, cinst.pltype,
                cinst.plfreq, cinst.channels);
        } else {
            printf("%i. %s pltype:%i plfreq:%i channels:%i\n", i, cinst.plname,
                cinst.pltype, cinst.plfreq, cinst.channels);
        }
    }

    cout << "输入“0”结束:";
    while(true)
    {
        int i;
        cin >>i;
        if (i == 0)
        {
            break;
        }
    }
    LoganVoiceEngine::Destroy(lve);
}

void ChanTransTest()
{
    lve = LoganVoiceEngine::Create();

    //PrintCodecs();
    int channelid = lve->LoganVoe_CreateChannel();

    LoganCodec codec;
    lve->LoganVoe_GetSpecCodec(0, codec);
    lve->LoganVoe_SetSendCodec(channelid,codec);
    int localport = 33333, remoteport = 33333;
    char strip[128] = {0};
    cout <<"输入对方IP:";
    cin >> strip;

   lve->LoganVoe_SetSendDestination(channelid, strip, remoteport);
    lve->LoganVoe_SetLocalReceiver(channelid, localport);

    lve->LoganVoe_SetEcStatus(true);
    lve->LoganVoe_SetNsStatus(true);
//	lve->LoganVoe_SetVADStatus(channelid, true);

    lve->LoganVoe_StartPlayout(channelid);
    lve->LoganVoe_StartSend(channelid);
    lve->LoganVoe_StartReceive(channelid);

    cout << "输入“0”结束:";
    while(true)
    {
        int i;
        cin >>i;
        if (i == 0) 
        {
            break;
        }
    }

    lve->LoganVoe_StopReceive(channelid);
    lve->LoganVoe_StopSend(channelid);
    lve->LoganVoe_StopPlayout(channelid);
    lve->LoganVoe_DeleteChannel(channelid);

    LoganVoiceEngine::Destroy(lve);
}

void PrintDevices()
{
    lve = LoganVoiceEngine::Create();
    char name[128] = {0};
    char guid[128] = {0};
    for (int i = 0; i < lve->LoganVoe_GetNumOfPlayoutDevices(); i++)
    {
        lve->LoganVoe_GetPlayoutDeviceName(i, name, guid);
        cout <<"Play Devices: "<<name<<endl;
    }

    for(int j = 0; j < lve->LoganVoe_GetNumOfRecordingDevices(); j++)
    {
        lve->LoganVoe_GetRecordingDeviceName(j, name, guid);
        cout <<"Record Devices:"<<name<<endl;
    }
    cout << "输入“0”结束:";
    while(true)
    {
        int i;
        cin >>i;
        if (i == 0) 
        {
            break;
        }
    }

    LoganVoiceEngine::Destroy(lve);
}
*/

/*
*  Copyright (c) 2012 The WebRTC project authors. All Rights Reserved.
*
*  Use of this source code is governed by a BSD-style license
*  that can be found in the LICENSE file in the root of the source
*  tree. An additional intellectual property rights grant can be found
*  in the file PATENTS.  All contributing project authors may
*  be found in the AUTHORS file in the root of the source tree.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <unistd.h>
#endif

#include <vector>
#include <process.h>
#include "CUDP.h"
#include "CVoiceModuleBase.h"

//#include "testing/gtest/include/gtest/gtest.h"
#include "webrtc/engine_configurations.h"
#include "webrtc/modules/audio_processing/include/audio_processing.h"
#include "webrtc/system_wrappers/interface/scoped_ptr.h"
#include "webrtc/test/channel_transport/include/channel_transport.h"
#include "webrtc/test/testsupport/fileutils.h"
#include "webrtc/test/testsupport/trace_to_stderr.h"
#include "webrtc/voice_engine/include/voe_audio_processing.h"
#include "webrtc/voice_engine/include/voe_base.h"
#include "webrtc/voice_engine/include/voe_codec.h"
#include "webrtc/voice_engine/include/voe_dtmf.h"
#include "webrtc/voice_engine/include/voe_errors.h"
#include "webrtc/voice_engine/include/voe_external_media.h"
#include "webrtc/voice_engine/include/voe_file.h"
#include "webrtc/voice_engine/include/voe_hardware.h"
#include "webrtc/voice_engine/include/voe_neteq_stats.h"
#include "webrtc/voice_engine/include/voe_network.h"
#include "webrtc/voice_engine/include/voe_rtp_rtcp.h"
#include "webrtc/voice_engine/include/voe_video_sync.h"
#include "webrtc/voice_engine/include/voe_volume_control.h"

using namespace webrtc;
using namespace test;

//#define _TWO_SEND_
//#define _CLIENT_
#define _SERVER_

class LoganRevThread
{
public:
	~LoganRevThread();
	LoganRevThread(int Channnal, VoEBase *vBasePtr, int iPort);
	void StartThread();
	void run();
	void SetCodec(CodecInst codecInst) { _rtpHeader.payloadType = codecInst.pltype; _rtpHeader.payload_type_frequency = codecInst.plfreq; }
	static unsigned __stdcall RevThread(LPVOID pContent);
private:
	int _iChannal, _iChannnal2, _iPort;
	VoEBase *_basePtr, *_basePtr2;
	CUDP _udpSev;
	RTPHeader _rtpHeader;
public:
	HANDLE  _hRevThread;
	HANDLE _hStopThreadEvent;
};
LoganRevThread::LoganRevThread(int Channal, VoEBase *vBasePtr, int iPort) :_iChannal(Channal), _basePtr(vBasePtr), _hRevThread(NULL), _hStopThreadEvent(NULL)
{
	_iPort = iPort;
	memset(&_rtpHeader, 0, sizeof(RTPHeader));
	BOOL bRet = _udpSev.Config(iPort, "", FALSE);
	if (!bRet) printf("_udpSev.Config Failed!!!\n");

	_hRevThread = (HANDLE)_beginthreadex(NULL, 0, RevThread, this, CREATE_SUSPENDED, NULL);
	if (NULL == _hRevThread)
	{
		printf("_beginthreadex Failed!!!\n");
	}

	_hStopThreadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (NULL == _hStopThreadEvent)
	{
		printf("CreateEvent Failed!!!\n");
	}
}
LoganRevThread::~LoganRevThread()
{
	if (_hStopThreadEvent)
	{
		BOOL bRet = SetEvent(_hStopThreadEvent);
		_hStopThreadEvent = NULL;
	}
	DWORD dwRet = WaitForSingleObject(_hRevThread, INFINITE);
	return;
}
unsigned __stdcall LoganRevThread::RevThread(LPVOID pContent)
{
	LoganRevThread *pCont = (LoganRevThread *)pContent;
	for (;;)
	{
		DWORD dwRet = WaitForSingleObject(pCont->_hStopThreadEvent, 2);
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
	ResumeThread(_hRevThread);
}

void LoganRevThread::run()
{
//	if (_iPort == 1223) return;
	unsigned char *data = NULL;
	int buffLen = 0;
	BOOL bFlag = _udpSev.RecvUdp(data, buffLen);
	if (!bFlag)
	{
		if (_hStopThreadEvent)
		{
			SetEvent(_hStopThreadEvent);
			_hStopThreadEvent = NULL;
			return;
		}
	}
	if (_basePtr)
	{
		_basePtr->ReceivedPayloadData(_iChannal, data, buffLen, &_rtpHeader);
		free(data);
	}
}

class LoganSendData :public VoiceSendData
{
public:
	virtual void CallbackGetVoiceData(const uint8_t*  payloadData, uint16_t  payloadSize);
	virtual ~LoganSendData(){ DeleteCriticalSection(&_criticalSec); }
	LoganSendData(int iPort,  char *pAddr);
private:
	CUDP _udpSend;
	CRITICAL_SECTION  _criticalSec;
	int _iPort;
};
LoganSendData::LoganSendData(int iPort, char *pAddr) :_iPort(iPort)
{
	InitializeCriticalSection(&_criticalSec);
	BOOL bRet = _udpSend.Config(iPort, pAddr);
	if (!bRet) printf("_udpSend.Config Failed!!!\n");
}
void LoganSendData::CallbackGetVoiceData(const uint8_t* payloadData, uint16_t payloadSize)
{
//	if (_iPort == 1223) return;
	EnterCriticalSection(&_criticalSec);
	BOOL bRet = _udpSend.SendUdp((unsigned char *)payloadData, payloadSize);
	LeaveCriticalSection(&_criticalSec);
	Sleep(1);
	if (!bRet) printf("_udpSend.SendUdp Failed!!!\n");
	return;
}

class SendTest :public VoiceSendData
{
public:
	SendTest() {}
	~SendTest() {}
	void CallbackGetVoiceData(const uint8_t* payloadData, uint16_t payloadSize) { return; }
};


#define VALIDATE                                           \
  if (res != 0) {                                          \
    printf("*** Error at line %i \n", __LINE__);           \
    printf("*** Error code = %i \n", base1->LastError());  \
    }

VoiceEngine *m_voe = NULL, *m_voe2 = NULL;
VoEBase *base1 = NULL, *base2 = NULL;
VoECodec *codec = NULL, *codec2 = NULL;
VoEVolumeControl* volume = NULL;
VoEDtmf* dtmf = NULL;
VoERTP_RTCP* rtp_rtcp = NULL;
VoEAudioProcessing *apm = NULL, *apm2 = NULL;
VoENetwork* netw = NULL;
VoEFile* file = NULL;
VoEVideoSync* vsync = NULL;
VoEHardware *hardware = NULL, *hardware2 = NULL;
VoEExternalMedia* xmedia = NULL;
VoENetEqStats* neteqst = NULL;
LoganRevThread *gRevThPtr = NULL, *gRevThPtr2 = NULL;
LoganSendData *gSendPtr = NULL, *gSendPtr2 = NULL;
SendTest *gSendTest = NULL;

void RunTest(std::string out_path);

class MyObserver : public VoiceEngineObserver {
public:
	virtual void CallbackOnError(int channel, int err_code);
};

void MyObserver::CallbackOnError(int channel, int err_code) {
	// Add printf for other error codes here
	if (err_code == VE_TYPING_NOISE_WARNING) {
		printf("  TYPING NOISE DETECTED \n");
	}
	else if (err_code == VE_TYPING_NOISE_OFF_WARNING) {
		printf("  TYPING NOISE OFF DETECTED \n");
	}
	else if (err_code == VE_RECEIVE_PACKET_TIMEOUT) {
		printf("  RECEIVE PACKET TIMEOUT \n");
	}
	else if (err_code == VE_PACKET_RECEIPT_RESTARTED) {
		printf("  PACKET RECEIPT RESTARTED \n");
	}
	else if (err_code == VE_RUNTIME_PLAY_WARNING) {
		printf("  RUNTIME PLAY WARNING \n");
	}
	else if (err_code == VE_RUNTIME_REC_WARNING) {
		printf("  RUNTIME RECORD WARNING \n");
	}
	else if (err_code == VE_SATURATION_WARNING) {
		printf("  SATURATION WARNING \n");
	}
	else if (err_code == VE_RUNTIME_PLAY_ERROR) {
		printf("  RUNTIME PLAY ERROR \n");
	}
	else if (err_code == VE_RUNTIME_REC_ERROR) {
		printf("  RUNTIME RECORD ERROR \n");
	}
	else if (err_code == VE_REC_DEVICE_REMOVED) {
		printf("  RECORD DEVICE REMOVED \n");
	}
}

void SetStereoIfOpus(bool use_stereo, CodecInst* codec_params) {
	if (strncmp(codec_params->plname, "opus", 4) == 0) {
		if (use_stereo)
			codec_params->channels = 2;
		else
			codec_params->channels = 1;
	}
}

int PrintCodecs(bool opus_stereo) {
	CodecInst codec_params;
	for (int i = 0; i < codec->NumOfCodecs(); ++i) {
		int res = codec->GetCodec(i, codec_params);
		VALIDATE;
		SetStereoIfOpus(opus_stereo, &codec_params);
		printf("%2d. %3d  %s/%d/%d \n", i, codec_params.pltype, codec_params.plname,
			codec_params.plfreq, codec_params.channels);
// 		if (codec_params.pltype == 'k')
// 		{
// 			return i;
// 		}
	}
	return 0;
}

int main(int argc, char** argv) {
//	google::ParseCommandLineFlags(&argc, &argv, true);
	//==============================================================
	int res = 0;

	printf("Test started \n");

	m_voe = VoiceEngine::Create();
	
	base1 = VoEBase::GetInterface(m_voe);
	
	codec = VoECodec::GetInterface(m_voe);

	apm = VoEAudioProcessing::GetInterface(m_voe);

	volume = VoEVolumeControl::GetInterface(m_voe);
	dtmf = VoEDtmf::GetInterface(m_voe);
	rtp_rtcp = VoERTP_RTCP::GetInterface(m_voe);
	netw = VoENetwork::GetInterface(m_voe);
	file = VoEFile::GetInterface(m_voe);
	vsync = VoEVideoSync::GetInterface(m_voe);

	hardware = VoEHardware::GetInterface(m_voe);
#ifdef _TWO_SEND_
	m_voe2 = VoiceEngine::Create();
	base2 = VoEBase::GetInterface(m_voe2);
	codec2 = VoECodec::GetInterface(m_voe2);
	apm2 = VoEAudioProcessing::GetInterface(m_voe2);
	hardware2 = VoEHardware::GetInterface(m_voe2);
#endif
	xmedia = VoEExternalMedia::GetInterface(m_voe);
	neteqst = VoENetEqStats::GetInterface(m_voe);

	//=============================FileTrace===================================
	scoped_ptr<test::TraceToStderr> trace_to_stderr;
	{
		const std::string trace_filename = "webrtc_trace.txt";
		VoiceEngine::SetTraceFilter(kTraceAll);
		res = VoiceEngine::SetTraceFile(trace_filename.c_str());
		VALIDATE;
		res = VoiceEngine::SetTraceCallback(NULL);
		VALIDATE;
		printf("Outputting logs to file: %s\n", trace_filename.c_str());
	}
	//========================================================================

	printf("Init\n");
	res = base1->Init();
	if (res != 0) {
		printf("\nError calling Init: %d\n", base1->LastError());
		fflush(NULL);
		exit(1);
	}
// 	res = base1->StartRecord();
// 	return 0;

#ifdef _TWO_SEND_
	res = base2->Init();
	if (res != 0){
		printf("\nErrorCalling base2 Init: %d\n", base2->LastError());
		fflush(NULL);
		exit(1);
	}
#endif

	printf("Version\n");
	char tmp[1024];
	res = base1->GetVersion(tmp);
	VALIDATE;
	printf("%s\n", tmp);

	RunTest("E:\\WebRtcDemo\\test");

	printf("Terminate \n");

	
	res = base1->Terminate();
	VALIDATE;
#ifdef _TWO_SNED_
	res = base2->Terminate();
	VALIDATE;
#endif
	if (base1)
		base1->Release();
	if (base2)
		base2->Release();

	if (codec)
		codec->Release();
	if (codec2)
		codec2->Release();

	if (volume)
		volume->Release();

	if (dtmf)
		dtmf->Release();

	if (rtp_rtcp)
		rtp_rtcp->Release();

	if (apm)
		apm->Release();
	if (apm2)
		apm2->Release();

	if (netw)
		netw->Release();

	if (file)
		file->Release();

	if (vsync)
		vsync->Release();

	if (hardware)
		hardware->Release();
	if (hardware2)
		hardware2->Release();

	if (xmedia)
		xmedia->Release();

	if (neteqst)
		neteqst->Release();

	if (gRevThPtr)
		free(gRevThPtr);
	if (gRevThPtr2)
		free(gRevThPtr2);

	if (gSendPtr)
		free(gSendPtr);
	if (gSendPtr2)
		free(gSendPtr2);
	if (gSendTest)
		free(gSendTest);

	VoiceEngine::Delete(m_voe);
#ifdef _TWO_SEND_
	VoiceEngine::Delete(m_voe2);
#endif	
	return 0;
}


void RunTest(std::string out_path) {
	int chan, chan2, res;
	CodecInst cinst;
	bool enable_aec = false;
	bool enable_agc = false;
	bool enable_rx_agc = false;
	bool enable_cng = false;
	bool enable_ns = false;
	bool enable_rx_ns = false;
	bool typing_detection = false;
	bool muted = false;
	bool opus_stereo = false;
	bool experimental_ns_enabled = false;

	chan = base1->CreateChannel();
//	chan2 = base1->CreateChannel();
	if (chan < 0) {
		printf("************ Error code = %i\n", base1->LastError());
		fflush(NULL);
	}

// 	scoped_ptr<VoiceChannelTransport> voice_channel_transport(
//  		new VoiceChannelTransport(netw, chan));
	VoiceChannelTransport *voice_channel_transport(new VoiceChannelTransport(netw, chan));
// 	scoped_ptr<VoiceChannelTransport> voice_channel_transport2(
// 		new VoiceChannelTransport(netw, chan2));


	int lPort = 1222;
	printf("Set Rec Port \n");

	char *temp = "172.20.28.144";
	unsigned long inum = inet_addr(temp);
	//	res = voice_channel_transport->SetLocalReceiver(lPort);
	IN_ADDR inTemp;
	inTemp.S_un.S_addr = 553494720;//84060352;
	char *chInTemp = inet_ntoa(inTemp);
	int iLen = strlen(chInTemp);
	char szTemp[MAX_PATH] = { 0 };
	CopyMemory(szTemp, chInTemp, 15);
	TCHAR szMsg[MAX_PATH];
	USES_CONVERSION;
	wsprintf(szMsg, L"[VolCtrl]...Init, line=%d, %s", __LINE__, A2W(szTemp));
	OutputDebugString(szMsg);
//	res = voice_channel_transport->SetMulticastReceive("224.2.2.222", lPort);
	lPort += 2;
//	res = voice_channel_transport2->SetMulticastReceive("224.2.2.222", lPort);
//	VALIDATE;
	char ip[64];
	printf("1. 127.0.0.1 \n");
	printf("2. Specify IP \n");
	int ip_selection;
//	ASSERT_EQ(1, scanf("%i", &ip_selection));
	scanf("%i", &ip_selection);

	if (ip_selection == 1) {
		strcpy(ip, "127.0.0.1");
	}
	else {
		printf("Specify remote IP: ");
//		ASSERT_EQ(1, scanf("%s", ip));
		scanf("%s", ip);
	}

	int rPort = 1222;
	printf("Set Send port \n");

	printf("Set Send IP \n");
	res = voice_channel_transport->SetSendDestination(ip, rPort);
	res = voice_channel_transport->SetLocalReceiver(rPort);
	rPort += 2;
//	res = voice_channel_transport2->SetSendDestination(ip, rPort);
	VALIDATE;
	


	printf("\n");
	int iCode = PrintCodecs(opus_stereo);
	scanf("%i", &iCode);
	codec->GetCodec(iCode, cinst);

	printf("Set primary codec\n");
	SetStereoIfOpus(opus_stereo, &cinst);
	res = codec->SetSendCodec(chan, cinst);
	VALIDATE;

	// Call loop
	bool newcall = true;
	while (newcall) {
		int rd(-1), pd(-1);
		res = hardware->GetNumOfRecordingDevices(rd);
		VALIDATE;
		res = hardware->GetNumOfPlayoutDevices(pd);
		VALIDATE;

		char dn[128] = { 0 };
		char guid[128] = { 0 };
		printf("\nPlayout devices (%d): \n", pd);
		for (int j = 0; j < pd; ++j) {
			res = hardware->GetPlayoutDeviceName(j, dn, guid);
			VALIDATE;
			printf("  %d: %s \n", j, dn);
		}

		printf("Recording devices (%d): \n", rd);
		GUID guidTemp = GUID_NULL;
		char chTemp[128] = { 0 };
		TCHAR charTemp[MAX_PATH] = { 0 };
		for (int j = 0; j < rd; ++j) {
			res = hardware->GetRecordingDeviceName(j, dn, guid);
			for (int k = 0; k < 128; ++k)
			{
				if (guid[k] == '.' && guid[k + 1] == '{')
				{
					int m = 0;
					while (guid[k + 1] != '}')
					{
						chTemp[m++] = guid[k + 1];
						++k;
					}
					chTemp[m] = guid[k + 1];
					break;
				}
			}
			USES_CONVERSION;
			LPWSTR pszText = A2W(chTemp);
			HRESULT  hRes = CLSIDFromString(pszText, &guidTemp);
			//CO_E_CLASSSTRING
			VALIDATE;
			printf("  %d: %s \n", j, dn);
		}

		printf("Select playout device: ");
//		ASSERT_EQ(1, scanf("%d", &pd));
		scanf("%d", &pd);
		res = hardware->SetPlayoutDevice(pd);
		VALIDATE;
		printf("Select recording device: ");
//		ASSERT_EQ(1, scanf("%d", &rd));
		scanf("%d", &rd);
		printf("Setting sound devices \n");
//		res = hardware->SetRecordingDevice(rd, false);
		res = hardware->SetRecordingDevice(0, true);
		VALIDATE;

		res = codec->SetVADStatus(0, enable_cng);
		VALIDATE;

		res = apm->SetAgcStatus(enable_agc);
		VALIDATE;

		res = apm->SetEcStatus(enable_aec);
		VALIDATE;

		res = apm->SetNsStatus(enable_ns);
		VALIDATE;

		printf("\n1. Send, listen and playout \n");
		printf("2. Send only \n");
		printf("3. Listen and playout only \n");
		printf("Select transfer mode: ");
		int call_selection;
//		ASSERT_EQ(1, scanf("%i", &call_selection));
		scanf("%i", &call_selection);
		const bool send = !(call_selection == 3);
		const bool receive = !(call_selection == 2);

		if (receive) {
#ifndef EXTERNAL_TRANSPORT
			printf("Start Listen \n");
			res = base1->StartReceive(chan);
//			res = base1->StartReceive(chan2);
			VALIDATE;
#endif

			printf("Start Playout \n");
			res = base1->StartPlayout(chan);
//			res = base1->StartPlayout(chan2);
			VALIDATE;
		}

		if (send) {
			printf("Start Send \n");
			res = base1->StartSend(chan);
//			res = base1->StartSend(chan2);
			VALIDATE;
		}

		printf("Getting mic volume \n");
		unsigned int vol = 999;
		res = volume->GetMicVolume(vol);
		VALIDATE;
		if ((vol > 255) || (vol < 1)) {
			printf("\n****ERROR in GetMicVolume");
		}

		int forever = 1;
		while (forever) {
			printf("\nSelect codec\n");
			PrintCodecs(opus_stereo);
			printf("\nOther actions\n");
			const int num_codecs = codec->NumOfCodecs();
			int option_index = num_codecs;	
			printf("%i. Toggle NS\n", option_index++);
			printf("%i. Toggle EC\n", option_index++);
			printf("%i. Select AEC\n", option_index++);
			int option_selection;
//			ASSERT_EQ(1, scanf("%i", &option_selection));
			scanf("%i", &option_selection);
			option_index = num_codecs;
			if (option_selection < option_index) {
				res = codec->GetCodec(option_selection, cinst);
				VALIDATE;
				SetStereoIfOpus(opus_stereo, &cinst);
				printf("Set primary codec\n");
				res = codec->SetSendCodec(chan, cinst);
				VALIDATE;
			}
			else if (option_selection == option_index++) {
				enable_ns = !enable_ns;
				res = apm->SetNsStatus(enable_ns);
				VALIDATE;
				if (enable_ns)
					printf("\n NS is now on! \n");
				else
					printf("\n NS is now off! \n");
			}
			else if (option_selection == option_index++) {
				enable_aec = !enable_aec;
				res = apm->SetEcStatus(enable_aec, kEcUnchanged);
				VALIDATE;
				if (enable_aec)
					printf("\n Echo control is now on! \n");
				else
					printf("\n Echo control is now off! \n");
			}
			else if (option_selection == option_index++) {
				res = apm->SetEcStatus(enable_aec, kEcAec);
				VALIDATE;
				printf("\n AEC selected! \n");
				if (enable_aec)
					printf(" (Echo control is on)\n");
				else
					printf(" (Echo control is off)\n");
			}
			
			else {
				break;
			}
		}

		if (send) {
			printf("Stop Send \n");
			res = base1->StopSend(chan);
//			res = base1->StopSend(chan2);
			VALIDATE;
		}

		if (receive) {
			printf("Stop Playout \n");
			res = base1->StopPlayout(chan);
//			res = base1->StopPlayout(chan2);
			VALIDATE;

#ifndef EXTERNAL_TRANSPORT
			printf("Stop Listen \n");
			res = base1->StopReceive(chan);
//			res = base1->StopReceive(chan2);
			VALIDATE;
#endif
		}

		printf("\n1. New call \n");
		printf("2. Quit \n");
		printf("Select action: ");
		int end_option;
//		ASSERT_EQ(1, scanf("%i", &end_option));
		scanf("%i", &end_option);
		newcall = (end_option == 1);
		// Call loop
	}

	printf("Delete channels \n");
	res = base1->DeleteChannel(chan);
	delete(voice_channel_transport);
//	res = base1->DeleteChannel(chan2);
	VALIDATE;
}


/*
void RunTest(std::string out_path) {
	int chan, chan2, res;
	CodecInst cinst;
	bool enable_cng = false;
	bool enable_agc = false;
	bool enable_aec = false;
	bool enable_ns = false;
	bool enable_rx_ns = false;
	bool typing_detection = false;
	bool muted = false;
	bool opus_stereo = false;
	bool experimental_ns_enabled = false;

	chan = base1->CreateChannel();
	chan2 = base2->CreateChannel();
	if (chan < 0 ) {
		printf("************ Error code = %i\n", base1->LastError());
		fflush(NULL);
	}
	
	char ip[64];
	printf("1. 127.0.0.1 \n");
	printf("2. Specify IP \n");
	int ip_selection;
	scanf("%i", &ip_selection);

	if (ip_selection == 1) {
		strcpy(ip, "127.0.0.1");
	}
	else {
		printf("Specify remote IP: ");
		scanf("%s", ip);
	}

	int rPort = 1222;
	printf("Set Send port \n");

	printf("Set Send IP \n");
	gSendPtr = new LoganSendData(rPort, ip);
	res = base1->RegisterVoiceSendData(*gSendPtr);
#ifdef  _SERVER_
	gSendPtr2 = new LoganSendData(rPort + 1, ip);
	res = base2->RegisterVoiceSendData(*gSendPtr2);
#else
	gSendTest = new SendTest();
	res = base2->RegisterVoiceSendData(*gSendTest);
#endif

	VALIDATE;
 
	int lPort = 1222;
	printf("Set Rec Port \n");

	gRevThPtr = new LoganRevThread(chan, base1, lPort);
#ifdef _CLIENT_
	gRevThPtr2 = new LoganRevThread(chan2, base2, lPort + 1);
#endif	
	VALIDATE;

	printf("\n");
	int iCode = PrintCodecs(opus_stereo);
	scanf("%i", &iCode);
	codec->GetCodec(iCode, cinst);
	codec2->GetCodec(iCode, cinst);

	printf("Set primary codec\n");
	SetStereoIfOpus(opus_stereo, &cinst);
	res = codec->SetSendCodec(chan, cinst);
#ifdef _SERVER_
	res = codec2->SetSendCodec(chan2, cinst);
#endif
	gRevThPtr->SetCodec(cinst);
	res = base1->InitializeRevDataDecoder(chan, cinst);
#ifdef _CLIENT_
	gRevThPtr2->SetCodec(cinst);
	res = base2->InitializeRevDataDecoder(chan2, cinst);
#endif
	VALIDATE;

	// Call loop
	bool newcall = true;
	while (newcall) {
		int rd(-1), pd(-1), rd2(-1);
		res = hardware->GetNumOfRecordingDevices(rd);
		VALIDATE;
		res = hardware->GetNumOfPlayoutDevices(pd);
		VALIDATE;

		char dn[128] = { 0 };
		char guid[128] = { 0 };
		printf("\nPlayout devices (%d): \n", pd);
		for (int j = 0; j < pd; ++j) {
			res = hardware->GetPlayoutDeviceName(j, dn, guid);
			VALIDATE;
			printf("  %d: %s \n", j, dn);
		}

		printf("Recording devices (%d): \n", rd);
		for (int j = 0; j < rd; ++j) {
			res = hardware->GetRecordingDeviceName(j, dn, guid);
			VALIDATE;
			printf("  %d: %s \n", j, dn);
		}

		printf("Select playout device: ");
		scanf("%d", &pd);
		res = hardware->SetPlayoutDevice(pd);
		VALIDATE;
		printf("Select recording device: ");
		scanf("%d", &rd);
#ifdef _SERVER_
		printf("Select recording device2:");
		scanf("%d", &rd2);
		res = hardware2->SetRecordingDevice(rd2);
#endif
		printf("Setting sound devices \n");
		res = hardware->SetRecordingDevice(rd);
		VALIDATE;

		res = codec->SetVADStatus(chan, enable_cng);
		res = codec2->SetVADStatus(chan2, enable_cng);
		VALIDATE;

		res = apm->SetAgcStatus(enable_agc);
		res = apm2->SetAgcStatus(enable_agc);
		VALIDATE;

		res = apm->SetEcStatus(enable_aec);
		res = apm2->SetEcStatus(enable_aec);
		VALIDATE;

		res = apm->SetNsStatus(enable_ns);
		res = apm2->SetNsStatus(enable_ns);
		VALIDATE;

		printf("\n1. Send, listen and playout \n");
		printf("2. Send only \n");
		printf("3. Listen and playout only \n");
		printf("Select transfer mode: ");
		int call_selection;
		scanf("%i", &call_selection);
		const bool send = !(call_selection == 3);
		const bool receive = !(call_selection == 2);

		if (receive) {
			printf("Start Listen \n");
			res = base1->StartReceive(chan);
#ifdef _CLIENT_
			res = base2->StartReceive(chan2);
#endif
			VALIDATE;

			printf("Start Playout \n");
			res = base1->StartPlayout(chan);
#ifdef _CLIENT_
			res = base2->StartPlayout(chan2);
#endif
			VALIDATE;
		}

		if (send) {
			printf("Start Send \n");
			res = base1->StartSend(chan);
#ifdef _SERVER_
			res = base2->StartSend(chan2);
#endif
			VALIDATE;
		}

		printf("Getting mic volume \n");
		unsigned int vol = 999;
		res = volume->GetMicVolume(vol);
		VALIDATE;
		if ((vol > 255) || (vol < 1)) {
			printf("\n****ERROR in GetMicVolume");
		}
		gRevThPtr->StartThread();
#ifdef _CLIENT_
		gRevThPtr2->StartThread();
#endif
		int forever = 1;
		while (forever) {
			printf("\nSelect codec\n");
			PrintCodecs(opus_stereo);
			printf("\nOther actions\n");
			const int num_codecs = codec->NumOfCodecs();
			int option_index = num_codecs;
			printf("%i. Toggle NS\n", option_index++);
			printf("%i. Toggle EC\n", option_index++);
			printf("%i. Select AEC\n", option_index++);
			printf("%i. Toggle AGC\n", option_index++);
			int option_selection;

			scanf("%i", &option_selection);
			option_index = num_codecs;
			if (option_selection < option_index) {
				res = codec->GetCodec(option_selection, cinst);
				VALIDATE;
				SetStereoIfOpus(opus_stereo, &cinst);
				printf("Set primary codec\n");
				res = codec->SetSendCodec(chan, cinst);
				VALIDATE;
			}
			else if (option_selection == option_index++) {
				enable_ns = !enable_ns;
				res = apm->SetNsStatus(enable_ns);
//				res = apm2->SetNsStatus(enable_ns);
				VALIDATE;
				if (enable_ns)
					printf("\n NS is now on! \n");
				else
					printf("\n NS is now off! \n");
			}
			else if (option_selection == option_index++) {
				enable_aec = !enable_aec;
				res = apm->SetEcStatus(enable_aec, kEcUnchanged);
//				res = apm2->SetEcStatus(enable_aec, kEcUnchanged);
				VALIDATE;
				if (enable_aec)
					printf("\n Echo control is now on! \n");
				else
					printf("\n Echo control is now off! \n");
			}
			else if (option_selection == option_index++) {
				res = apm->SetEcStatus(enable_aec, kEcAec);
//				res = apm2->SetEcStatus(enable_aec, kEcAec);
				VALIDATE;
				printf("\n AEC selected! \n");
				if (enable_aec)
					printf(" (Echo control is on)\n");
				else
					printf(" (Echo control is off)\n");
			}
			else if (option_selection == option_index++){
				enable_agc = !enable_agc;
				res = apm->SetAgcStatus(enable_agc);
				res = apm->SetAgcStatus(enable_agc, kAgcDefault);
				VALIDATE;
				printf("\n AGC selected!\n");
				if (enable_agc)
					printf("(AGC control is on)\n");
				else
					printf("(AGC control is off)\n");
			}

			else {
				break;
			}
		}

		if (send) {
			printf("Stop Send \n");
			res = base1->StopSend(chan);
#ifdef _SERVER_
			res = base2->StopSend(chan2);
#endif
			VALIDATE;
		}

		if (receive) {
			printf("Stop Playout \n");
			res = base1->StopPlayout(chan);
#ifdef _CLIENT_
			res = base2->StopPlayout(chan2);
#endif
			VALIDATE;

			printf("Stop Listen \n");
			res = base1->StopReceive(chan);
#ifdef _CLIENT_
			res = base2->StopReceive(chan2);
#endif
			VALIDATE;
		}

		printf("\n1. New call \n");
		printf("2. Quit \n");
		printf("Select action: ");
		int end_option;
		scanf("%i", &end_option);
		newcall = (end_option == 1);
	}

	printf("Delete channels \n");
	res = base1->DeleteChannel(chan);
	res = base2->DeleteChannel(chan2);
	VALIDATE;
}
*/
//#endif


/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <unistd.h>
#endif

#include <vector>

#include "webrtc/engine_configurations.h"
#include "webrtc/modules/audio_processing/include/audio_processing.h"
#include "webrtc/system_wrappers/interface/scoped_ptr.h"
#include "webrtc/test/channel_transport/include/channel_transport.h"
#include "webrtc/test/testsupport/fileutils.h"
#include "webrtc/test/testsupport/trace_to_stderr.h"
#include "webrtc/voice_engine/include/voe_audio_processing.h"
#include "webrtc/voice_engine/include/voe_base.h"
#include "webrtc/voice_engine/include/voe_codec.h"
#include "webrtc/voice_engine/include/voe_dtmf.h"
#include "webrtc/voice_engine/include/voe_errors.h"
#include "webrtc/voice_engine/include/voe_external_media.h"
#include "webrtc/voice_engine/include/voe_file.h"
#include "webrtc/voice_engine/include/voe_hardware.h"
#include "webrtc/voice_engine/include/voe_neteq_stats.h"
#include "webrtc/voice_engine/include/voe_network.h"
#include "webrtc/voice_engine/include/voe_rtp_rtcp.h"
#include "webrtc/voice_engine/include/voe_video_sync.h"
#include "webrtc/voice_engine/include/voe_volume_control.h"


using namespace webrtc;
using namespace test;

#define VALIDATE                                           \
  if (res != 0) {                                          \
    printf("*** Error at line %i \n", __LINE__);           \
    printf("*** Error code = %i \n", base1->LastError());  \
    }

VoiceEngine* m_voe = NULL;
VoEBase* base1 = NULL;
VoECodec* codec = NULL;
VoEVolumeControl* volume = NULL;
VoEDtmf* dtmf = NULL;
VoERTP_RTCP* rtp_rtcp = NULL;
VoEAudioProcessing* apm = NULL;
VoENetwork* netw = NULL;
VoEFile* file = NULL;
VoEVideoSync* vsync = NULL;
VoEHardware* hardware = NULL;
VoEExternalMedia* xmedia = NULL;
VoENetEqStats* neteqst = NULL;

void RunTest(std::string out_path);

class MyObserver : public VoiceEngineObserver {
public:
	virtual void CallbackOnError(int channel, int err_code);
};

void MyObserver::CallbackOnError(int channel, int err_code) {
	// Add printf for other error codes here
	if (err_code == VE_TYPING_NOISE_WARNING) {
		printf("  TYPING NOISE DETECTED \n");
	}
	else if (err_code == VE_TYPING_NOISE_OFF_WARNING) {
		printf("  TYPING NOISE OFF DETECTED \n");
	}
	else if (err_code == VE_RECEIVE_PACKET_TIMEOUT) {
		printf("  RECEIVE PACKET TIMEOUT \n");
	}
	else if (err_code == VE_PACKET_RECEIPT_RESTARTED) {
		printf("  PACKET RECEIPT RESTARTED \n");
	}
	else if (err_code == VE_RUNTIME_PLAY_WARNING) {
		printf("  RUNTIME PLAY WARNING \n");
	}
	else if (err_code == VE_RUNTIME_REC_WARNING) {
		printf("  RUNTIME RECORD WARNING \n");
	}
	else if (err_code == VE_SATURATION_WARNING) {
		printf("  SATURATION WARNING \n");
	}
	else if (err_code == VE_RUNTIME_PLAY_ERROR) {
		printf("  RUNTIME PLAY ERROR \n");
	}
	else if (err_code == VE_RUNTIME_REC_ERROR) {
		printf("  RUNTIME RECORD ERROR \n");
	}
	else if (err_code == VE_REC_DEVICE_REMOVED) {
		printf("  RECORD DEVICE REMOVED \n");
	}
}

void SetStereoIfOpus(bool use_stereo, CodecInst* codec_params) {
	if (strncmp(codec_params->plname, "opus", 4) == 0) {
		if (use_stereo)
			codec_params->channels = 2;
		else
			codec_params->channels = 1;
	}
}

void PrintCodecs(bool opus_stereo) {
	CodecInst codec_params;
	for (int i = 0; i < codec->NumOfCodecs(); ++i) {
		int res = codec->GetCodec(i, codec_params);
		VALIDATE;
		SetStereoIfOpus(opus_stereo, &codec_params);
		printf("%2d. %3d  %s/%d/%d \n", i, codec_params.pltype, codec_params.plname,
			codec_params.plfreq, codec_params.channels);
	}
}

int main(int argc, char** argv) {

	int res = 0;

	printf("Test started \n");

	m_voe = VoiceEngine::Create();
	base1 = VoEBase::GetInterface(m_voe);
	codec = VoECodec::GetInterface(m_voe);
	apm = VoEAudioProcessing::GetInterface(m_voe);
	volume = VoEVolumeControl::GetInterface(m_voe);
	dtmf = VoEDtmf::GetInterface(m_voe);
	rtp_rtcp = VoERTP_RTCP::GetInterface(m_voe);
	netw = VoENetwork::GetInterface(m_voe);
	file = VoEFile::GetInterface(m_voe);
	vsync = VoEVideoSync::GetInterface(m_voe);
	hardware = VoEHardware::GetInterface(m_voe);
	xmedia = VoEExternalMedia::GetInterface(m_voe);
	neteqst = VoENetEqStats::GetInterface(m_voe);

	MyObserver my_observer;

	scoped_ptr<test::TraceToStderr> trace_to_stderr;
	 {
		const std::string trace_filename = "webrtc_trace.txt";
		VoiceEngine::SetTraceFilter(kTraceAll);
		res = VoiceEngine::SetTraceFile(trace_filename.c_str());
		VALIDATE;
		res = VoiceEngine::SetTraceCallback(NULL);
		VALIDATE;
		printf("Outputting logs to file: %s\n", trace_filename.c_str());
	}

	printf("Init\n");
	res = base1->Init();
	if (res != 0) {
		printf("\nError calling Init: %d\n", base1->LastError());
		fflush(NULL);
		exit(1);
	}

	res = base1->RegisterVoiceEngineObserver(my_observer);
	VALIDATE;

	printf("Version\n");
	char tmp[1024];
	res = base1->GetVersion(tmp);
	VALIDATE;
	printf("%s\n", tmp);

	RunTest("E:\\Test");

	printf("Terminate \n");

	base1->DeRegisterVoiceEngineObserver();

	res = base1->Terminate();
	VALIDATE;

	if (base1)
		base1->Release();

	if (codec)
		codec->Release();

	if (volume)
		volume->Release();

	if (dtmf)
		dtmf->Release();

	if (rtp_rtcp)
		rtp_rtcp->Release();

	if (apm)
		apm->Release();

	if (netw)
		netw->Release();

	if (file)
		file->Release();

	if (vsync)
		vsync->Release();

	if (hardware)
		hardware->Release();

	if (xmedia)
		xmedia->Release();

	if (neteqst)
		neteqst->Release();

	VoiceEngine::Delete(m_voe);

	return 0;
}

void RunTest(std::string out_path) {
	int chan, res;
	CodecInst cinst;
	bool enable_aec = false;
	bool enable_agc = false;
	bool enable_rx_agc = false;
	bool enable_cng = false;
	bool enable_ns = false;
	bool enable_rx_ns = false;
	bool typing_detection = false;
	bool muted = false;
	bool opus_stereo = false;
	bool experimental_ns_enabled = false;

// #if defined(WEBRTC_ANDROID)
// 	std::string resource_path = "/sdcard/";
// #else
// 	std::string resource_path = webrtc::test::ProjectRootPath();
// 	if (resource_path == webrtc::test::kCannotFindProjectRootDir) {
// 		printf("*** Unable to get project root directory. "
// 			"File playing may fail. ***\n");
// 		// Fall back to the current directory.
// 		resource_path = "./";
// 	}
// 	else {
// 		resource_path += "data/voice_engine/";
// 	}
// #endif
	const std::string audio_filename = "audio_long16.pcm";

	const std::string play_filename = out_path + "recorded_playout.pcm";
	const std::string mic_filename = out_path + "recorded_mic.pcm";

	chan = base1->CreateChannel();
	if (chan < 0) {
		printf("************ Error code = %i\n", base1->LastError());
		fflush(NULL);
	}

	scoped_ptr<VoiceChannelTransport> voice_channel_transport(
		new VoiceChannelTransport(netw, chan));

	char ip[64];
	printf("1. 127.0.0.1 \n");
	printf("2. Specify IP \n");
	int ip_selection;
	scanf("%i", &ip_selection);

	if (ip_selection == 1) {
		strcpy(ip, "127.0.0.1");
	}
	else {
		printf("Specify remote IP: ");
		scanf("%s", ip);
	}

	int rPort;
	printf("Specify remote port (1=1234): ");
	scanf("%i", &rPort);
	if (1 == rPort)
		rPort = 1234;
	printf("Set Send port \n");

	printf("Set Send IP \n");
	res = voice_channel_transport->SetSendDestination(ip, rPort);
	VALIDATE;

	int lPort;
	printf("Specify local port (1=1234): ");
	scanf("%i", &lPort);
	if (1 == lPort)
		lPort = 1234;
	printf("Set Rec Port \n");

	res = voice_channel_transport->SetLocalReceiver(lPort);
	VALIDATE;

	printf("\n");
	PrintCodecs(opus_stereo);
	printf("Select send codec: ");
	int codec_selection;
	scanf("%i", &codec_selection);
	codec->GetCodec(codec_selection, cinst);

	printf("Set primary codec\n");
	SetStereoIfOpus(opus_stereo, &cinst);
	res = codec->SetSendCodec(chan, cinst);
	VALIDATE;

	const int kMaxNumChannels = 8;
	int channel_index = 0;
	std::vector<int> channels(kMaxNumChannels);
	std::vector<VoiceChannelTransport*> voice_channel_transports(kMaxNumChannels);

	for (int i = 0; i < kMaxNumChannels; ++i) {
		channels[i] = base1->CreateChannel();
		int port = rPort + (i + 1) * 2;

		voice_channel_transports[i] = new VoiceChannelTransport(netw, channels[i]);

		res = voice_channel_transports[i]->SetSendDestination(ip, port);
		VALIDATE;
		res = voice_channel_transports[i]->SetLocalReceiver(port);
		VALIDATE;
		res = codec->SetSendCodec(channels[i], cinst);
		VALIDATE;
	}

	// Call loop
	bool newcall = true;
	while (newcall) {
		int rd(-1), pd(-1);
		res = hardware->GetNumOfRecordingDevices(rd);
		VALIDATE;
		res = hardware->GetNumOfPlayoutDevices(pd);
		VALIDATE;

		char dn[128] = { 0 };
		char guid[128] = { 0 };
		printf("\nPlayout devices (%d): \n", pd);
		for (int j = 0; j < pd; ++j) {
			res = hardware->GetPlayoutDeviceName(j, dn, guid);
			VALIDATE;
			printf("  %d: %s \n", j, dn);
		}

		printf("Recording devices (%d): \n", rd);
		for (int j = 0; j < rd; ++j) {
			res = hardware->GetRecordingDeviceName(j, dn, guid);
			VALIDATE;
			printf("  %d: %s \n", j, dn);
		}

		printf("Select playout device: ");
		scanf("%d", &pd);
		res = hardware->SetPlayoutDevice(pd);
		VALIDATE;
		printf("Select recording device: ");
		scanf("%d", &rd);
		printf("Setting sound devices \n");
		res = hardware->SetRecordingDevice(rd);
		VALIDATE;

		res = codec->SetVADStatus(0, enable_cng);
		VALIDATE;

		res = apm->SetAgcStatus(enable_agc);
		VALIDATE;

		res = apm->SetEcStatus(enable_aec);
		VALIDATE;

		res = apm->SetNsStatus(enable_ns);
		VALIDATE;

		printf("\n1. Send, listen and playout \n");
		printf("2. Send only \n");
		printf("3. Listen and playout only \n");
		printf("Select transfer mode: ");
		int call_selection;
		scanf("%i", &call_selection);
		const bool send = !(call_selection == 3);
		const bool receive = !(call_selection == 2);

		if (receive) {
#ifndef EXTERNAL_TRANSPORT
			printf("Start Listen \n");
			res = base1->StartReceive(chan);
			VALIDATE;
#endif

			printf("Start Playout \n");
			res = base1->StartPlayout(chan);
			VALIDATE;
		}

		if (send) {
			printf("Start Send \n");
			res = base1->StartSend(chan);
			VALIDATE;
		}

		printf("Getting mic volume \n");
		unsigned int vol = 999;
		res = volume->GetMicVolume(vol);
		VALIDATE;
		if ((vol > 255) || (vol < 1)) {
			printf("\n****ERROR in GetMicVolume");
		}

		int forever = 1;
		while (forever) {
			printf("\nSelect codec\n");
			PrintCodecs(opus_stereo);
			printf("\nOther actions\n");
			const int num_codecs = codec->NumOfCodecs();
			int option_index = num_codecs;
			printf("%i. Toggle CNG\n", option_index++);
			printf("%i. Toggle AGC\n", option_index++);
			printf("%i. Toggle NS\n", option_index++);
			printf("%i. Toggle experimental NS\n", option_index++);
			printf("%i. Toggle EC\n", option_index++);
			printf("%i. Select AEC\n", option_index++);
			printf("%i. Select AECM\n", option_index++);
			printf("%i. Get speaker volume\n", option_index++);
			printf("%i. Set speaker volume\n", option_index++);
			printf("%i. Get microphone volume\n", option_index++);
			printf("%i. Set microphone volume\n", option_index++);
			printf("%i. Play local file (audio_long16.pcm) \n", option_index++);
			printf("%i. Change playout device \n", option_index++);
			printf("%i. Change recording device \n", option_index++);
			printf("%i. Toggle receive-side AGC \n", option_index++);
			printf("%i. Toggle receive-side NS \n", option_index++);
			printf("%i. AGC status \n", option_index++);
			printf("%i. Toggle microphone mute \n", option_index++);
			printf("%i. Get last error code \n", option_index++);
			printf("%i. Toggle typing detection \n",
				option_index++);
			printf("%i. Record a PCM file \n", option_index++);
			printf("%i. Play a previously recorded PCM file locally \n",
				option_index++);
			printf("%i. Play a previously recorded PCM file as microphone \n",
				option_index++);
			printf("%i. Add an additional file-playing channel \n", option_index++);
			printf("%i. Remove a file-playing channel \n", option_index++);
			printf("%i. Toggle Opus stereo (Opus must be selected again to apply "
				"the setting) \n", option_index++);
			printf("%i. Set Opus maximum audio bandwidth \n", option_index++);
			printf("%i. Set bit rate (only take effect on codecs that allow the "
				"change) \n", option_index++);

			printf("Select action or %i to stop the call: ", option_index);
			int option_selection;
			scanf("%i", &option_selection);

			option_index = num_codecs;
			if (option_selection < option_index) {
				res = codec->GetCodec(option_selection, cinst);
				VALIDATE;
				SetStereoIfOpus(opus_stereo, &cinst);
				printf("Set primary codec\n");
				res = codec->SetSendCodec(chan, cinst);
				VALIDATE;
			}
			else if (option_selection == option_index++) {
				enable_cng = !enable_cng;
				res = codec->SetVADStatus(0, enable_cng);
				VALIDATE;
				if (enable_cng)
					printf("\n CNG is now on! \n");
				else
					printf("\n CNG is now off! \n");
			}
			else if (option_selection == option_index++) {
				enable_agc = !enable_agc;
				res = apm->SetAgcStatus(enable_agc);
				VALIDATE;
				if (enable_agc)
					printf("\n AGC is now on! \n");
				else
					printf("\n AGC is now off! \n");
			}
			else if (option_selection == option_index++) {
				enable_ns = !enable_ns;
				res = apm->SetNsStatus(enable_ns);
				VALIDATE;
				if (enable_ns)
					printf("\n NS is now on! \n");
				else
					printf("\n NS is now off! \n");
			}
			else if (option_selection == option_index++) {
				experimental_ns_enabled = !experimental_ns_enabled;
				Config config;
				config.Set<ExperimentalNs>(new ExperimentalNs(experimental_ns_enabled));
				base1->audio_processing()->SetExtraOptions(config);
				if (experimental_ns_enabled) {
					printf("\n Experimental NS is now on!\n");
				}
				else {
					printf("\n Experimental NS is now off!\n");
				}
			}
			else if (option_selection == option_index++) {
				enable_aec = !enable_aec;
				res = apm->SetEcStatus(enable_aec, kEcUnchanged);
				VALIDATE;
				if (enable_aec)
					printf("\n Echo control is now on! \n");
				else
					printf("\n Echo control is now off! \n");
			}
			else if (option_selection == option_index++) {
				res = apm->SetEcStatus(enable_aec, kEcAec);
				VALIDATE;
				printf("\n AEC selected! \n");
				if (enable_aec)
					printf(" (Echo control is on)\n");
				else
					printf(" (Echo control is off)\n");
			}
			else if (option_selection == option_index++) {
				res = apm->SetEcStatus(enable_aec, kEcAecm);
				VALIDATE;
				printf("\n AECM selected! \n");
				if (enable_aec)
					printf(" (Echo control is on)\n");
				else
					printf(" (Echo control is off)\n");
			}
			else if (option_selection == option_index++) {
				unsigned vol(0);
				res = volume->GetSpeakerVolume(vol);
				VALIDATE;
				printf("\n Speaker Volume is %d \n", vol);
			}
			else if (option_selection == option_index++) {
				printf("Level: ");
				int level;
				scanf("%i", &level);
				res = volume->SetSpeakerVolume(level);
				VALIDATE;
			}
			else if (option_selection == option_index++) {
				unsigned vol(0);
				res = volume->GetMicVolume(vol);
				VALIDATE;
				printf("\n Microphone Volume is %d \n", vol);
			}
			else if (option_selection == option_index++) {
				printf("Level: ");
				int level;
				scanf("%i", &level);
				res = volume->SetMicVolume(level);
				VALIDATE;
			}
			else if (option_selection == option_index++) {
				res = file->StartPlayingFileLocally(0, audio_filename.c_str());
				VALIDATE;
			}
			else if (option_selection == option_index++) {
				// change the playout device with current call
				int num_pd(-1);
				res = hardware->GetNumOfPlayoutDevices(num_pd);
				VALIDATE;

				char dn[128] = { 0 };
				char guid[128] = { 0 };

				printf("\nPlayout devices (%d): \n", num_pd);
				for (int i = 0; i < num_pd; ++i) {
					res = hardware->GetPlayoutDeviceName(i, dn, guid);
					VALIDATE;
					printf("  %d: %s \n", i, dn);
				}
				printf("Select playout device: ");
				scanf("%d", &num_pd);
				// Will use plughw for hardware devices
				res = hardware->SetPlayoutDevice(num_pd);
				VALIDATE;
			}
			else if (option_selection == option_index++) {
				// change the recording device with current call
				int num_rd(-1);

				res = hardware->GetNumOfRecordingDevices(num_rd);
				VALIDATE;

				char dn[128] = { 0 };
				char guid[128] = { 0 };

				printf("Recording devices (%d): \n", num_rd);
				for (int i = 0; i < num_rd; ++i) {
					res = hardware->GetRecordingDeviceName(i, dn, guid);
					VALIDATE;
					printf("  %d: %s \n", i, dn);
				}

				printf("Select recording device: ");
				scanf("%d", &num_rd);
				printf("Setting sound devices \n");
				// Will use plughw for hardware devices
				res = hardware->SetRecordingDevice(num_rd);
				VALIDATE;
			}
			else if (option_selection == option_index++) {
				// Remote AGC
				enable_rx_agc = !enable_rx_agc;
				res = apm->SetRxAgcStatus(chan, enable_rx_agc);
				VALIDATE;
				if (enable_rx_agc)
					printf("\n Receive-side AGC is now on! \n");
				else
					printf("\n Receive-side AGC is now off! \n");
			}
			else if (option_selection == option_index++) {
				// Remote NS
				enable_rx_ns = !enable_rx_ns;
				res = apm->SetRxNsStatus(chan, enable_rx_ns);
				VALIDATE;
				if (enable_rx_ns)
					printf("\n Receive-side NS is now on! \n");
				else
					printf("\n Receive-side NS is now off! \n");
			}
			else if (option_selection == option_index++) {
				AgcModes agcmode;
				bool enable;
				res = apm->GetAgcStatus(enable, agcmode);
				VALIDATE
					printf("\n AGC enable is %d, mode is %d \n", enable, agcmode);
			}
			else if (option_selection == option_index++) {
				// Toggle Mute on Microphone
				res = volume->GetInputMute(chan, muted);
				VALIDATE;
				muted = !muted;
				res = volume->SetInputMute(chan, muted);
				VALIDATE;
				if (muted)
					printf("\n Microphone is now on mute! \n");
				else
					printf("\n Microphone is no longer on mute! \n");
			}
			else if (option_selection == option_index++) {
				// Get the last error code and print to screen
				int err_code = 0;
				err_code = base1->LastError();
				if (err_code != -1)
					printf("\n The last error code was %i.\n", err_code);
			}
			else if (option_selection == option_index++) {
				typing_detection = !typing_detection;
				res = apm->SetTypingDetectionStatus(typing_detection);
				VALIDATE;
				if (typing_detection)
					printf("\n Typing detection is now on!\n");
				else
					printf("\n Typing detection is now off!\n");
			}
			else if (option_selection == option_index++) {
				int stop_record = 1;
				int file_source = 1;
				printf("\n Select source of recorded file. ");
				printf("\n 1. Record from microphone to file ");
				printf("\n 2. Record from playout to file ");
				printf("\n Enter your selection: \n");
				scanf("%i", &file_source);
				if (file_source == 1) {
					printf("\n Start recording microphone as %s \n",
						mic_filename.c_str());
					res = file->StartRecordingMicrophone(mic_filename.c_str());
					VALIDATE;
				}
				else {
					printf("\n Start recording playout as %s \n", play_filename.c_str());
					res = file->StartRecordingPlayout(chan, play_filename.c_str());
					VALIDATE;
				}
				while (stop_record != 0) {
					printf("\n Type 0 to stop recording file \n");
					scanf("%i", &stop_record);
				}
				if (file_source == 1) {
					res = file->StopRecordingMicrophone();
					VALIDATE;
				}
				else {
					res = file->StopRecordingPlayout(chan);
					VALIDATE;
				}
				printf("\n File finished recording \n");
			}
			else if (option_selection == option_index++) {
				int file_type = 1;
				int stop_play = 1;
				printf("\n Select a file to play locally in a loop.");
				printf("\n 1. Play %s", mic_filename.c_str());
				printf("\n 2. Play %s", play_filename.c_str());
				printf("\n Enter your selection\n");
				scanf("%i", &file_type);
				if (file_type == 1)  {
					printf("\n Start playing %s locally in a loop\n",
						mic_filename.c_str());
					res = file->StartPlayingFileLocally(chan, mic_filename.c_str(), true);
					VALIDATE;
				}
				else {
					printf("\n Start playing %s locally in a loop\n",
						play_filename.c_str());
					res = file->StartPlayingFileLocally(chan, play_filename.c_str(),
						true);
					VALIDATE;
				}
				while (stop_play != 0) {
					printf("\n Type 0 to stop playing file\n");
					scanf("%i", &stop_play);
				}
				res = file->StopPlayingFileLocally(chan);
				VALIDATE;
			}
			else if (option_selection == option_index++) {
				int file_type = 1;
				int stop_play = 1;
				printf("\n Select a file to play as microphone in a loop.");
				printf("\n 1. Play %s", mic_filename.c_str());
				printf("\n 2. Play %s", play_filename.c_str());
				printf("\n Enter your selection\n");
				scanf("%i", &file_type);
				if (file_type == 1)  {
					printf("\n Start playing %s as mic in a loop\n",
						mic_filename.c_str());
					res = file->StartPlayingFileAsMicrophone(chan, mic_filename.c_str(),
						true);
					VALIDATE;
				}
				else {
					printf("\n Start playing %s as mic in a loop\n",
						play_filename.c_str());
					res = file->StartPlayingFileAsMicrophone(chan, play_filename.c_str(),
						true);
					VALIDATE;
				}
				while (stop_play != 0) {
					printf("\n Type 0 to stop playing file\n");
					scanf("%i", &stop_play);
				}
				res = file->StopPlayingFileAsMicrophone(chan);
				VALIDATE;
			}
			else if (option_selection == option_index++) {
				if (channel_index < kMaxNumChannels) {
					res = base1->StartReceive(channels[channel_index]);
					VALIDATE;
					res = base1->StartPlayout(channels[channel_index]);
					VALIDATE;
					res = base1->StartSend(channels[channel_index]);
					VALIDATE;
					res = file->StartPlayingFileAsMicrophone(channels[channel_index],
						audio_filename.c_str(),
						true,
						false);
					VALIDATE;
					channel_index++;
					printf("Using %d additional channels\n", channel_index);
				}
				else {
					printf("Max number of channels reached\n");
				}
			}
			else if (option_selection == option_index++) {
				if (channel_index > 0) {
					channel_index--;
					res = file->StopPlayingFileAsMicrophone(channels[channel_index]);
					VALIDATE;
					res = base1->StopSend(channels[channel_index]);
					VALIDATE;
					res = base1->StopPlayout(channels[channel_index]);
					VALIDATE;
					res = base1->StopReceive(channels[channel_index]);
					VALIDATE;
					printf("Using %d additional channels\n", channel_index);
				}
				else {
					printf("All additional channels stopped\n");
				}
			}
			else if (option_selection == option_index++) {
				opus_stereo = !opus_stereo;
				if (opus_stereo)
					printf("\n Opus stereo enabled (select Opus again to apply the "
					"setting). \n");
				else
					printf("\n Opus mono enabled (select Opus again to apply the "
					"setting). \n");
			}
			else if (option_selection == option_index++) {
				printf("\n Input bandwidth in Hz: ");
				int max_playback_rate;
				scanf("%i", &max_playback_rate);
				res = codec->SetOpusMaxBandwidth(chan, max_playback_rate);
				VALIDATE;
			}
			else if (option_selection == option_index++) {
				res = codec->GetSendCodec(chan, cinst);
				VALIDATE;
				printf("Current bit rate is %i bps, set to: ", cinst.rate);
				scanf("%i", &cinst.rate);
				res = codec->SetSendCodec(chan, cinst);
				VALIDATE;
			}
			else {
				break;
			}
		}

		if (send) {
			printf("Stop Send \n");
			res = base1->StopSend(chan);
			VALIDATE;
		}

		if (receive) {
			printf("Stop Playout \n");
			res = base1->StopPlayout(chan);
			VALIDATE;

#ifndef EXTERNAL_TRANSPORT
			printf("Stop Listen \n");
			res = base1->StopReceive(chan);
			VALIDATE;
#endif
		}

		while (channel_index > 0) {
			--channel_index;
			res = file->StopPlayingFileAsMicrophone(channels[channel_index]);
			VALIDATE;
			res = base1->StopSend(channels[channel_index]);
			VALIDATE;
			res = base1->StopPlayout(channels[channel_index]);
			VALIDATE;
			res = base1->StopReceive(channels[channel_index]);
			VALIDATE;
		}

		printf("\n1. New call \n");
		printf("2. Quit \n");
		printf("Select action: ");
		int end_option;
		scanf("%i", &end_option);
		newcall = (end_option == 1);
		// Call loop
	}
	for (int i = 0; i < kMaxNumChannels; ++i) {
		delete voice_channel_transports[i];
		voice_channel_transports[i] = NULL;
	}

	printf("Delete channels \n");
	res = base1->DeleteChannel(chan);
	VALIDATE;

	for (int i = 0; i < kMaxNumChannels; ++i) {
		channels[i] = base1->DeleteChannel(channels[i]);
		VALIDATE;
	}
}
*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <unistd.h>
#endif

#include <vector>
#include <process.h>
#include "CUDP.h"
#include "CVoiceModuleBase.h"
int main(int argc, char** argv) {
	//	google::ParseCommandLineFlags(&argc, &argv, true);
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	BOOL bServer = TRUE;
	HINSTANCE hDll = NULL;
	if (bServer)
	{
		hDll = LoadLibrary(L"E:\\WebRtcDemo\\VolCtrl\\Debug\\VolCtrl.dll");
	}
	else
	{
		hDll = LoadLibrary(L"VolCtrl.dll");
	}
	if (!hDll)
		return -1;
	printf("LoadLibrary Successed!!!\n");
	typedef CVoiceModuleBase* (*pGetVoiceModule)();
	typedef CMyRecorderBase* (*pGetRecorderBase)(GUID &guidDev, HANDLE hEvent, BOOL bRender);
	pGetRecorderBase GetRecorderBase = (pGetRecorderBase)GetProcAddress(hDll, "GetRecorderObject");
	GUID guidTemp = GUID_NULL;
	CMyRecorderBase *myRecorderBase = GetRecorderBase(guidTemp, NULL, FALSE);
	int iSum = myRecorderBase->AddTest(5, 6);

	pGetVoiceModule GetVoiceModuleFun = (pGetVoiceModule)GetProcAddress(hDll, "GetVoiceModule");
	if (!GetVoiceModuleFun)
		return -1;
	GUID guidDev2 = { 0xD54640C6, 0x7D41, 0x4D3B, { 0xB3, 0x74, 0x87, 0x28, 0xF7, 0x19, 0x72, 0x71 } };			//Ren
	GUID guidDev = { 0xB5A9CDA2, 0x1C84, 0x4891, { 0xB0, 0x4E, 0x8B, 0x4A, 0x5C, 0x7D, 0x56, 0x38 } };	//Cap
	CVoiceModuleBase *voiceModule = NULL;
	voiceModule = GetVoiceModuleFun();
	int iRet = voiceModule->AddTest(5, 6);
	
	BOOL bRet = voiceModule->Init(guidDev, guidDev2, FALSE, bServer);
	bServer = TRUE;
	IN_ADDR inAddrTemp;
	inAddrTemp.S_un.S_addr = 436054208;// inet_addr("224.2.2.222") + 1;
	char *chIp = inet_ntoa(inAddrTemp);
	if (bServer)
	{
		bRet = voiceModule->InitTranParams(0, inet_addr("227.33.144.22"), 1222, TRUE, bServer);
		int iCount = 0;
		bRet = voiceModule->GetRecCount(iCount);
		bRet = voiceModule->Start(0x07, 1);
		bRet = voiceModule->Start(0x01, 0);
	}
	else
	{
		bRet = voiceModule->InitTranParams(inet_addr("192.168.0.100"), inet_addr("227.33.144.22"), 1222, TRUE, bServer);
		bRet = voiceModule->Start(0x06, 1);
		bRet = voiceModule->Start(0x07, 0);
	}
	while (TRUE)
	{
		SleepEx(10, FALSE);
	}
	bRet = voiceModule->Stop(0x07, 0);
	bRet = voiceModule->Stop(0x07, 0);
	CoUninitialize();
	FreeLibrary(hDll);
	return 0;
}
*/