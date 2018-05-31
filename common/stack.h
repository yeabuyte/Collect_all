/*******************************************************************
*@filename:     stack.h
*@author:       zxj
*@date:         2018/5/31 17:40
*@about:		ʹ��vectorʵ��ջ
********************************************************************/

#ifndef _BASE_STACK_H_
#define _BASE_STACK_H_

#include <vector>
#include "mutex.h"

namespace baseCollect {

	/// @brief ջ��ʵ����
	template<typename T>
	class Stack
	{
	public:
		Stack()
		{}
		~Stack()
		{}

		/// @brief ��ջ
		/// param[in] value ��Ҫ��ջ��ֵ
		void push(const T &value)
		{
			MutexGuard lock(_mutex);
			_data.push_back(value);
		}

		/// @brief ����ջ��
		void pop()
		{
			MutexGuard lock(_mutex);
			if (!_data.empty())
				_data.pop_back();
		}

		/// @brief �õ�ջ������
		/// @param[out] value �õ���ջ����ֵ
		/// @return �ɹ�����true�����򷵻�false
		bool getTop(T &value)
		{
			MutexGuard lock(_mutex);
			if (!_data.empty()) {
				value = _data[_data.size() - 1];
				return true;
			}
			return false;
		}

		/// @brief �õ�ջ��ָ��λ�õ�ֵ
		/// @param[in] position ��Ҫ�õ�ֵ��λ��
		///                     ������1��ʼ��������ʾ��ջ�����±�����λ��
		///                     �Ӹ���-1��ʼ�ݼ�����ʾ��ջ�����ϱ�����λ��
		/// @param[out] value �õ�positionλ���ϵ�ֵ
		/// @return �ɹ�����true�����򷵻�false
		bool getAt(const int position, T &value)
		{
			MutexGuard lock(_mutex);
			size_t index = 0;
			if (getIndexByPosition(position, index)) {
				value = _data[index];
				return true;
			}
			return false;
		}

		/// @brief ��ջ��ָ��λ�ø�ֵ
		/// @param[in] position ��Ҫ��ֵ��λ��
		///                     ������1��ʼ��������ʾ��ջ�����±�����λ��
		///                     �Ӹ���-1��ʼ�ݼ�����ʾ��ջ�����ϱ�����λ��
		/// @param[out] value �����õ�ֵ
		/// @return �ɹ�����true�����򷵻�false
		bool setAt(const int position, const T &value)
		{
			MutexGuard lock(_mutex);
			size_t index = 0;
			if (getIndexByPosition(position, index)) {
				_data[index] = value;
				return true;
			}
			return false;
		}

		/// @brief �õ�ջ�����ݸ���
		/// @return ����ջ�����ݸ���
		size_t size()
		{
			MutexGuard lock(_mutex);
			return _data.size();
		}

		/// @brief �ж��Ƿ��ǿ�ջ
		/// @return ���ջ��Ϊ�շ���true�����򷵻�false
		bool empty()
		{
			MutexGuard lock(_mutex);
			return _data.empty();
		}

	private:
		// ͨ��Position�õ���vector�е�����
		bool getIndexByPosition(const int position, size_t &index) const
		{
			if (_data.empty()) {
				return false;
			}

			if (position > 0) { // ��ջ�����±���
				int i = static_cast<int>(_data.size() - position);
				if (i >= 0) {
					index = i;
					return true;
				}
			}
			else if (position < 0) { //��ջ�����ϱ���
				if (static_cast<int>(_data.size()) + position >= 0) {
					index = (position * -1) - 1;
					return true;
				}
			}
			return false;
		}

		std::vector<T> _data;
		Mutex _mutex;
	};

} // namespace 

#endif // _BASE_STACK_H_