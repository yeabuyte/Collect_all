/*******************************************************************
*@filename:     thread.h
*@author:       zxj
*@date:         2018/5/31 18:54
*@about:		线程
********************************************************************/

#ifndef _THREAD_H
#define _THREAD_H

#include<vector>
#include <thread>
#include <functional>
#include "common.h"


namespace baseCollect
{

	/// @brief 线程类
	class Thread
	{
	public:
		DISALLOW_EVIL_CONSTRUCTORS(Thread);
		enum StateT { kInit, kStart, kJoined, kStop };

		explicit Thread(void)
			: _state(kInit),
			m_thread(nullptr)
		{}

		~Thread()
		{
			join();
			_state = kStop;
		}

		/// @brief 启动线程
		/// @return 成功返回true，失败返回false
		bool start();

		/// @brief 结束线程
		/// @return 成功返回true，失败返回false
		bool stop();
		
		/// 是否停止
		bool isActive()
		{
			if (_state != kStop)
			{
				return true;
			}
			return false;
		}

		/// @brief 在当前线程中等待该线程结束
		/// @return 成功返回true，失败返回false
		bool join();
		//run
		void run();
	private:
		StateT _state;
		std::shared_ptr<std::thread> m_thread;
	};

	/// @breaf 线程组
// 	class ThreadGroup
// 	{
// 	public:
// 		ThreadGroup()
// 		{}
// 		~ThreadGroup()
// 		{
// 			joinAll();
// 			for (size_t i = 0; i < _threads.size(); ++i) {
// 				delete _threads[i];
// 			}
// 
// 			_threads.clear();
// 		}
// 
// 		Thread *createThread(const ThreadCallback &threadfunc)
// 		{
// 			Thread *thread = new Thread(threadfunc);
// 			_threads.push_back(thread);
// 			return thread;
// 		}
// 
// 		void addThread(Thread *thread)
// 		{
// 			_threads.push_back(thread);
// 		}
// 
// 		void startAll()
// 		{
// 			for (size_t i = 0; i < _threads.size(); ++i) {
// 				_threads[i]->start();
// 			}
// 		}
// 
// 		void joinAll()
// 		{
// 			for (size_t i = 0; i < _threads.size(); ++i) {
// 				_threads[i]->join();
// 			}
// 		}
// 
// 		void stopAll()
// 		{
// 			for (size_t i = 0; i < _threads.size(); ++i) {
// 				_threads[i]->stop();
// 			}
// 		}
// 
// 		size_t size() const { return _threads.size(); }
// 
// 	private:
// 		THEFOX_DISALLOW_EVIL_CONSTRUCTORS(ThreadGroup);
// 		std::vector<Thread *> _threads;
// 	};
// 	
}

#endif

