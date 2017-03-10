/*
 * Asc's root-level Lua API
 * Accessed via Asc.foo from Lua
 */

#include <stdlib.h>

#include <wlc/wlc.h>

#include "lua/root.h"

int asc_lua_exec(lua_State *l) {
  const char *cmd = luaL_checkstring(l, 1);

  lua_len(l, 2);
  int nargs = luaL_checkinteger(l, -1);
  lua_pop(l, 1);

  const char **args = calloc(nargs + 2, sizeof(char *));

  const char **arg = args;
  *(arg++) = cmd;

  lua_pushnil(l);
  while (lua_next(l, 2) != 0) {
    if (lua_type(l, -2) != LUA_TNUMBER) break;

    *arg = luaL_checkstring(l, -1);
    arg++;

    lua_pop(l, 1);
  }
  arg = NULL;

  wlc_exec(cmd, (char *const *)args);
  free(args);

  return 0;
}

int asc_lua_register_callback(lua_State *l) {
  if (!lua_isstring(l, 1)) {
    fprintf(stderr, "Asc.on: Argument 1 is not a string\n");
    return 0;
  }
  if (!lua_isfunction(l, 2)) {
    fprintf(stderr, "Asc.on: Argument 2 is not a function\n");
    return 0;
  }

  lua_getfield(l, LUA_REGISTRYINDEX, "asc_callbacks");

  lua_pushvalue(l, 1); /* Event name (key) */
  lua_pushvalue(l, 2); /* Callback (value) */
  lua_settable(l, -3); /* Put the value in the table */

  lua_setfield(l, LUA_REGISTRYINDEX, "asc_callbacks");

  return 0;
}

