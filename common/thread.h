/*******************************************************************
*@filename:     thread.h
*@author:       zxj
*@date:         2018/5/31 18:54
*@about:		�߳�
********************************************************************/

#ifndef _THREAD_H
#define _THREAD_H

#include<vector>
#include <thread>
#include <functional>
#include "common.h"


namespace baseCollect
{

	/// @brief �߳���
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

		/// @brief �����߳�
		/// @return �ɹ�����true��ʧ�ܷ���false
		bool start();

		/// @brief �����߳�
		/// @return �ɹ�����true��ʧ�ܷ���false
		bool stop();
		
		/// �Ƿ�ֹͣ
		bool isActive()
		{
			if (_state != kStop)
			{
				return true;
			}
			return false;
		}

		/// @brief �ڵ�ǰ�߳��еȴ����߳̽���
		/// @return �ɹ�����true��ʧ�ܷ���false
		bool join();
		//run
		void run();
	private:
		StateT _state;
		std::shared_ptr<std::thread> m_thread;
	};

	/// @breaf �߳���
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

