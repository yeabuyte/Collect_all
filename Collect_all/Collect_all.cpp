// Collect_all.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "../common/common.h"
#include "../common/common_fun.h"
#include "../common/mutex.h"

class test
{
public:
	test()
	{

	}
	~test()
	{

	}
	DISALLOW_EVIL_CONSTRUCTORS(test);
protected:
private:
};

using namespace baseCollect;

int main()
{
	std::cout << "Hello World"<< std::endl;

	//test t;
	//test a(t);
	std::string strFileName = basefunc::getFileNameFromPath("D:\\code\\svncode\\code\\3.0\\PlanD_SvnServer\\code\\rc_app\\DeepEye.exe");


	Mutex mutex;
	
	{
		MutexGuard mg(mutex);
	}
	
	


	getchar();
    return 0;
}

