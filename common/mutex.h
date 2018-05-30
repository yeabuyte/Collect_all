/*******************************************************************
*@filename:     mutex.h
*@author:       zxj
*@date:         2018/5/30 13:16
*@about:		»¥³âÁ¿²Ù×÷
********************************************************************/

#ifndef _MUTEX_H
#define _MUTEX_H

#include "common.h"

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
typedef CRITICAL_SECTION pthread_mutex_t;
#else
#include <pthread.h>
#endif // WIN32


namespace baseCollect
{
	class Mutex
	{
	public:
		DISALLOW_EVIL_CONSTRUCTORS(Mutex);
		Mutex():_threadId(0)
		{
#ifdef WIN32 
			InitializeCriticalSection(&_mutex);
#else
			pthread_mutex_init(&_mutex, NULL);
#endif
		}
		~Mutex()
		{
#ifdef WIN32 
			DeleteCriticalSection(&_mutex);
#else
			pthread_mutex_destroy(&_mutex);
#endif
		}

		void lock()
		{
#ifdef WIN32
			EnterCriticalSection(&_mutex);
			_threadId = static_cast<uint32_t>(GetCurrentThreadId());
#else
			pthread_mutex_lock(&_mutex);
			_threadId = static_cast<uint32_t>(pthread_self());
#endif
		}
		void unlock()
		{
			_threadId = 0;
#ifdef WIN32
			LeaveCriticalSection(&_mutex);
#else
			pthread_mutex_unlock(&_mutex);
#endif
		}
		pthread_mutex_t *getMutex()
		{
			return &_mutex;
		}
	private:
		uint32_t _threadId;
		pthread_mutex_t _mutex;
	};

	class MutexGuard
	{
	public:
		DISALLOW_EVIL_CONSTRUCTORS(MutexGuard);
		MutexGuard(Mutex& mutex):_mutex(mutex)
		{
			_mutex.lock();
		}
		~MutexGuard()
		{
			_mutex.unlock();
		}
	private:
		Mutex &_mutex;
	};

//#define MutexGuard(x) error "Missing MutexGuard object name"
}

#endif