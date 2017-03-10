#ifndef _ASC_LUA_ROOT_H
#define _ASC_LUA_ROOT_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int asc_lua_exec(lua_State *l);
int asc_lua_register_callback(lua_State *l);

static const struct luaL_Reg asc_lua_root_api[] = {
  {"exec", asc_lua_exec},
  {"on", asc_lua_register_callback},

  {NULL, NULL}
};

#endif

