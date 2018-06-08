/*******************************************************************
*@filename:     Semaphore.h
*@author:       zxj
*@date:         2018/6/5 8:07
*@about:		信号量实现（锁，条件变量）
********************************************************************/

#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#include <mutex>

namespace baseCollect
{

class Semaphore {
public:
  Semaphore(long count = 0)
    : count_(count) {
  }

  void Signal() {
    std::unique_lock<std::mutex> lock(mutex_);
    ++count_;
    cv_.notify_one();
  }

  void Wait() {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [=] { return count_ > 0; });
    --count_;
  }

private:
  std::mutex mutex_;
  std::condition_variable cv_;
  long count_;
};
}
#endif