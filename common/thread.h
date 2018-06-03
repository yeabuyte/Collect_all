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

	typedef std::shared_ptr<Thread> ThreadPtr;
	typedef std::vector<ThreadPtr> VecThreadPtr;
	/// @breaf 线程组
 	class ThreadGroup
 	{
 	public:
		DISALLOW_EVIL_CONSTRUCTORS(ThreadGroup);
 		ThreadGroup()
 		{}
 		~ThreadGroup()
 		{
 			joinAll();
			m_threads.clear();
 		}

 		void addThread(ThreadPtr thread)
 		{
			m_threads.push_back(thread);
 		}
 
 		void startAll()
 		{
 			for (size_t i = 0; i < m_threads.size(); ++i) {
				m_threads[i]->start();
 			}
 		}
 
 		void joinAll()
 		{
 			for (size_t i = 0; i < m_threads.size(); ++i) {
				m_threads[i]->join();
 			}
 		}
 
 		void stopAll()
 		{
 			for (size_t i = 0; i < m_threads.size(); ++i) {
				m_threads[i]->stop();
 			}
 		}
 
 		size_t size() const { return m_threads.size(); }
		VecThreadPtr m_threads;
 	};
 	
}

#endif

