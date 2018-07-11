#ifndef __LOGGER_H_
#define __LOGGER_H_

#include "../../common/singleton.h"
#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdarg.h>
#include "../../common/mem_pool.h"
#include <string>
#include <chrono>
#include <thread>
#include <memory>
#include <fstream>
#include <mutex>
#include <condition_variable>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
// 线程安全
class Log
{
	static const unsigned int _SIZE = 1024;
	enum Priority :unsigned char
	{
		PRIO_FATAL = 1,
		PRIO_CRITICAL,
		PRIO_ERROR,
		PRIO_WARNING,
		PRIO_NOTICE,
		PRIO_INFORMATION,
		PRIO_DEBUG,
		PRIO_TRACE
	};
public:
	Log();
	~Log();
	Log(const Log&) = delete;
	Log& operator= (const Log&) = delete;

public:
	void fatal(char* msg, const char* file, int line);
	void critical(char* msg, const char* file, int line);
	void error(char* msg, const char* file, int line);
	void warning(char* msg, const char* file, int line);
	void notice(char* msg, const char* file, int line);
	void information(char* msg, const char* file, int line);
	void debug(char* msg, const char* file, int line);
	void trace(char* msg, const char* file, int line);

public:
	void init();
	char *format_log(char *format, ...);
	std::string get_file_name(const char* path_file_name);

private:
	void write(char *msg, Priority prio, const char* file, int line);
	void output_log();
	void read_log();

private:
	std::string get_log_name();
private:
	bool				_is_running;
	std::ofstream		_log_file;
    baseCollect::MemPool<char>	_pool;

	std::unique_ptr<std::thread>	_thread_ptr;
	std::queue<char *>				_work_queue;

	std::mutex					_mutex;
	std::condition_variable		_cv;
	bool						_cv_flag;

	std::chrono::time_point<std::chrono::system_clock>	m_nextDay;

private:
#ifdef _WIN32
	HANDLE	m_hStdHandle;
#endif
};

#define __G_LOGGER__\
	baseCollect::singleton<Log>::instance()

#define __FORMAT__( fmt, ... )\
	baseCollect::singleton<Log>::instance().format_log(fmt, ##__VA_ARGS__)

#define __FILE_NAME__\
	__G_LOGGER__.get_file_name(__FILE__).c_str()

#ifdef _DEBUG
#define debug_log(fmt, ...)\
	__G_LOGGER__.debug(__FORMAT__(fmt, ##__VA_ARGS__), __FILE_NAME__, __LINE__)
#define trace_log( fmt, ... )\
	__G_LOGGER__.trace(__FORMAT__(fmt, ##__VA_ARGS__), __FILE_NAME__, __LINE__)
#else
#define debug_log(fmt, ...)
#define trace_log(fmt, ...)
#endif



#define fatal_log( fmt, ... )\
	__G_LOGGER__.fatal(__FORMAT__(fmt, ##__VA_ARGS__), __FILE_NAME__, __LINE__)

#define critical_log( fmt, ... )\
	__G_LOGGER__.critical(__FORMAT__(fmt, ##__VA_ARGS__), __FILE_NAME__, __LINE__)

#define error_log( fmt, ... )\
	__G_LOGGER__.error(__FORMAT__(fmt, ##__VA_ARGS__), __FILE_NAME__, __LINE__)

#define warning_log( fmt, ... )\
	__G_LOGGER__.warning(__FORMAT__(fmt, ##__VA_ARGS__), __FILE_NAME__, __LINE__)

#define notice_log( fmt, ... )\
	__G_LOGGER__.notice(__FORMAT__(fmt, ##__VA_ARGS__), __FILE_NAME__, __LINE__)

#define info_log( fmt, ... )\
	__G_LOGGER__.information(__FORMAT__(fmt, ##__VA_ARGS__), __FILE_NAME__, __LINE__)

#endif