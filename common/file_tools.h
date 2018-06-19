/*******************************************************************
*@filename:     file_tools.h
*@author:       zxj
*@date:         2018/6/19 20:33
*@about:		一些文件操作的辅助帮助函数
********************************************************************/
#ifndef _BASE_FILES_H_
#define _BASE_FILES_H_

#include <string.h>
#include "common.h"

#ifdef WIN32
#include <direct.h>
#define getcwd _getcwd
#else
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif

namespace baseCollect {

class Files
{
public:
	/// @biref 创建目录
	static void makePath(string &dir)
	{   
		char filePath[1000] = {0};
		bool bAbsolutePath = true;

	#ifdef WIN32
		if (string::npos == dir.find(':'))
			bAbsolutePath = false;
	#else
		if ('/' != dir[0])
			bAbsolutePath = false;
	#endif
    
		if (!bAbsolutePath) {
			getcwd(filePath, sizeof(filePath));
			char cSeparator = filePath[strlen(filePath)];
			if (!(cSeparator == '/' || cSeparator == '\\'))
				strcat(filePath, "/");
        
			strncat(filePath, dir.c_str(), sizeof(filePath) - strlen(filePath));
		} else {
			strncpy(filePath, dir.c_str(), sizeof(filePath));
		}
    
		char *curDir = filePath;
    
		while (*curDir != '\0') {
			if (*curDir == '\\' || *curDir == '/') {
				*curDir = '\0';
	#ifdef WIN32
			_mkdir(filePath);
	#else
			mkdir(filePath, S_IRWXU);
	#endif
				*curDir = '/';
			}
			++curDir;
		}
	#ifdef WIN32
		_mkdir(filePath);
	#else
		mkdir(filePath, S_IRWXU);
	#endif 
		size_t pathLen = strlen(filePath);
		if ('/' != filePath[pathLen - 1]) {
			strcat(filePath, "/");
			++pathLen;
		}
    
		dir = filePath;
	}
};

} // namespace baseCollect

#endif // _BASE_FILES_H_