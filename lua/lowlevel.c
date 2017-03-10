// #include <stdlib.h>
// #include <stdio.h>

#include <wlc/wlc.h>

#include "lua/lowlevel.h"
#include "lua_api.h"

int asc_lua_output_get_name(lua_State *l) {
  wlc_handle output = asc_lua_get_handle(l, 1);

  const char *name = wlc_output_get_name(output);
  lua_pushstring(l, name); /* Conveniently handles NULL values for us */

  return 1;
}

int asc_lua_output_get_mask(lua_State *l) {
  wlc_handle output = asc_lua_get_handle(l, 1);
  uint32_t mask = wlc_output_get_mask(output);

  lua_pushnumber(l, mask);
  return 1;
}

int asc_lua_view_focus(lua_State *l) {
  wlc_handle view = asc_lua_get_handle(l, 1);

  wlc_view_focus(view);

  return 0;
}

int asc_lua_view_get_output(lua_State *l) {
  wlc_handle view = asc_lua_get_handle(l, 1);

  wlc_handle output = wlc_view_get_output(view);
  asc_lua_push_handle(l, output);

  return 1;
}

int asc_lua_view_get_output_mask(lua_State *l) {
  wlc_handle view = asc_lua_get_handle(l, 1);

  wlc_handle output = wlc_view_get_output(view);
  uint32_t mask = wlc_output_get_mask(output);

  lua_pushnumber(l, mask);
  return 1;
}

int asc_lua_view_show(lua_State *l) {
  wlc_handle view = asc_lua_get_handle(l, 1);

  wlc_handle output = wlc_view_get_output(view);
  uint32_t mask = wlc_output_get_mask(output);
  wlc_view_set_mask(view, mask);

  return 0;
}

int asc_lua_view_bring_to_front(lua_State *l) {
  wlc_handle view = asc_lua_get_handle(l, 1);

  wlc_view_bring_to_front(view);

  return 0;
}

int asc_lua_view_set_mask(lua_State *l) {
  wlc_handle view = asc_lua_get_handle(l, 1);
  uint32_t mask = luaL_checkinteger(l, 2);

  wlc_view_set_mask(view, mask);

  return 0;
}

int asc_lua_view_set_state(lua_State *l) {
  wlc_handle view = asc_lua_get_handle(l, 1);

  enum wlc_view_state_bit state = luaL_checkinteger(l, 2);

  if (!lua_isboolean(l, 3)) return -1;
  bool toggle = lua_toboolean(l, 3);

  wlc_view_set_state(view, state, toggle);

  return 0;
}

int asc_lua_set_pointer_position(lua_State *l) {
  struct wlc_point pos = {
    luaL_checkinteger(l, 1),
    luaL_checkinteger(l, 2),
  };

  wlc_pointer_set_position(&pos);

  return 0;
}

