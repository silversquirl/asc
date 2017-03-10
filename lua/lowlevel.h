#ifndef _ASC_LUA_LOWLEVEL_H
#define _ASC_LUA_LOWLEVEL_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

/* Output API */
int asc_lua_output_get_name(lua_State *l);
int asc_lua_output_get_mask(lua_State *l);

/* View API */
int asc_lua_view_focus(lua_State *l);
int asc_lua_view_get_output(lua_State *l);
int asc_lua_view_bring_to_front(lua_State *l);
int asc_lua_view_set_mask(lua_State *l);
int asc_lua_view_set_state(lua_State *l);

int asc_lua_view_get_output_mask(lua_State *l);
int asc_lua_view_show(lua_State *l);

/* Input API */
int asc_lua_set_pointer_position(lua_State *l);

static const struct luaL_Reg asc_lua_lowlevel_api[] = {
  /* Output API */
  // {"get_outputs", asc_lua_get_outputs},
  // {"get_focused_output", asc_lua_get_focused_output},
  {"output_get_name", asc_lua_output_get_name},
  // {"output_get_sleep", asc_lua_output_get_sleep},
  // {"output_set_sleep", asc_lua_output_set_sleep},
  // {"output_set_gamma", asc_lua_output_set_gamma},
  // {"output_get_gamma_size", asc_lua_output_get_gamma_size},
  // {"output_get_resolution", asc_lua_output_get_resolution},
  // {"output_set_resolution", asc_lua_output_set_resolution},
  // {"output_get_virtual_resolution", asc_lua_output_get_virtual_resolution},
  // {"output_get_scale", asc_lua_output_get_scale},
  {"output_get_mask", asc_lua_output_get_mask},
  // {"output_set_mask", asc_lua_output_set_mask},
  // {"output_get_views", asc_lua_output_get_views},
  // {"output_set_views", asc_lua_output_set_views},
  // {"output_get_mutable_views", asc_lua_output_get_mutable_views},
  // {"output_focus", asc_lua_output_focus},

  /* View API */
  {"view_focus", asc_lua_view_focus},
  // {"view_close", asc_lua_view_close},
  {"view_get_output", asc_lua_view_get_output},
  // {"view_send_to_back", asc_lua_view_send_to_back},
  // {"view_send_below", asc_lua_view_send_below},
  // {"view_bring_above", asc_lua_view_bring_above},
  {"view_bring_to_front", asc_lua_view_bring_to_front},
  // {"view_get_mask", asc_lua_view_get_mask},
  {"view_set_mask", asc_lua_view_set_mask},
  // {"view_get_geometry", asc_lua_view_get_geometry},
  // {"view_set_geometry", asc_lua_view_set_geometry},
  // {"view_get_visible_geometry", asc_lua_view_get_visible_geometry},
  // {"view_get_type", asc_lua_view_get_type},
  // {"view_set_type", asc_lua_view_set_type},
  // {"view_get_state", asc_lua_view_get_state},
  {"view_set_state", asc_lua_view_set_state},
  // {"view_get_parent", asc_lua_view_get_parent},
  // {"view_set_parent", asc_lua_view_set_parent},
  // {"view_get_title", asc_lua_view_get_title},
  // {"view_get_instance", asc_lua_view_get_instance},
  // {"view_get_class", asc_lua_view_get_class},
  // {"view_get_app_id", asc_lua_view_get_app_id},
  // {"view_get_pid", asc_lua_view_get_pid},

  {"view_show", asc_lua_view_show},
  {"view_get_output_mask", asc_lua_view_get_output_mask},

  // {"view_positioner_get_size", asc_lua_view_positioner_get_size},
  // {"view_positioner_get_anchor_rect", asc_lua_view_positioner_get_anchor_rect},
  // {"view_positioner_get_offset", asc_lua_view_positioner_get_offset},
  // {"view_positioner_get_anchor", asc_lua_view_positioner_get_anchor},
  // {"view_positioner_get_gravity", asc_lua_view_positioner_get_gravity},
  // {"view_positioner_get_constraint_adjustment", asc_lua_view_positioner_get_constraint_adjustment},

  /* Input API */
  {"set_pointer_position", asc_lua_set_pointer_position},
  // {"", asc_lua_},

  {NULL, NULL}
};

#endif

