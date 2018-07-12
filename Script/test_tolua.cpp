/*
** Lua binding: tolua
** Generated automatically by tolua++-1.0.92 on 07/11/18 18:57:27.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
extern "C" __declspec(dllexport) int  tolua_tolua_open (lua_State* tolua_S);

#include "testlua.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_TestLua (lua_State* tolua_S)
{
 TestLua* self = (TestLua*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"TestLua");
}

/* method: new of class  TestLua */
#ifndef TOLUA_DISABLE_tolua_tolua_TestLua_new00
static int tolua_tolua_TestLua_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TestLua",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int a = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   TestLua* tolua_ret = (TestLua*)  new TestLua(a);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"TestLua");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  TestLua */
#ifndef TOLUA_DISABLE_tolua_tolua_TestLua_new00_local
static int tolua_tolua_TestLua_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TestLua",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int a = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   TestLua* tolua_ret = (TestLua*)  new TestLua(a);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"TestLua");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  TestLua */
#ifndef TOLUA_DISABLE_tolua_tolua_TestLua_delete00
static int tolua_tolua_TestLua_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TestLua",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TestLua* self = (TestLua*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: show of class  TestLua */
#ifndef TOLUA_DISABLE_tolua_tolua_TestLua_show00
static int tolua_tolua_TestLua_show00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TestLua",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TestLua* self = (TestLua*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'show'",NULL);
#endif
  {
   self->show();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'show'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_a of class  TestLua */
#ifndef TOLUA_DISABLE_tolua_get_TestLua_m_a
static int tolua_get_TestLua_m_a(lua_State* tolua_S)
{
  TestLua* self = (TestLua*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_a'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_a);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_a of class  TestLua */
#ifndef TOLUA_DISABLE_tolua_set_TestLua_m_a
static int tolua_set_TestLua_m_a(lua_State* tolua_S)
{
  TestLua* self = (TestLua*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_a'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_a = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
int tolua_tolua_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TestLua","TestLua","",tolua_collect_TestLua);
  #else
  tolua_cclass(tolua_S,"TestLua","TestLua","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TestLua");
   tolua_function(tolua_S,"new",tolua_tolua_TestLua_new00);
   tolua_function(tolua_S,"new_local",tolua_tolua_TestLua_new00_local);
   tolua_function(tolua_S,".call",tolua_tolua_TestLua_new00_local);
   tolua_function(tolua_S,"delete",tolua_tolua_TestLua_delete00);
   tolua_function(tolua_S,"show",tolua_tolua_TestLua_show00);
   tolua_variable(tolua_S,"m_a",tolua_get_TestLua_m_a,tolua_set_TestLua_m_a);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 int luaopen_tolua (lua_State* tolua_S) {
 return tolua_tolua_open(tolua_S);
};
#endif

