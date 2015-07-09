
#include <stdio.h>
#include <stdlib.h>
#include <WINSOCK2.H>
#pragma comment(lib, "ws2_32.lib") 
#include <WS2TCPIP.H>

#include "CUDP.h"

CUDP::CUDP()
:m_bIsConnect(false)
,m_bSender(false) {
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		printf("WSAStartup Error!!!\n");
	}
}


CUDP::~CUDP() {
	DisConnect();
	WSACleanup();
}

void CUDP::DisConnect() {
    if (m_bIsConnect) {
        closesocket(m_nSock);
        m_bIsConnect = false;
    }
}

bool CUDP::Config(size_t szPort, char* pAddr, bool bSender) {
    assert(!m_bIsConnect);

    memset(&m_stSock, 0, sizeof(m_stSock));
    m_stSock.sin_family = AF_INET;
    m_stSock.sin_port = htons(szPort);
    if (bSender) {
        m_stSock.sin_addr.s_addr = inet_addr(pAddr);
    } else {
        m_stSock.sin_addr.s_addr = INADDR_ANY;
    }

    m_nSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_nSock < 0) {
        perror("create sock failed");
        return false;
    }

    if (!bSender) {
        if (bind(m_nSock, (struct sockaddr*)&m_stSock, sizeof(m_stSock))) {
            perror("bind sock error");
            closesocket(m_nSock);
            return false;
        }
    }
    m_bSender = bSender;
    m_bIsConnect = true;
    return true;
}

bool CUDP::SendUdp(unsigned char* message, short len) {
    assert(m_bSender);
    assert(m_bIsConnect);

   unsigned char header[2] = {0};
    header[0] = (len & 0xFF00)>>8;
    header[1] = len & 0xFF;

    size_t sz = sizeof(m_stSock);
    int ret = sendto(m_nSock, (char *)header, 2, 0, (struct sockaddr *)&m_stSock, sz);
    if (ret != 2) {
        perror("send udp message failed");
        closesocket(m_nSock);
        m_bIsConnect = false;
        return false;
    }

    ret = sendto(m_nSock, (char *)message, len, 0, (struct sockaddr *)&m_stSock, sz);
    if (ret != len) {
        perror("send udp message failed");
        closesocket(m_nSock);
        m_bIsConnect = false;
        return false;
    }
    return true;
}

bool CUDP::RecvUdp(unsigned char* &buff, int &buffLen) {
    assert(!m_bSender);
    assert(m_bIsConnect);
    assert(buff == NULL);

    int uLocal = sizeof(m_stSock);
    unsigned char header[2] = {0};
    int ret = recvfrom(m_nSock, (char *)header, 2, 0, (struct sockaddr*)&m_stSock, &uLocal);
    if (ret < 0) {
		TCHAR szBuf[128];
		LPVOID lpMsgBuf;
		DWORD dw = GetLastError();
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);

// 		wsprintf(szBuf,
// 			("%s 出错信息 (出错码=%d): %s"),
// 			"CreateCaptureBuffer...", dw, lpMsgBuf);
// 		LocalFree(lpMsgBuf);
// 		printf("Error Message: %s\n", szBuf);

        printf("recv message error\n");
        closesocket(m_nSock);
        m_bIsConnect = false;
        return false;
    }
    short len = ((header[0] << 8) & 0xFF00) | header[1];
//	short len = 160;
    buff = reinterpret_cast<unsigned char *>(calloc(1, len + 1));
    ret = recvfrom(m_nSock, (char *)buff, len, 0, (struct sockaddr*)&m_stSock, &uLocal);
	buffLen = len;
    if (ret < 0) {
        perror("recv message error");
        closesocket(m_nSock);
        m_bIsConnect = false;
        return false;
    }
	*(buff + len) = '\0';
    return true;
}

