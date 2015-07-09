/*
**Copyright (c) 2013 Calvin Cheung. All Rights Reserved.
**
**Use of this source code is governed by a BSD-style license.
**
**This is a simple wrapper for WebRTC. I used it in the Video Conference project.
**You just need this file , lib file , and dll file in the root folder.
**URL:https://github.com/calvingit/WebRTC_Wrapper/
**
**File: LoganVoiceEngine.h
**
**Author: Calvin Cheung, Chinna.
**
**Update Date: 2013-5-21
*/

#ifndef __LOGAN_VOICE_ENGINE_H__
#define __LOGAN_VOICE_ENGINE_H__

#define LOGAN_API_EXPORTS

#ifdef LOGAN_API_EXPORTS
#define LOGAN_API  __declspec(dllexport)
#else
#define LOGAN_API __declspec(dllimport)
#endif


// �������ṹ��. Each codec supported can be described by this structure.
struct LoganCodec
{
    int pltype;
    char plname[32];
    int plfreq;
    int pacsize;
    int channels;
    int rate;
};


/*
**������Ļص�����,һ��һд
*/
//read stream data from net or file
typedef int  (__stdcall *LoganReadStreamCallBack)(void *buf,int len);
//write stream data to net or file
typedef bool (__stdcall *LoganWriteStreamCallBack)(const void *buf,int len);


class LOGAN_API LoganVoiceEngine
{
protected:
    ~LoganVoiceEngine(){}

public:

    //���к���֮ǰʹ��. Called firest to create an object.
    static LoganVoiceEngine *Create();

    //����һ��ͨ��ID��������������(Ŀǰֻ��һ��),���������������й�
    //You must create one channel at least. If you have N network connections,
    //then create N channels.
    virtual int LoganVoe_CreateChannel() = 0;

    /************************************************************************/
    /* ���紫��(NOT SURPPORTED NOW)                                        */
    /************************************************************************/
    //������������(��ʱδ��)
    virtual int LoganVoe_SetSendDestination(int channelId, const char* ip, int port) = 0;
    virtual int LoganVoe_SetLocalReceiver(int channelId, int port) = 0;


    /************************************************************************/
    /* ������(Codec)                                                       */
    /************************************************************************/
    //��ȡ�����������Ŀ
    virtual int LoganVoe_GetNumsOfCodec() = 0;

    //��ȡָ�������ı������
    virtual int LoganVoe_GetSpecCodec(int index, LoganCodec &lc) = 0;

    //����ָ��ͨ���ı�����
    virtual int LoganVoe_SetSendCodec(int channelid, LoganCodec lc) = 0;



    /************************************************************************/
    /* �豸����                                                      */
    /*(ע��name��guid����UTF8��, ��Ҫת, Ӣ�ĵĻ�1�ֽڣ���������2�ֽ�)  */
    /************************************************************************/
    //��ȡ¼���豸����Ŀ
    virtual int LoganVoe_GetNumOfRecordingDevices() = 0;

    //��ȡ�����豸����Ŀ
    virtual int LoganVoe_GetNumOfPlayoutDevices() = 0;

    //��ȡָ�������Ĳ����豸������
    virtual int LoganVoe_GetPlayoutDeviceName(int index, 
        char nameUTF8[128], char guidUTF8[128]) = 0;

    //��ȡָ��������¼���豸������
    virtual int LoganVoe_GetRecordingDeviceName(int index, 
        char nameUTF8[128], char guidUTF8[128]) = 0;

    //���ò����豸
    virtual int LoganVoe_SetPlayoutDevice(int idx) = 0;

    //����¼���豸
    virtual int LoganVoe_SetRecordingDevice(int idx) = 0;



    /************************************************************************/
    /*������������(��������, ��������, �Զ�����, �������)                                                                  */
    /************************************************************************/
    /*
    **vad: mode 
    **0: low
    **1:
    **2:
    **3: most high
    */
    virtual int LoganVoe_SetVADStatus(int channelsid, bool b, int mode = 1) = 0;
    /*
    **agc: mode 
    **0: previously set mode
    **1: platform default
    **2: adaptive mode for use when analog volume control exists (e.g. for PC softphone)
    **3: scaling takes place in the digital domain (e.g. for conference servers and embedded devices)
    **4: can be used on embedded devices where the capture signal level is predictable
    */
    virtual int LoganVoe_SetAgcStatus(bool b, int mode = 1) = 0;

    /*
    **EC mode
    **0: previously set mode
    **1: platform default
    **2: conferencing default (aggressive AEC)
    **3: Acoustic Echo Cancellation
    **4: AEC mobile
    */
    virtual int LoganVoe_SetEcStatus(bool b, int mode = 3) = 0;

    /*
    **NS mode
    **0: previously set mode
    **1: platform default
    **2: conferencing default
    **3: lowest suppression
    **4: Moderate Suppression
    **5: High Suppression
    **6: highest suppression
    */
    virtual int LoganVoe_SetNsStatus(bool b, int mode = 4) = 0;

    virtual int LoganVoe_GetVADStatus(int channelsid, bool &b, int &mode) = 0;
    virtual int LoganVoe_GetAgcStatus(bool &b, int &mode) = 0;
    virtual int LoganVoe_GetEcStatus(bool &b, int &mode) = 0;
    virtual int LoganVoe_GetNsStatus(bool &b, int &mode) = 0;

    /*
    ** �������ſ���, Start����������Stop��Ե���
    */
    // Starts forwarding the packets to the mixer/soundcard for a
    // specified |channel|.(Important: must be called before other playing action)
    virtual int LoganVoe_StartPlayout(int channelid) = 0;

