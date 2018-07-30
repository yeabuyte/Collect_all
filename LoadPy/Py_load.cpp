#include "Py_load.h"
#include <string>
#include <Python.h>

using namespace baseCollect;

bool Py_load::LoadPyEnv(const char* pszPath /* = "" */)
{
	Py_Initialize();    // ³õÊ¼»¯
	PyRun_SimpleString("import sys");

	if (strlen(pszPath) > 0)
	{
		std::string strPath = "sys.path.append('";
		strPath += pszPath;
		strPath += "')";
		PyRun_SimpleString(strPath.c_str());
	}
	else
	{
		PyRun_SimpleString("sys.path.append('./Python')");
	}

	return (!Py_IsInitialized());
}