// Collect_all.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "../common/common.h"
#include "../common/common_fun.h"
#include "../common/mutex.h"
#include "../common/TimeElapsed.h"
#include "../common/mem_pool.h"

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

typedef struct MyStruct
{
	int a[10000000];
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
		//�ڴ�ز���
		MemPool<MyStruct> g_mp;

		{
			timeElapsed te("��ͨ�����ڴ�");
			for (int i = 0; i < 1000; i++)
			{
				MyStruct* ms = new MyStruct();
				delete ms;
			}
		}

		{
			timeElapsed te("�ڴ�������ڴ�");
			for (int i = 0; i < 1000; i++)
			{
				MyStruct* ms = g_mp.get();
				g_mp.put(ms);
			}
		}
		
	}
	
	
#endif

	getchar();
    return 0;
}

