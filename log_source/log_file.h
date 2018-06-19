/*******************************************************************
*@filename:     log_file.h
*@author:       zxj
*@date:         2018/6/19 17:35
*@about:		日志写入文件
********************************************************************/

#ifndef _LOGFILE_H_
#define _LOGFILE_H_

#ifdef WIN32
#else
#include <unistd.h>
#endif

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../common/common.h"
#include "../common/mutex.h"
#include "logging.h"

namespace baseCollect {

class LogFile
{
public:
	class File;
	DISALLOW_EVIL_CONSTRUCTORS(LogFile);
	LogFile(const string &dir, const string &basename, size_t rollSize);
	~LogFile();

	void init();
	void append(const string &message);
	void flush();

private:
	static string getLogFileName(const string &dir, const string& basename, time_t* now);
	void rollFile();

	string _dir;
	const string _basename;
	size_t _rollSize;
	
	Mutex _mutex;
	time_t _startOfPeriod;
	time_t _lastRoll;
	File *_file;

	static const int _kRollPerSeconds = 86400;
};

} // namespace baseCollect

void SET_LOG_FILE(const baseCollect::string &dir,
							const baseCollect::string &basename,
							size_t rollSize = 100*1024*1024);
#endif // _LOGFILE_H_
