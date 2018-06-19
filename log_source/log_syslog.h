/**
* @file log_syslog.h
* @brief log to syslog server
* @ahthor macwe1024 at gmail dot com
*/

#ifndef _LOGSYSLOG_H_
#define _LOGSYSLOG_H_

#ifdef WIN32
#include <Winsock2.h>
#else
#include <sys/socket.h>
#define SOCKET int
#endif

#include "../common/common.h"
#include "../common/mutex.h"
#include "../log_source/log_stdout.h"
//#include <net/inet_address.h>

namespace baseCollect
{

class LogSyslog
{
public:
	LogSyslog(const string& basename, const net::InetAddress &serverAddr);
	~LogSyslog();

	void append(const string &message);
	bool init();
	
private:
	THEFOX_DISALLOW_EVIL_CONSTRUCTORS(LogSyslog);

	const string _basename;
	net::InetAddress _serverAddr;
	SOCKET _sockfd;
	Mutex _mutex;
};

} // namespace thefox

void THEFOX_SET_LOG_SYSLOG(const string& basename, const net::InetAddress &serverAddr);

#endif // _THEFOX_LOGSYSLOG_H_
