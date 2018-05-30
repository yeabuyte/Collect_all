/*******************************************************************
*@filename:     TimeElapsed.h
*@author:       zxj
*@date:         2018/5/30 15:30
*@about:		函数性能执行时间检测类
********************************************************************/
#ifndef _TIME_ELAPSED_H
#define _TIME_ELAPSED_H

#include <chrono>
#include <ctime>
#include <string>
#include <iostream>

using namespace std;
using namespace std::chrono;

namespace baseCollect{
	class timeElapsed
	{
	public:
		timeElapsed()
		{
			start = system_clock::now();
		}
		timeElapsed(const string &str)
		{
			start = system_clock::now();
			m_str = str;
		}
		~timeElapsed()
		{
			auto end = system_clock::now();

			auto duration = duration_cast<microseconds>(end - start);
			cout << m_str << "执行时间"
				<< double(duration.count()) * microseconds::period::num / microseconds::period::den
				<< "秒" << endl;
		}
	private:
		std::chrono::system_clock::time_point start;
		string m_str;
	};
}

#endif // !_TIME_ELAPSED_H
