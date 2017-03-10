#include <wlc/wlc.h>

#include "lua/consts.h"

void asc_lua_register_consts(lua_State *l) {
  lua_getglobal(l, "Asc"); // Get Asc library
  lua_newtable(l); // Create consts table

  /* wlc_view_state_bit */
  lua_pushnumber(l, WLC_BIT_MAXIMIZED);
  lua_setfield(l, -2, "MAXIMIZED");
  lua_pushnumber(l, WLC_BIT_FULLSCREEN);
  lua_setfield(l, -2, "FULLSCREEN");
  lua_pushnumber(l, WLC_BIT_RESIZING);
  lua_setfield(l, -2, "RESIZING");
  lua_pushnumber(l, WLC_BIT_MOVING);
  lua_setfield(l, -2, "MOVING");
  lua_pushnumber(l, WLC_BIT_ACTIVATED);
  lua_setfield(l, -2, "ACTIVATED");

  lua_setfield(l, -2, "const"); // Put consts table into Asc library
  lua_pop(l, 1);
}

