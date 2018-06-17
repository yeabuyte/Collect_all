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
#include "../common/singleton.h"
#include "../common/read_write_lock.h"

#include "../common/debug_win.h"

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
public:
	void show()
	{
		printf("Hello Test\n");
	}
protected:
private:
};

using namespace baseCollect;

typedef struct MyStruct
{
	int a[1024*4];
}MyStruct,*pMyStruct;


int g_count = 0;
readwrite_lock rl;
void fun()
{
	while (1)
	{
		rl.readLock();
		printf("fun():%d\n", g_count);
		rl.readUnlock();
		Sleep(1000);
		
	}
	
}
void fun1()
{
	while (1)
	{
		rl.readLock();
		printf("fun1():%d\n", g_count);
		rl.readUnlock();
		Sleep(1000);

	}

}
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
// 
// 	std::string str = "ZHANG";
// 	std::string strDest = baseCollect::StringUtil::format(str,"%d%s",123,"sd");
// 
// 	std::string strDest1 = baseCollect::StringUtil::format("%d%s", 123, "sd");
// 	
// 	baseCollect::singleton<test>::instance().show();
// 	baseCollect::singleton<test>::instance().show();
// 	baseCollect::singleton<test>::instance().show();
// 	baseCollect::singleton<test>::instance().show();
// 	baseCollect::singleton<test>::instance().show();


	//
	
	
// 	std::thread t(fun);
// 	t.detach();
// 	std::thread t1(fun1);
// 	t1.detach();
// 
// 	while (1)
// 	{
// 		rl.writeLock();
// 		printf("main:%d\n", ++g_count);
// 		rl.writeUnlock();
// 		Sleep(5000);
// 		
// 	}

	//崩溃信息
	SET_UNHANDLED_EXCEPTION_FILTER;

	int* p = nullptr;

	*p = 4;


	getchar();
    return 0;
}

