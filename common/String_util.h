/*******************************************************************
*@filename:     String_util.h
*@author:       zxj
*@date:         2018/6/12 13:47
*@about:		�ַ���������
********************************************************************/

#ifndef _STRING_UTIL_H_
#define _STRING_UTIL_H_

#include <stdlib.h>
#include <stdarg.h>
#include <vector>
#include "common.h"

namespace baseCollect {

	class StringUtil
	{
	public:
		static const int kMaxStringLen = 100 * 1024;

		/// @brief ת����int����
		static int stoi(const string &str)
		{
			return (0 == str.length()) ? 0 : atoi(str.c_str());
		}

		/// @brief ת����unsigned int
		static unsigned int stoui(const string &str)
		{
			return (0 == str.length()) ? 0 : static_cast<unsigned int>(atoi(str.c_str()));
		}

		/// @brief ת����int64����
		static int64_t stoi64(const std::string &str)
		{
			int64_t v = 0;
#ifdef WIN32
			sscanf(str.c_str(), "%I64d", &v);
#else
			sscanf(str.c_str(), "%lld", &v);
#endif
			return v;
		}

		/// @briefת����uint64����
		static int64_t stoui64(const std::string &str)
		{
			int64_t v = 0;
#ifdef WIN32
			sscanf(str.c_str(), "%I64u", &v);
#else
			sscanf(str.c_str(), "%llu", &v);
#endif
			return v;
		}

		/// @brief ת����long
		static long stol(const string &str)
		{
			return (0 == str.length()) ? 0L : atol(str.c_str());
		}

		/// @brief ת����float
		static float stof(const string &str)
		{
			return (0 == str.length()) ? 0.0f : static_cast<float>(atof(str.c_str()));
		}

		/// @brief ת����double
		static double stod(const string &str)
		{
			return (0 == str.length()) ? 0.0 : atof(str.c_str());
		}

		/// @brief ת����bool
		static bool stob(const string &str)
		{
			return (0 == str.length() || str == "0" || str == "false" || str == "FALSE") ? false : true;
		}

		/// @brief ��int��������ת���ַ���
		static string toString(const int val)
		{
			char buf[32] = { 0 };
			snprintf(buf, sizeof(buf), "%d", val);
			return buf;
		}

		/// @brief ��unsigned int��������ת���ַ���
		static string toString(const unsigned int val)
		{
			char buf[32] = { 0 };
			snprintf(buf, sizeof(buf), "%u", val);
			return buf;
		}

		/// @brief ��long��������ת���ַ���
		static string toString(const long val)
		{
			char buf[32] = { 0 };
			snprintf(buf, sizeof(buf), "%ld", val);
			return buf;
		}

		/// @brief ��long long��������ת���ַ���
		static string toString(const long long val)
		{
			char buf[32] = { 0 };
			snprintf(buf, sizeof(buf), "%lld", val);
			return buf;
		}

		/// @brief ��double��������ת���ַ���
		static string toString(const double val)
		{
			char buf[32] = { 0 };
			snprintf(buf, sizeof(buf), "%f", val);
			return buf;
		}

		/// @brief ��bool��������ת���ַ���
		static string toString(const bool val)
		{
			return val ? "1" : "0";
		}

		/// @brief ��ʽ���ַ���
		static string &format(string &str, const char *format, ...)
		{
			va_list ap;
			va_start(ap, format);

			char *buf = (char *)malloc(kMaxStringLen);
			if (buf) {
				vsnprintf(buf, kMaxStringLen, format, ap);
				str = buf;
				free(buf);
				va_end(ap);
			}
			return str;
		}

		/// @brief ��ʽ���ַ���
		static string format(const char *format, ...)
		{
			va_list ap;
			va_start(ap, format);
			string str;

			char *buf = (char *)malloc(kMaxStringLen);
			if (buf) {
				vsnprintf(buf, kMaxStringLen, format, ap);
				str = buf;
				free(buf);
				va_end(ap);
			}
			return str;
		}

		/// @brief �Ƴ����Ŀո񡢻��з����Ʊ��
		static string trimLeft(const string &str)
		{
			string::size_type index = str.find_first_not_of("\n\r\t");
			if (index != string::npos) {
				return str.substr(index);
			}
			return str;
		}

		/// @brief �Ƴ��Ҳ�Ŀո񡢻��з����Ʊ��
		static string trimRight(const string &str)
		{
			string::size_type index = str.find_last_not_of("\n\r\t");
			if (index != string::npos) {
				return str.substr(0, index + 1);
			}
			return str;
		}

		/// @brief �Ƴ���������Ŀո񡢻��з����Ʊ��
		static string trim(const string &str)
		{
			return trimRight(trimLeft(str));
		}

