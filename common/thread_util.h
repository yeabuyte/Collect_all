#ifndef _THREAD_UTIL_H_
#define _THREAD_UTIL_H_

#ifdef WIN32
#else
#include <pthread.h>
#endif

#include "common.h"

namespace baseCollect {

#ifdef WIN32
	#define	currentThreadId (uint32_t)::GetCurrentThreadId
#else
	#define currentThreadId (uint32_t)pthread_self
#endif

} // namespace baseCollect

#endif // _THREAD_UTIL_H_
