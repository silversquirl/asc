#ifndef _ASC_LUA_API_H
#define _ASC_LUA_API_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "lua/lowlevel.h"
#include "lua/root.h"
#include "lua/consts.h"

lua_State *asc_lua_init();

void asc_lua_push_handle(lua_State *l, wlc_handle h);
wlc_handle asc_lua_get_handle(lua_State *l, int arg);

int asc_lua_push_callback(lua_State *l, const char *cbname);
void asc_lua_push_point(lua_State *l, const struct wlc_point *p);
void asc_lua_push_size(lua_State *l, const struct wlc_size *s);

int asc_lua_call_safely(lua_State *l, int nargs, int nresults);

#endif

