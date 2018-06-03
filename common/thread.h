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

	typedef std::shared_ptr<Thread> ThreadPtr;
	typedef std::vector<ThreadPtr> VecThreadPtr;
	/// @breaf �߳���
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

