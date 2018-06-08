/*******************************************************************
*@filename:     thread_pool.h
*@author:       zxj
*@date:         2018/6/3 13:33
*@about:		�̳߳����
********************************************************************/

#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

#include <functional>
#include <memory>
#include <queue>
#include "thread.h"
#include "mutex.h"

namespace baseCollect {

	typedef std::function<void()> TaskMethod;

	class ThreadPool
	{
	public:
		ThreadPool()
			: _inited(false)
		{}
		~ThreadPool()
		{}

		/// @brief ��ʼ���̳߳�
		/// @param[in] threadNum �̸߳���
		bool init(int threadNum = kDefaultThreadNum)
		{
			if (_inited) {
				return false;
			}
			_inited = true;
			addWorker(threadNum);
			return _inited;
		}

		/// @brief ����߳�����
		void addTask(const TaskMethod &task)
		{
			_tasks.put(task);
		}

		/// @brief �ȴ��̳߳ؽ���
		void join()
		{
			for (ThreadVector::const_iterator it = _threads.begin(); it != _threads.end(); ++it) {
				(*it)->join();
			}

			_threads.clear();
		}

		/// @brief �õ��̸߳���
		size_t size() const { return _threads.size(); }

		/// @brief �����̳߳�
		void terminate()
		{
			for (ThreadVector::const_iterator it = _threads.begin(); it != _threads.end(); ++it) {
				(*it)->stop();
			}
		}

	private:
		DISALLOW_EVIL_CONSTRUCTORS(ThreadPool);
		typedef std::vector<std::shared_ptr<Thread>> ThreadVector;

		class TaskQueue
		{
		public:
			TaskQueue() {}
			~TaskQueue() {}

			void put(const TaskMethod &task)
			{
				MutexGuard mutex(m_mutex);
				_tasks.push(task);
			}
			TaskMethod get()
			{
				if (_tasks.empty())
				{
					return nullptr;
				}
				TaskMethod task;
				MutexGuard mutex(m_mutex);
				task = _tasks.front();
				_tasks.pop();
				return task;
			}

		private:
			DISALLOW_EVIL_CONSTRUCTORS(TaskQueue);
			typedef std::queue<TaskMethod> Tasks;
			Tasks _tasks;
			Mutex m_mutex;
		};

		// ��ӹ����߳�
		void addWorker(int threadNum)
		{
			for (int i = 0; i < threadNum; ++i) {
				std::shared_ptr<Thread> thread(new Thread());
				_threads.push_back(thread);
				thread->start();
			}
		}

		// ��������
		void taskRunner()
		{
			while (true) {
				TaskMethod task = _tasks.get();
				task();
			}
		}

		bool _inited;
		ThreadVector _threads;
		TaskQueue _tasks;

		static const int32_t kDefaultThreadNum = 10;
	};

} // namespace 

#endif // _THEFOX_BASE_THREADPOOL_H_