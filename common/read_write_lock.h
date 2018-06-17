/*******************************************************************
*@filename:     read_write_lock.h
*@author:       zxj
*@date:         2018/6/17 13:34
*@about:		读写锁
********************************************************************/


#include <mutex>
#include <condition_variable>

class readwrite_lock
{
public:
	readwrite_lock()
		: stat(0)
	{
	}

	void readLock()
	{
		std::unique_lock<std::mutex> lck(mtx);
		while (stat < 0)
			cond.wait(lck);
		++stat;
	}

	void readUnlock()
	{
		std::unique_lock<std::mutex> lck(mtx);
		if (--stat == 0)
			cond.notify_one(); // 叫醒一个等待的写操作  
	}

	void writeLock()
	{
		std::unique_lock<std::mutex> lck(mtx);
		while (stat != 0)
			cond.wait(lck);
		stat = -1;
	}

	void writeUnlock()
	{
		std::unique_lock<std::mutex> lck(mtx);
		stat = 0;
		cond.notify_all(); // 叫醒所有等待的读和写操作  
	}

private:
	std::mutex mtx;
	std::condition_variable cond;
	int stat; // == 0 无锁；> 0 已加读锁个数；< 0 已加写锁  
};