#include "thread.h"


namespace baseCollect
{

	// 全局的函数
	void ThreadProcess(Thread* pThread)
	{
		assert(nullptr != pThread);

		pThread->run();
	}

	bool Thread::start()
	{
		if (kInit != _state) {
			return false;
		}

		bool result = false;
		m_thread = std::make_shared<std::thread>(&ThreadProcess, this);
		if (m_thread == nullptr)
		{
			return result;
		}
		result = true;
		_state = kStart;
		return result;
	}

	bool Thread::stop()
	{
		if (kStop == _state || kInit == _state) {
			return true;
		}
		_state = kStop;
		return true;
	}

	void Thread::run()
	{
		_state = kJoined;
	}

	bool Thread::join()
	{
		assert(m_thread!=nullptr);
		m_thread->join();
		_state = kJoined;
		return true;
	}
}
