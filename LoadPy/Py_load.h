/*******************************************************************
*@filename:     Py_load.h
*@author:       zxj
*@date:         2018/7/30 18:38
*@about:		
********************************************************************/

#ifndef PY_LOAD_H
#define PY_LOAD_H


namespace baseCollect
{
	class Py_load
	{
		//加载Python环境
		static bool LoadPyEnv(const char* pszPath = "");
		//释放Python环境

	};
}
#endif