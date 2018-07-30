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
#include "../log_source/logging.h"
#include "../log_source/log_stdout.h"
#include "../log_source/log_file.h"
#include "../net/inet_address.h"
#include "../log_source/log_syslog.h"

#include "../log_source/log/logger.h"

//lua test
#include "../Script/script.h"
#include "../Script/testlua.h"

extern "C"
{
	int  tolua_tolua_open(lua_State* tolua_S);
}


class test1
{
public:
	test1()
	{
		std::cout << "Test1" << std::endl;
	}
	~test1()
	{
		std::cout << "~Test1" << std::endl;
	}
	void show()
	{
		std::cout << "test1::show" << std::endl;
	}
protected:
private:
};
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
	//DISALLOW_EVIL_CONSTRUCTORS(test);
	void operator=(test1& t1)
	{
		t1.show();
	}
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
		
	}
	
}
void fun1()
{
	while (1)
	{
		BASECOLLECT_LOG(LOGLEVEL_TRACE) << "中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
			中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民\
中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民中国人民";

	}

}


int lua_add(lua_State *L)
{
	int x = lua_tonumber(L, 1);
	int y = lua_tonumber(L, 2);
	int ret = x + y;
	printf("lua_add: x(%d) + y(%d) = %d\n", x, y, ret);
	lua_pushnumber(L, ret);
	return 1;
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

	//设置控制台数据
	//SET_LOG_STDOUT("consol");

	//写文件
	//SET_LOG_FILE("\\logs","client");

	//写服务器
	//net::InetAddress ia = net::InetAddress("127.0.0.1",60002);
	//SET_LOG_SYSLOG("SYSLOG",ia);
// 	while (1)
// 	{
// 		BASECOLLECT_LOG(LOGLEVEL_TRACE) << "你好，中国123";
// 		Sleep(1000);
// 	}
// 	BASECOLLECT_LOG(LOGLEVEL_TRACE) << "123";

	//std::thread t(fun1);
	//t.detach();
	
//  	while (1)
//  	{
// 		debug_log("中国人民中国人");
// 			
//  	}

 	lua_State *l = lua_open();
 	luaL_openlibs(l);
 
 	
 	//tolua_tolua_open(l);

	// 往lua中注册函数    
	lua_pushvalue(l, LUA_GLOBALSINDEX);
	lua_pushstring(l, "lua_add");
	lua_pushcfunction(l, lua_add);
	lua_rawset(l, -3);
	lua_pop(l, 1);
 
 	if (luaL_dofile(l, "main.lua"))
 	{  // load and call
		std::cout <<"lua 文件加载失败" << std::endl;
 	}
 	lua_close(l);
	getchar();
    return 0;
}

