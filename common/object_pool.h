/*******************************************************************
*@filename:     object_pool.h
*@author:       zxj
*@date:         2018/5/31 10:34
*@about:		添加对象池(自动调用构造析构函数)
********************************************************************/


#ifndef _OBJECT_POOL_H_
#define _OBJECT_POOL_H_

#include <new>
#include "mem_pool.h"

namespace baseCollect {

	template<typename T>
	class ObjectPool
	{
	public:
		T *get()
		{
			T *obj = _pool.get();
			new(obj) T(); // placement new 
			return obj;
		}

		template<typename Arg0>
		T *get(Arg0 &arg0)
		{
			T *obj = _pool.get();
			new(obj) T(arg0); // placement new
			return obj;
		}

		template<typename Arg0, typename Arg1>
		T *get(Arg0 &arg0, Arg1 &arg1)
		{
			T *obj = _pool.get();
			new(obj) T(arg0, arg1); // placement new
			return obj;
		}

		template<typename Arg0, typename Arg1, typename Arg2>
		T *get(Arg0 &arg0, Arg1 &arg1, Arg2 &arg2)
		{
			T *obj = _pool.get();
			new(obj) T(arg0, arg1, arg2); // placement new
			return obj;
		}

		template<typename Arg0, typename Arg1, typename Arg2, typename Arg3>
		T *get(Arg0 &arg0, Arg1 &arg1, Arg2 &arg2, Arg3 &arg3)
		{
			T *obj = _pool.get();
			new(obj) T(arg0, arg1, arg2, arg3); // placement new
			return obj;
		}

		template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
		T *get(Arg0 &arg0, Arg1 &arg1, Arg2 &arg2, Arg3 &arg3, Arg4 &arg4)
		{
			T *obj = _pool.get();
			new(obj) T(arg0, arg1, arg2, arg3, arg4); // placement new
			return obj;
		}

		/*
		* @brief delete object
		*/
		void put(T *obj)
		{
			obj->~T();
			_pool.put(obj);
		}

	private:
		MemPool<T> _pool;
	};

} // namespace 

#endif // _OBJECT_MEM_POOL_H_