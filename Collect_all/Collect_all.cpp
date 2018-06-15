// Collect_all.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "../common/common.h"
#include "../common/common_fun.h"
#include "../common/mutex.h"
#include "../common/TimeElapsed.h"
#include "../common/mem_pool.h"
#include "../common/object_pool.h"
#include "../common/String_util.h"

class test
{
public:
	test()
	{
		std::cout <<"test()" << std::endl;
	}
	~test()
	{
		std::cout << "~test()" << std::endl;
	}
	DISALLOW_EVIL_CONSTRUCTORS(test);
protected:
private:
};

using namespace baseCollect;

typedef struct MyStruct
{
	int a[1024*4];
}MyStruct,*pMyStruct;

int main()
{
	std::cout << "Hello World"<< std::endl;

	//test t;
	//test a(t);
	//std::string strFileName = basefunc::getFileNameFromPath("D:\\code\\svncode\\code\\3.0\\PlanD_SvnServer\\code\\rc_app\\DeepEye.exe");


	//Mutex mutex;
	
	//{
		//MutexGuard mg(mutex);
	//}
	
	//{
	//	timeElapsed te("time start");
	//	Sleep(1000);
	//}
	
#if 0


	{
		//内存池测试
		MemPool<MyStruct> g_mp;

		{
			timeElapsed te("普通申请内存");
			for (int i = 0; i < 1024; i++)
			{
				MyStruct* ms = new MyStruct();
				delete ms;
			}
		}

		{
			timeElapsed te("内存池申请内存");
			for (int i = 0; i < 1024; i++)
			{
				MyStruct* ms = g_mp.get();
				g_mp.put(ms);
			}
		}
		
	}
	
	
#endif

	//对象池
// 	ObjectPool<test> ot;
// 	test* t = ot.get();
// 	ot.put(t);

	std::string str = "ZHANG";
	std::string strDest = baseCollect::StringUtil::format(str,"%d%s",123,"sd");

	std::string strDest1 = baseCollect::StringUtil::format("%d%s", 123, "sd");
	getchar();
    return 0;
}

