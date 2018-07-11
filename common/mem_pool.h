/*******************************************************************
*@filename:     mem_pool.h
*@author:       zxj
*@date:         2018/5/30 19:00
*@about:		简单内存池实现
********************************************************************/

#ifndef _MEM_POOL_H_
#define _MEM_POOL_H_


#include <vector>
#include "common.h"
#include "mutex.h"

namespace baseCollect {

	template<typename T>
	class MemPool
	{
	public:
		DISALLOW_EVIL_CONSTRUCTORS(MemPool);
		MemPool()
		{
			addChunk();
			_freeHead = _chunks.back();
		}
		~MemPool()
		{
			while (!_chunks.empty()) {
				T *pointer = _chunks.back();
				_chunks.pop_back();
				free(pointer);
			}

			_freeBlocks.clear();
			_freeHead = NULL;
		}

		/// @brief alloc memory
		/// @raturn pointer to allocated memory
		T *get()
		{
			T *ret = NULL;

			MutexGuard lock(_mutex);
			if (!_freeBlocks.empty()) {
				ret = _freeBlocks.back();
				_freeBlocks.pop_back();
			}
			else {
				//if (_freeHead == (_chunks.back() + (_chunks.size() * kDefaultBlockSize))) {
				if (_freeHead != _chunks.back())
				{
					addChunk();
					_freeHead = _chunks.back();
				}
				ret = _freeHead;
				++_freeHead;
			}
			return ret;
		}

		/// @brief delete memory
		/// @param[in] pointer pointer to delete
		void put(T *pointer)
		{
			MutexGuard lock(_mutex);
			_freeBlocks.push_back(pointer);
		}

	private:
		void addChunk()
		{
			size_t blockSize = (_chunks.size() + 1) * kDefaultBlockSize;
			_chunks.push_back(reinterpret_cast<T *>(malloc(sizeof(T)* kDefaultBlockSize)));
		}

		Mutex _mutex;
		T *_freeHead;
		std::vector<T *> _chunks;
		std::vector<T *> _freeBlocks;

		static const size_t kDefaultBlockSize = 1024;
	};

} // namespace

#endif // _MEMPOOL_H_
