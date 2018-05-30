// Collect_all.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "../common/common.h"

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


	getchar();
    return 0;
}

