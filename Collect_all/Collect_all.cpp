// Collect_all.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "../common/common.h"
#include "../common/common_fun.h"

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


int main()
{
	std::cout << "Hello World"<< std::endl;

	//test t;
	//test a(t);
	std::string strFileName = basefunc::getFileNameFromPath("D:\\code\\svncode\\code\\3.0\\PlanD_SvnServer\\code\\rc_app\\DeepEye.exe");

	getchar();
    return 0;
}

