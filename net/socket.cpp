#include "socket.h"
#include "../log_source/logging.h"
#include "inet_address.h"

#ifdef WIN32
    #define socklen_t int
#else
	#include <unistd.h>
	#include <fcntl.h>
	#include <netinet/tcp.h>
	#include <sys/types.h>
	#include <sys/socket.h>
#endif

#pragma comment(lib, "Ws2_32.lib")

using namespace baseCollect;
using namespace baseCollect::net;

Socket::Socket(SOCKET sockfd)
	: _sockfd(sockfd)
{
	BASECOLLECT_TRACE_FUNCTION;
}

Socket::~Socket()
{
	BASECOLLECT_TRACE_FUNCTION;

	Socket::close(_sockfd);
}

InetAddress Socket::getLocalAddr(SOCKET sockfd)
{
	BASECOLLECT_TRACE_FUNCTION;

	struct sockaddr_in localaddr;
	memset(&localaddr, 0, sizeof(localaddr));
    socklen_t addrlen = static_cast<socklen_t>(sizeof(localaddr));
    if (::getsockname(sockfd, (sockaddr *)&localaddr, &addrlen) < 0) {
#ifdef WIN32
        int errCode = ::WSAGetLastError();
		BASECOLLECT_LOG(LOGLEVEL_ERROR) << "getsockname() failed, errcode:" << errCode;
#else
		BASECOLLECT_LOG(LOGLEVEL_ERROR) << "getsockname() failed";
#endif
    }
	return localaddr;
}

SOCKET Socket::create()
{
	BASECOLLECT_TRACE_FUNCTION;

	SOCKET sockfd = INVALID_SOCKET;
#ifdef WIN32
	sockfd = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == sockfd) {
        int errCode = ::WSAGetLastError();
        BASECOLLECT_LOG(LOGLEVEL_ERROR) << "WSASocket failed, errcode:"<< errCode;
    }
#else
	sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == sockfd) {
		BASECOLLECT_LOG(LOGLEVEL_ERROR) << "create socket failed";
	}
#endif
	return sockfd;
}

bool Socket::setNonBlock(SOCKET sockfd)
{
#ifndef WIN32
	int flags = 0;
	if ((flags = ::fcntl(sockfd, F_GETFL, 0)) != -1) {
		flags |= O_NONBLOCK;
		if (::fcntl(sockfd, F_SETFL, flags) != -1) { // set non-blocking
			return true;
		}
	}
	return false;
#else
	return true;
#endif
}

bool Socket::connect(SOCKET sockfd, const InetAddress &serverAddr)
{
	BASECOLLECT_TRACE_FUNCTION << "sockfd=" << sockfd << "server:" << serverAddr.toIpPort();
	int ret = ::connect(sockfd, 
                      (struct sockaddr *)&serverAddr.getSockAddrInet(), 
                      sizeof(struct sockaddr_in));

    if (INVALID_SOCKET == ret  
#ifdef WIN32
		&& WSAEWOULDBLOCK != ::WSAGetLastError()
#endif
		) {
		BASECOLLECT_LOG(LOGLEVEL_ERROR) << "server connection failed, addr="<< serverAddr.toIpPort();
        
		return false;
	}
	return true;
}

bool Socket::close(SOCKET sockfd)
{
	BASECOLLECT_TRACE_FUNCTION << "sockfd=" << sockfd;

	if (INVALID_SOCKET != sockfd) {
#ifdef WIN32
		::shutdown(sockfd, SD_BOTH);
		if (SOCKET_ERROR == ::closesocket(sockfd)) {
#else
		::shutdown(sockfd, SHUT_RDWR);
		if (-1 == ::close(sockfd)) {
#endif
			return false;
		}
		sockfd = INVALID_SOCKET;
	}
	return true;
}

bool Socket::bind(const InetAddress &listenAddr)
{
	BASECOLLECT_TRACE_FUNCTION;

	int ret = ::bind(_sockfd, (struct sockaddr *)&listenAddr.getSockAddrInet(), sizeof(struct sockaddr_in));
    
	if (SOCKET_ERROR == ret) {
#ifdef WIN32
        int errCode = ::WSAGetLastError();
        BASECOLLECT_LOG(LOGLEVEL_ERROR) << "socket bind failed, errcode:"<< errCode;
#else
		BASECOLLECT_LOG(LOGLEVEL_ERROR) << "socket bind failed";
#endif
        Socket::close(_sockfd);
        return false;
    }
	return true;
}

bool Socket::listen()
{
	BASECOLLECT_TRACE_FUNCTION;
	int ret = ::listen(_sockfd, SOMAXCONN);
    if (SOCKET_ERROR == ret) {
#ifdef WIN32
        int errCode = ::WSAGetLastError();
        BASECOLLECT_LOG(LOGLEVEL_ERROR) << "socket listen failed, errcode:"<< errCode;
#else
		BASECOLLECT_LOG(LOGLEVEL_ERROR) << "socket listen failed";
#endif
        Socket::close(_sockfd);
        return false;
    }
	return true;
}

SOCKET Socket::accept(InetAddress *peerAddr)
{
	BASECOLLECT_TRACE_FUNCTION;

	SOCKET clientSockfd = INVALID_SOCKET;
	struct sockaddr_in addr;
    socklen_t len = static_cast<socklen_t>(sizeof(addr));
#ifdef WIN32
    clientSockfd = ::WSAAccept(_sockfd, (sockaddr *)&addr, &len, 0, 0);
#else
	clientSockfd = ::accept(_sockfd, (sockaddr *)&addr, &len);
#endif
	if (INVALID_SOCKET == clientSockfd) {
		BASECOLLECT_LOG(LOGLEVEL_ERROR) << "accept socket failed";
	} else {
		peerAddr->setSockAddrInet(addr);
	}
	return clientSockfd;
}

bool Socket::shutdownWrite()
{
	BASECOLLECT_TRACE_FUNCTION;

#ifdef WIN32
	if (SOCKET_ERROR == ::shutdown(_sockfd, SD_SEND)) {
#else
	if (-1 == ::shutdown(_sockfd, SHUT_WR)) {
#endif
		return false;
	}
	return true;
}

void Socket::setTcpNoDelay(bool on)
{
	BASECOLLECT_TRACE_FUNCTION << "on=" << on;

	char optval = on ? 1 : 0;
	::setsockopt(_sockfd, SOL_SOCKET, TCP_NODELAY,
               &optval, static_cast<socklen_t>(sizeof optval));
}

void Socket::setKeepAlive(bool on)
{
	BASECOLLECT_TRACE_FUNCTION << "on=" << on;

	char optval = on ? 1 : 0;
	::setsockopt(_sockfd, SOL_SOCKET, SO_KEEPALIVE,
               &optval, static_cast<socklen_t>(sizeof optval));
}
