/*******************************************************************
*@filename:     common.h
*@author:       zxj
*@date:         2018/5/29 19:44
********************************************************************/

#ifndef _COMMON_H
#define _COMMON_H


#include <string>
#include <functional>
#include <stdint.h>
#include <memory>


#ifndef NDEBUG
#include <assert.h>
#endif

#ifdef WIN32
#pragma warning(disable:4819)
#pragma warning(disable:4996)
#define snprintf _snprintf

#if _MSC_VER < 1500 // MSVC 2008
#define vsnprintf _vsnprintf
#endif
#endif

namespace baseCollect
{
	using std::string;
	using namespace std::placeholders;


	// disallow copy ctor and assign opt
	#undef DISALLOW_EVIL_CONSTRUCTORS
	#define DISALLOW_EVIL_CONSTRUCTORS(TypeName)    \
    TypeName(const TypeName&) =delete;                         \
    void operator=(const TypeName&) = delete

	// delete object safe
	#define SAFE_DELETE(p)        \
    if (NULL != p) {          \
        delete p;             \
        p = NULL;             \
    }

	// delete object safe
	#define SAFE_DELETE_ARRAY(p)        \
    if (NULL != p) {          \
        delete []p;             \
        p = NULL;             \
    }

	#define MIN(a,b) ((a)<(b)) ? (a) : (b)
	#define MAX(a,b) ((a)>(b)) ? (a) : (b)

}



#endif