		/// @brief �ж��ַ����Ƿ��ǿ���ʾ���ַ�
		static bool canDisplay(const string &str)
		{
			for (size_t i = 0; i < str.length(); i++) {
				if (!(str[i] >= 0x20 && str[i] <= 127)) {
					return false;
				}
			}
			return true;
		}

		/// @brief �Ƿ������д��ĸ
		static bool isContainUppercase(const string &str)
		{
			for (size_t i = 0; i < str.length(); i++) {
				if (str[i] >= 'A' && str[i] <= 'Z') {
					return true;
				}
			}
			return false;
		}

		/// @brief �Ƿ����Сд��ĸ
		static bool isContainLowercase(const string &str)
		{
			for (size_t i = 0; i < str.length(); i++) {
				if (str[i] >= 'a' && str[i] <= 'z') {
					return true;
				}
			}
			return false;
		}

		/// @brief �Ƿ�����������
		static bool isInteger(const string &str)
		{
			for (size_t i = 0; i < str.length(); i++) {
				if (str[i] > '9' || str[i] < '0') {
					return false;
				}
			}
			return true;

		}

		/// @brief ת��Сд��ĸ
		static string toLower(string &str)
		{
			for (string::size_type i = 0; i < str.length(); ++i)
				if (str[i] >= 'A' && str[i] <= 'Z') {
					str[i] += 0x20;
				}
			return str;
		}

		/// @brief ת�ɴ�д��ĸ
		static string toUpper(string &str)
		{
			for (string::size_type i = 0; i < str.length(); ++i)
				if (str[i] >= 'a' && str[i] <= 'z') {
					str[i] -= 0x20;
				}
			return str;
		}

		/// @brief �ַ��ǲ�����ĸ
		static bool charIsLetter(char c)
		{
			if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
				return true;
			}
			return false;
		}

		/// @brief ���ַ����Ƿ���ȣ����Դ�Сд
		static bool equalsIgnoreCase(const string &s1, const string &s2)
		{
			if (s1.length() != s2.length()) {
				return false;
			}

			for (string::size_type i = 0; i < s1.length(); ++i) {
				if (s1[i] == s2[i]) {
					continue;
				}
				if (!charIsLetter(s1[i]) || !charIsLetter(s2[i])) {
					return false;
				}
				if (0x20 != abs(s1[i] - s2[i])) {
					return false;
				}
			}
			return true;
		}

		// @brief �Ƿ�����Ӵ������Դ�Сд
		static bool isContainStringIgnoreCase(const string &str1, const string &str2)
		{
			string s1(str1);
			string s2(str2);

			toUpper(s1);
			toUpper(s2);

			return string::npos != str1.find(str2);
		}

		/// @brief �滻�ַ����е�����
		static string replace(string &str, const string &from, const string &to)
		{
			string::size_type pos = 0;
			while ((pos = str.find(from, pos)) != -1) {
				str.replace(pos, from.length(), to);
				pos += to.length();
			}
			return str;
		}

		static void swap(string &ls, string &rs)
		{
			string temp(ls);
			ls = rs;
			rs = temp;
		}

		static void strtok(const string &str, char separator, std::vector<string> &arr)
		{
			size_t pos = 0;
			size_t newPos = 0;

			while (string::npos != pos) {
				pos = str.find_first_of(separator, newPos);
				if (string::npos == pos) { // ������
					if (pos > newPos) {
						arr.push_back(str.substr(newPos, pos - newPos));
					}
					break;
				}
				else {
					if (pos > newPos) {
						arr.push_back(str.substr(newPos, pos - newPos));
					}
					newPos = pos + 1;
				}
			}
		}

		static std::vector<string> strtok(const string &str, char separator)
		{
			size_t pos = 0;
			size_t newPos = 0;
			std::vector<string> arr;

			while (string::npos != pos) {
				pos = str.find_first_of(separator, newPos);
				if (string::npos == pos) { // ������
					if (pos > newPos) {
						arr.push_back(str.substr(newPos, pos - newPos));
					}
					break;
				}
				else {
					if (pos > newPos) {
						arr.push_back(str.substr(newPos, pos - newPos));
					}
					newPos = pos + 1;
				}
			}
			return arr;
		}
	};

	inline string operator+(const char *ls, const string &rs)
	{
		string buf(ls);
		buf += rs;
		return buf;
	}

	inline bool operator==(const char *ls, const string &rs)
	{
		return !rs.compare(ls);
	}

	inline bool operator==(const string &ls, const char *rs)
	{
		return !ls.compare(rs);
	}

} // namespace thefox

#endif // _THEFOX_BASE_STRING_UTIL_H_
