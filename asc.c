#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wlc/wlc.h>

static bool view_created(wlc_handle view) {
   wlc_view_set_mask(view, wlc_output_get_mask(wlc_view_get_output(view)));
   wlc_view_bring_to_front(view);
   // wlc_view_focus(view);
   return true;
}

static void view_focus(wlc_handle view, bool focus) {
   wlc_view_set_state(view, WLC_BIT_ACTIVATED, focus);
}

static bool pointer_motion(wlc_handle view, uint32_t time, const struct wlc_point *pos) {
  wlc_view_focus(view);
  wlc_pointer_set_position(pos);
  return false;
}

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
  puts(display_str);
  setenv("DISPLAY", display_str, 1); // For children

  return 0;
}

int main(int argc, char *argv[]) {
   wlc_set_view_created_cb(view_created);
   wlc_set_view_focus_cb(view_focus);
   wlc_set_pointer_motion_cb(pointer_motion);

   if (!wlc_init())
      return EXIT_FAILURE;

   start_xwayland();
   wlc_exec("weston-terminal", (char *const[]){ "weston-terminal", NULL });

   wlc_run();
   return EXIT_SUCCESS;
}