    // Prepares and initiates the VoiceEngine for reception of
    // incoming RTP/RTCP packets on the specified |channel|.
    //NOT SUPPORT NOW
    virtual int LoganVoe_StartReceive(int channelid) = 0;

    // Starts sending packets to an already specified IP address and
    // port number for a specified |channel|.
    //NOT SUPPORT NOW
    virtual int LoganVoe_StartSend(int channelid) = 0;

    //NOT SUPPORT NOW
    virtual int LoganVoe_StopReceive(int channelid) = 0;

    //NOT SUPPORT NOW
    virtual int LoganVoe_StopPlayout(int channelid) = 0;

    //NOT SUPPORT NOW
    virtual int LoganVoe_StopSend(int channelid) = 0;


    /*
    **�ļ�����(File operations)
    */
    // Starts recording the microphone signal to a stream.
    //lwscb is a callback function to deal with data captured from hardware.
    virtual int LoganVoe_StartRecordingMicrophone(LoganWriteStreamCallBack lwscb) = 0;

    // Starts recording the microphone signal to a file.
    virtual int LoganVoe_StartRecordingMicrophone(const char* fileNameUTF8, 
        LoganCodec* codec = NULL) = 0;

    // Starts playing and mixing streams with the local speaker signal for playout.
    // lrscb is a callback function to deal with data received from network
    virtual int LoganVoe_StartPlayingFileLocally(int channelid, 
        LoganReadStreamCallBack lrscb) = 0;

    // Starts playing and mixing files with the local speaker signal for playout.
    virtual int LoganVoe_StartPlayingFileLocally(
        int channelid,
        const char fileNameUTF8[1024],
        int samplerate,//(8000, 16000, 32000)
        bool loop = false) = 0;

    // Returns the current file playing state for a specific |channel|.
    virtual int LoganVoe_IsPlayingFileLocally(int channel) = 0;

    // Starts reading data from a file and transmits the data either
    // mixed with or instead of the microphone signal.
    virtual int LoganVoe_StartPlayingFileAsMicrophone(
        int channel,
        const char fileNameUTF8[1024],
        int sampleRate,
        bool loop = false ,
        bool mixWithMicrophone = false) = 0;

    // Starts reading data from a stream and transmits the data either
    // mixed with or instead of the microphone signal.
    virtual int LoganVoe_StartPlayingFileAsMicrophone(
        int channel,
        LoganReadStreamCallBack read,
        int sampleRate,
        bool mixWithMicrophone = false) = 0;

    // Stops playing of a file as microphone signal for a specific |channel|.
    virtual int LoganVoe_StopPlayingFileAsMicrophone(int channel) = 0;

    // Returns whether the |channel| is currently playing a file as microphone.
    virtual int LoganVoe_IsPlayingFileAsMicrophone(int channel) = 0;

    // Starts recording the mixed playout audio to a file.
    virtual int LoganVoe_StartRecordingPlayout(int channel, const char* fileNameUTF8,
        LoganCodec *codec = NULL) = 0;

    // Stops playback of a file on a specific |channel|.
    virtual int LoganVoe_StopPlayingFileLocally(int channelid) = 0;

    // Stops recording the microphone signal.
    virtual int LoganVoe_StopRecordingMicrophone() = 0;

    // Stops recording the mixed playout audio.
    virtual int LoganVoe_StopRecordingPlayout(int channel) = 0;


    /*
    **��������(Volume control)
    */
    //Get Volume, Valid range is [0,255]
    virtual unsigned int LoganVoe_GetMicVolume() = 0;
    virtual unsigned int LoganVoe_GetSpeakerVolume() = 0;

    //Set Volume, Valid range is [0,255]
    virtual int LoganVoe_SetMicVolume(unsigned int vol) = 0;
    virtual int LoganVoe_SetSpeakerVolume(unsigned int vol) = 0;

    // Mutes the microphone input signal completely without affecting
    // the audio device volume.
    virtual int LoganVoe_SetInputMute(int channel, bool enable) = 0;

    // Gets the current microphone input mute state.
    virtual int LoganVoe_GetInputMute(int channel, bool& enabled) = 0;

    // Mutes the speaker device completely in the operating system.
    virtual int LoganVoe_SetSystemOutputMute(bool enable) = 0;

    // Gets the output device mute state in the operating system.
    virtual int LoganVoe_GetSystemOutputMute(bool &enabled) = 0;

    // Mutes the microphone device completely in the operating system.
    virtual int LoganVoe_SetSystemInputMute(bool enable) = 0;

    // Gets the mute state of the input device in the operating system.
    virtual int LoganVoe_GetSystemInputMute(bool& enabled) = 0;

    // Gets the microphone speech |level|, mapped non-linearly to the range
    // [0,9].(��Ƶ�źŷ���,�ö�ʱ�������ȡ)
    virtual int LoganVoe_GetSpeechInputLevel(unsigned int& level) = 0;

    // Gets the speaker speech |level|, mapped non-linearly to the range
    // [0,9].(��Ƶ�źŷ���,�ö�ʱ�������ȡ)
    virtual int LoganVoe_GetSpeechOutputLevel(int channel, unsigned int& level) = 0;



    //������ɾ�����ͨ��������
    //remember to delete channel.
    virtual int LoganVoe_DeleteChannel(int channel) = 0;
    virtual int LoganVoe_DeleteAllChannel() = 0;

    //���к���������ʹ��
    static void Destroy(LoganVoiceEngine* lve);
};


#endif //__LOGAN_VOICE_ENGINE_H__