/*******************************************************************
*@filename:     thread_pool.h
*@author:       zxj
*@date:         2018/6/3 13:33
*@about:		线程池添加
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

		/// @brief 初始化线程池
		/// @param[in] threadNum 线程个数
		bool init(int threadNum = kDefaultThreadNum)
		{
			if (_inited) {
				return false;
			}
			_inited = true;
			addWorker(threadNum);
			return _inited;
		}

		/// @brief 添加线程任务
		void addTask(const TaskMethod &task)
		{
			_tasks.put(task);
		}

		/// @brief 等待线程池结束
		void join()
		{
			for (ThreadVector::const_iterator it = _threads.begin(); it != _threads.end(); ++it) {
				(*it)->join();
			}

			_threads.clear();
		}

		/// @brief 得到线程个数
		size_t size() const { return _threads.size(); }

		/// @brief 结束线程池
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

		// 添加工作线程
		void addWorker(int threadNum)
		{
			for (int i = 0; i < threadNum; ++i) {
				std::shared_ptr<Thread> thread(new Thread());
				_threads.push_back(thread);
				thread->start();
			}
		}

		// 运行任务
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

#endif // 