#include "logger.h"
#include <chrono>
#include <ctime>

#if defined(_WIN32)
#include <windows.h>
#define  SPRINTF( buffer, sizeOfbuffer, fmt, ... )\
	sprintf_s(buffer, sizeOfbuffer, fmt, ##__VA_ARGS__)
#define TIME2TM(TM, TIME) localtime_s(TM, TIME)
#else
#define SPRINTF( buffer, sizeOfbuffer, fmt, ... )\
	snprintf(buffer, sizeOfbuffer, fmt, ##__VA_ARGS__)
#define TIME2TM(TM, TIME) localtime_r(TIME, TM)
#endif


Log::Log()
{
	init();

	std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	struct tm local_time;
	TIME2TM(&local_time, &tt);

	local_time.tm_hour = 0;
	local_time.tm_min = 0;
	local_time.tm_sec = 0;
	m_nextDay = std::chrono::system_clock::from_time_t(std::mktime(&local_time)) + std::chrono::duration<int, std::ratio<60 * 60 * 24>>(1);
}

void Log::init()
{
#ifdef _WIN32
	m_hStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
	_is_running = true;
	_cv_flag = false;
	//	_log_file.open(get_log_name().c_str(), std::ios::app);	// 追加模式
	_log_file.open(get_log_name().c_str(), std::ios::trunc);	// trunc模式
	_thread_ptr = std::make_unique<std::thread>(std::bind(&Log::output_log, this));
}

Log::~Log()
{
	//最后一次唤醒线程,然后等待IO线程退出
	_is_running = false;
	_cv_flag = true;
	_cv.notify_one();
	_thread_ptr->join();

	//确保最后一条写入日志
	read_log();
	_log_file.close();

#ifdef _WIN32
	CloseHandle(m_hStdHandle);
#endif
}

std::string Log::get_log_name()
{
	std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	struct tm local_time;
	TIME2TM(&local_time, &tt);

	std::string log_name;
	log_name += std::to_string(local_time.tm_year + 1900);
	log_name += "_";
	log_name += std::to_string(local_time.tm_mon + 1);
	log_name += "_";
	log_name += std::to_string(local_time.tm_mday);
	log_name += "_server.log";
	return log_name;		// RVO
}

char* Log::format_log(char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	char* buff = static_cast<char *>(_pool.get());

#if defined(_WIN32)
	vsprintf_s(buff, _SIZE, fmt, args);
#else
	vsnprintf(buff, _SIZE, fmt, args);
#endif
	va_end(args);

	return buff;
}

std::string Log::get_file_name(const char* path_file_name)
{
	std::string file_name(path_file_name);
	std::string::size_type idx;
	idx = file_name.find_last_of("\\/");
	if (idx == std::string::npos)
	{
		return file_name;
	}
	else
	{
		return file_name.substr(idx + 1);
	}
}

void Log::write(char* msg, Priority prio, const char* file, int line)
{
	time_t t;
	struct tm local_time;
	t = time(NULL);
	TIME2TM(&local_time, &t);
	char *buff = static_cast<char *>(_pool.get());
	char *log_message = static_cast<char *>(_pool.get());
	strftime(buff, _SIZE, "%Y-%m-%d %H:%M:%S", &local_time);

	switch (prio)
	{
	case PRIO_FATAL:
	{
					   SPRINTF(log_message, _SIZE, "%c[%s %s(%d)] Fatal : %s", PRIO_FATAL, buff, file, line, msg);
					   break;
	}
	case PRIO_CRITICAL:
	{
						  SPRINTF(log_message, _SIZE, "%c[%s %s(%d)] Critical : %s", PRIO_CRITICAL, buff, file, line, msg);
						  break;
	}
	case PRIO_ERROR:
	{
					   SPRINTF(log_message, _SIZE, "%c[%s %s(%d)] Error : %s", PRIO_ERROR, buff, file, line, msg);
					   break;
	}
	case PRIO_WARNING:
	{
						 SPRINTF(log_message, _SIZE, "%c[%s %s(%d)] Warning : %s", PRIO_WARNING, buff, file, line, msg);
						 break;
	}
	case PRIO_NOTICE:
	{
						SPRINTF(log_message, _SIZE, "%c[%s %s(%d)] Notice : %s", PRIO_NOTICE, buff, file, line, msg);
						break;
	}
	case PRIO_INFORMATION:
	{
							 SPRINTF(log_message, _SIZE, "%c[%s %s(%d)] Information : %s", PRIO_INFORMATION, buff, file, line, msg);
							 break;
	}
	case PRIO_DEBUG:
	{
					   SPRINTF(log_message, _SIZE, "%c[%s %s(%d)] Debug : %s", PRIO_DEBUG, buff, file, line, msg);
					   break;
	}
	case PRIO_TRACE:
	{
					   SPRINTF(log_message, _SIZE, "%c[%s %s(%d)] Trace : %s", PRIO_TRACE, buff, file, line, msg);
					   break;
	}
	default:
		break;
	}

	SPRINTF(msg, _SIZE, "%s", log_message);
	_pool.put(log_message);
	_pool.put(buff);


	{
		//入队列
		std::unique_lock<std::mutex> u_lock(_mutex);
		_work_queue.push(msg);
	}
	_cv_flag = true;
	_cv.notify_one();
}

void Log::output_log()
{
	

	while (true)
	{
		if (_is_running)
		{
			{
				std::unique_lock<std::mutex> u_lock(_mutex);
				_cv.wait(u_lock, [this]() {return this->_cv_flag; });
				read_log();
			}
			

			//std::cout << "mem_pool.size = "<<_pool._chunks.size()<< std::endl;
		}
		else
		{
			break;
		}
		_cv_flag = false;
	}
}

void Log::read_log()
{
	if (std::chrono::system_clock::now() >= m_nextDay)
	{
		m_nextDay += std::chrono::duration<int, std::ratio<60 * 60 * 24>>(1);
		_log_file.close();
		_log_file.open(get_log_name().c_str(), std::ios::trunc);
	}
	char *buffer;
	while (!_work_queue.empty())
	{
		buffer = _work_queue.front();
		_work_queue.pop();

#ifdef _WIN32
		switch (buffer[0])
		{
		case PRIO_FATAL:
		case PRIO_CRITICAL:
		case PRIO_ERROR:
			SetConsoleTextAttribute(m_hStdHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
			break;
		case PRIO_WARNING:
		case PRIO_NOTICE:
		case PRIO_INFORMATION:
			SetConsoleTextAttribute(m_hStdHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		case PRIO_DEBUG:
		case PRIO_TRACE:
			SetConsoleTextAttribute(m_hStdHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
			break;
		default:
			break;
		}
#endif
		//输出日志信息
		_log_file << buffer + 1 << std::endl;
		std::cout << buffer + 1 << std::endl;

#ifdef _WIN32
		// 恢复原始的颜色
		SetConsoleTextAttribute(m_hStdHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
#endif

		//回收内存
		_pool.put(buffer);
	}
}

void Log::fatal(char* msg, const char* file, int line)
{
	write(msg, PRIO_FATAL, file, line);
}

void Log::critical(char* msg, const char* file, int line)
{
	write(msg, PRIO_CRITICAL, file, line);
}

void Log::error(char* msg, const char* file, int line)
{
	write(msg, PRIO_ERROR, file, line);
}

void Log::warning(char* msg, const char* file, int line)
{
	write(msg, PRIO_WARNING, file, line);
}

void Log::notice(char* msg, const char* file, int line)
{
	write(msg, PRIO_NOTICE, file, line);
}

void Log::information(char* msg, const char* file, int line)
{
	write(msg, PRIO_INFORMATION, file, line);
}

void Log::debug(char* msg, const char* file, int line)
{
	write(msg, PRIO_DEBUG, file, line);
}

void Log::trace(char* msg, const char* file, int line)
{
	write(msg, PRIO_TRACE, file, line);
}