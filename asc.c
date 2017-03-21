#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <wlc/wlc.h>

#include "lua_api.h"

lua_State *l; /* Has to be global, as it's used in callbacks */

/* To group things as a single arg, without using parens */
#define _(...) __VA_ARGS__

/* To check if a string is equal to "bool" */
#define ISBOOL(a) (strcmp(a, "bool") == 0)

#define CREATE_CALLBACK_HANDLER(name, rettype, defaultret, errret, nargs, args, pushargs) \
  static rettype name(args) { \
    switch (asc_lua_push_callback(l, #name)) { \
      case 0: \
        break; \
      case 1: \
        return defaultret; \
      default: \
        fprintf(stderr, "Error: Invalid callback for " #name "\n"); \
        return errret; \
    } \
    \
    pushargs; \
    \
    if (asc_lua_call_safely(l, nargs, ISBOOL(#rettype))) return errret; \
    \
    if (ISBOOL(#rettype)) { \
      if (!lua_isboolean(l, -1)) { \
        fprintf(stderr, "Error: " #name " callback did not return a boolean\n"); \
        return errret; \
      } \
      bool retval = lua_toboolean(l, -1); \
      lua_pop(l, 1); \
      return retval; \
    } else return; \
  }

/* Output Callbacks */
CREATE_CALLBACK_HANDLER(output_created, bool, true, false, 1,
    _(wlc_handle output),
    asc_lua_push_handle(l, output))

CREATE_CALLBACK_HANDLER(output_destroyed, bool, true, false, 1,
    _(wlc_handle output),
    asc_lua_push_handle(l, output))

CREATE_CALLBACK_HANDLER(output_focus, bool, true, false, 2,
    _(wlc_handle output, bool focus),
    do {
      asc_lua_push_handle(l, output);
      lua_pushboolean(l, focus);
    } while (0))

CREATE_CALLBACK_HANDLER(output_resolution, bool, true, false, 3,
    _(wlc_handle output, const struct wlc_size *from, const struct wlc_size *to),
    do {
      asc_lua_push_handle(l, output);
      asc_lua_push_size(l, from);
      asc_lua_push_size(l, to);
    } while (0))

CREATE_CALLBACK_HANDLER(output_render_pre, bool, true, false, 1,
    _(wlc_handle output),
    asc_lua_push_handle(l, output))

CREATE_CALLBACK_HANDLER(output_render_post, bool, true, false, 1,
    _(wlc_handle output),
    asc_lua_push_handle(l, output))

CREATE_CALLBACK_HANDLER(output_context_created, bool, true, false, 1,
    _(wlc_handle output),
    asc_lua_push_handle(l, output))

CREATE_CALLBACK_HANDLER(output_context_destroyed, bool, true, false, 1,
    _(wlc_handle output),
    asc_lua_push_handle(l, output))

/* View Callbacks */
CREATE_CALLBACK_HANDLER(view_created, bool, true, false, 1,
    _(wlc_handle view),
    asc_lua_push_handle(l, view))

CREATE_CALLBACK_HANDLER(view_destroyed, bool, true, false, 1,
    _(wlc_handle view),
    asc_lua_push_handle(l, view))

CREATE_CALLBACK_HANDLER(view_focus, void, false, false, 2,
    _(wlc_handle view, bool focus),
    do {
      asc_lua_push_handle(l, view);
      lua_pushboolean(l, focus);
    } while (0))

/* Input Callbacks */
CREATE_CALLBACK_HANDLER(pointer_motion, bool, false, false, 3,
    _(wlc_handle view, uint32_t time, const struct wlc_point *pos),
    do {
      asc_lua_push_handle(l, view);
      lua_pushnumber(l, time);
      asc_lua_push_point(l, pos);
    } while (0))


int get_unused_X_display() {
  char filename[15];
  int i = -1;
  do {
    i++;
    if (i > 999) return -1;
    snprintf(filename, sizeof(filename), "/tmp/.X%d-lock", i);
  } while (access(filename, F_OK) == -1);

  return i;
}

int start_xwayland() {
  int display = get_unused_X_display();
  if (display < 0) return -1;

  char display_str[4];
  snprintf(display_str, sizeof(display_str), ":%d", display);

  wlc_exec("Xwayland", (char *const[]){ "Xwayland", display_str, "-rootless", NULL });
  setenv("DISPLAY", display_str, 1); /* For children */

  return 0;
}

int main(int argc, char *argv[]) {
  wlc_set_output_created_cb(output_created);
  wlc_set_view_created_cb(view_created);
  wlc_set_view_focus_cb(view_focus);
  wlc_set_pointer_motion_cb(pointer_motion);

  if (!wlc_init())
    return EXIT_FAILURE;

  if (!(l = asc_lua_init()))
    return EXIT_FAILURE;

  luaL_dofile(l, "conf.lua");

  start_xwayland();

  wlc_run();

  lua_close(l);

  return EXIT_SUCCESS;
}

