#include "log_syslog.h"
#include "../net/socket.h"

using namespace baseCollect;

static LogSyslog *g_logSyslog = NULL;

void SET_LOG_SYSLOG(const string& basename, const net::InetAddress &serverAddr)
{
	if (g_logSyslog) {
		delete g_logSyslog;
		g_logSyslog = NULL;
	}
	g_logSyslog = new LogSyslog(basename, serverAddr);
}

void logSyslogAppend(const string &message)
{
	if (g_logSyslog) {
		g_logSyslog->append(message);
	}
}

LogSyslog::LogSyslog(const string& basename, const net::InetAddress &serverAddr)
	: _basename(basename)
	, _serverAddr(serverAddr)

{
	SOCKET_STARTUP;
	init();
	thefoxSetLogHandler(logSyslogAppend);
}

LogSyslog::~LogSyslog()
{
	closesocket(_sockfd);
	SOCKET_CLEANUP;
}

void LogSyslog::append(const string &message)
{
	MutexGuard lock(_mutex);
	if (_sockfd >= 0) {
		int rtn = ::sendto(_sockfd, message.c_str(), message.length(), 0,
			(struct sockaddr *)&_serverAddr.getSockAddrInet(),
			sizeof(struct sockaddr_in));
		int a = rtn;
	}
}

bool LogSyslog::init()
{
	_sockfd = ::socket(PF_INET, SOCK_DGRAM, 0);
	return _sockfd >= 0;
}