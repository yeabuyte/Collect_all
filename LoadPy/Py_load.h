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
	public:
		//����Python����
		static bool LoadPyEnv(const char* pszPath = "");
		//�ͷ�Python����
		static void ReleasePyEnv();
	};
}
#endif