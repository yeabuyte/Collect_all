/*******************************************************************
*@filename:     log_stdout.h
*@author:       zxj
*@date:         2018/6/19 16:27
*@about:		控制台输出日志
********************************************************************/

#ifndef _LOGSTDOUTLOG_H_
#define _LOGSTDOUTLOG_H_

#include <iostream>
#include "logging.h"
#include "../common/common.h"
#include "../common/mutex.h"

namespace baseCollect {

class LogStdout
{
public:
	explicit LogStdout(const string& basename);
	~LogStdout();

	void append(const string &message);
	
private:
	Mutex _mutex;
	const string _basename;
};

} // namespace thefox

void SET_LOG_STDOUT(const baseCollect::string &basename = "");

#endif // _THEFOX_LOGSYSLOG_H_
