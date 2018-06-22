/*******************************************************************
*@filename:     log_syslog.h
*@author:       zxj
*@date:         2018/6/22 14:51
*@about:		log to syslog server
********************************************************************/

#ifndef _LOGSYSLOG_H_
#define _LOGSYSLOG_H_

#ifdef WIN32
#include <Winsock2.h>
#else
#include <sys/socket.h>
#define SOCKET int
#endif
#include <string>
#include "../common/common.h"
#include "../common/mutex.h"
#include "../log_source/logging.h"
#include "../net/inet_address.h"


namespace baseCollect
{
class LogSyslog
{
public:
	DISALLOW_EVIL_CONSTRUCTORS(LogSyslog);
	LogSyslog(const std::string& basename, const net::InetAddress &serverAddr);
	~LogSyslog();

	void append(const std::string &message);
	bool init();
	
private:
	const std::string _basename;
	net::InetAddress _serverAddr;
	SOCKET _sockfd;
	Mutex _mutex;
};

} // namespace baseCollect

void SET_LOG_SYSLOG(const std::string& basename, const baseCollect::net::InetAddress &serverAddr);

#endif // _THEFOX_LOGSYSLOG_H_
