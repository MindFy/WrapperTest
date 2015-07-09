class CVoiceModuleBase
{
public:
	virtual ~CVoiceModuleBase() {}
	virtual int AddTest(int a, int b) = 0; 
	virtual BOOL InitTranParams(DWORD dwIp, DWORD dwGroupIp, DWORD dwPort, BOOL bMultSend, BOOL bServer) = 0;
	virtual BOOL Init(GUID guidCap, GUID guidRen, BOOL bRender, BOOL bServer) = 0;
	virtual BOOL Start(DWORD dwFlag, int iChannel) = 0;
	virtual BOOL Stop(DWORD dwFlag, int iChannel) = 0;
	virtual BOOL GetRecCount(int &iCount) = 0;
// 	virtual void RegisterGetDataFun(/*pGetVoiceData pDataFun*/) = 0;
// 	virtual int SetRenderData(const uint8_t *payloadData, uint16_t payloadSize) = 0;
};

class CMyRecorderBase
{
public:
	virtual ~CMyRecorderBase(){};
	virtual BOOL InitCaptureDevice() = 0;
	virtual BOOL StartRecord() = 0;
	virtual BOOL StopRecord() = 0;
	virtual BOOL GetRecorderBuffer(BYTE *pBuff, UINT32 &buffLen, DWORD &dwFlags) = 0;
	virtual BOOL ReleaseBuffer(UINT32 numAvailable) = 0;
	virtual GUID GetGuid() = 0;
	virtual WAVEFORMATEX* GetWaveFormat() = 0;
	virtual BOOL SetWaveFormat(WAVEFORMATEX *pWfex) = 0;
	virtual BOOL GetBufferSize(UINT32 &buffSize) = 0;
	virtual BOOL GetNextPacketSize(UINT32 &packetSize) = 0;
	virtual BOOL GetDefaultGuid(GUID &guidDev, BOOL &bDefault) = 0;
	virtual BOOL GetRenderPosition(UINT64 &uintPos, UINT64 &uintQCPos) = 0;
	virtual BOOL GetStreamLatency(/*REFERENCE_TIME*/LONGLONG &latencyTime) = 0;
	virtual BOOL SetEndPointArgs(WAVEFORMATEX *pWfex) = 0;

	virtual BOOL InitRenderDevice() = 0;
	virtual BOOL StartRender() = 0;
	virtual BOOL StopRender() = 0;
	virtual BOOL SetRenderData(BYTE *pBuffer, UINT32 BufferLen) = 0;

	virtual BOOL SpeexStateInit(INT iFrameSum, INT iFilterLen, INT iSampleRate) = 0;
	virtual BOOL SpeexCancellation(short *pCapBuff, short *pFilterBuff, short *pOutBuff) = 0;
	virtual BOOL SpeexPlayBack(short *pPlayBuff) = 0;
	virtual BOOL SpeexCapture(short *pCapBuff, short *pOutBuff) = 0;
	virtual INT AddTest(INT a, INT b) = 0;
};