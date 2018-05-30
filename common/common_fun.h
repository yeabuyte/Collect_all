/*******************************************************************
*@filename:     common_fun.h
*@author:       zxj
*@date:         2018/5/30 12:10
********************************************************************/

#ifndef _COMMON_FUN_H
#define _COMMON_FUN_H

#include <string.h>

namespace basefunc
{
	// 从路径中得到文件名
	inline const char *getFileNameFromPath(const char *pathName)
	{
		const char* slash = strrchr(pathName, '/');
		if (slash) {
			return slash + 1;
		}
		else {
			const char *bslash = strrchr(pathName, '\\');
			if (bslash) {
				return bslash + 1;
			}
		}
		return pathName;
	}



}


#endif