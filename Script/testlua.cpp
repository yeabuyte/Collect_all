#include "testlua.h"
#include <iostream>

TestLua::TestLua(int a):m_a(a)
{

}
TestLua::~TestLua()
{

}

void TestLua::show()
{
	std::cout <<"m_a =:" << m_a<< std::endl;
}