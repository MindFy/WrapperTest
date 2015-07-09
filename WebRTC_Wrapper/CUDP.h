
#ifndef __CUDP_H__
#define __CUDP_H__

#include <stdio.h>
#include <stdlib.h>
#include <WINSOCK2.H>
#pragma comment(lib, "ws2_32.lib") 
#include <WS2TCPIP.H>
#include <assert.h>
#include <atlbase.h>
#include <tchar.h>

class CUDP {
public:
    CUDP();
    virtual ~CUDP();

    bool Config(size_t szPort, char* pAddr, bool bSender = true);
    bool SendUdp(unsigned char * msg, short len);
    bool RecvUdp(unsigned char * &buff, int &buffLen);
    void DisConnect();

private:
    struct sockaddr_in m_stSock;
    int m_nSock;
    bool m_bSender;
    bool m_bIsConnect;

};


#endif //__CUDP_H__
