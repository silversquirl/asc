#include <wlc/wlc.h>

#include "lua_api.h"

lua_State *asc_lua_init() {
  lua_State *l = luaL_newstate();
  if (!l) return NULL;
  luaL_openlibs(l);

  /* Register library */
  luaL_newlib(l, asc_lua_root_api);
  luaL_newlib(l, asc_lua_lowlevel_api);
  lua_setfield(l, -2, "lowlevel");
  lua_setglobal(l, "Asc");

  /* Create callback table in registry */
  lua_newtable(l);
  lua_setfield(l, LUA_REGISTRYINDEX, "asc_callbacks");

  /* Create metatable for handles */
  luaL_newmetatable(l, "asc_handle");
  lua_pop(l, 1);

  /* Register constants */
  asc_lua_register_consts(l);

  return l;
}

void asc_lua_push_handle(lua_State *l, wlc_handle h) {
  wlc_handle *ud = lua_newuserdata(l, sizeof(h));
  memcpy(ud, &h, sizeof(h));
  luaL_setmetatable(l, "asc_handle");
}

wlc_handle asc_lua_get_handle(lua_State *l, int arg) {
  wlc_handle *h = luaL_checkudata(l, arg, "asc_handle");
  return *h;
}

int asc_lua_push_callback(lua_State *l, const char *cbname) {
  lua_getfield(l, LUA_REGISTRYINDEX, "asc_callbacks");

  switch (lua_getfield(l, -1, cbname)) {
    case LUA_TFUNCTION:
      lua_remove(l, -2);
      return 0;
    case LUA_TNIL:
      lua_pop(l, 2);
      return 1;
    default:
      lua_pop(l, 2);
      return -1;
  }
}

void asc_lua_push_point(lua_State *l, const struct wlc_point *p) {
  lua_newtable(l);
  lua_pushnumber(l, p->x);
  lua_setfield(l, -2, "x");
  lua_pushnumber(l, p->y);
  lua_setfield(l, -2, "y");
}

void asc_lua_push_size(lua_State *l, const struct wlc_size *s) {
  lua_newtable(l);
  lua_pushnumber(l, s->w);
  lua_setfield(l, -2, "w");
  lua_pushnumber(l, s->h);
  lua_setfield(l, -2, "h");
}

int asc_lua_call_safely(lua_State *l, int nargs, int nresults) {
  switch (lua_pcall(l, nargs, nresults, 0)) {
    case 0:
      return 0;

    case LUA_ERRRUN:
      fprintf(stderr, "Runtime");
      break;
    case LUA_ERRMEM:
      fprintf(stderr, "Memory allocation");
      break;
    case LUA_ERRGCMM:
      fprintf(stderr, "Garbage collection");
      break;
  }

  fprintf(stderr, " error in Lua code");

  if (lua_isstring(l, -1)) {
    fprintf(stderr, ": %s", lua_tostring(l, -1));
    lua_pop(l, 1);
  }

  fprintf(stderr, "\n");

  return -1;
}

