# Asc
### A simple compositor

I felt like trying Wayland. There were no compositors I liked. I'd been
wanting to try writing a WM. Hence, asc.

Asc uses [wlc][wlc] for handling the boring stuff, meaning it can
dedicate its precious lines of code to making cool stuff happen with
your windows.

## Status

In under 50 lines of code, I've got something that can run both native
Wayland programs and X11 programs via Xwayland (which is automatically
launched on startup).

Nothing else is implemented apart from the focus following the mouse
cursor.

In other words, this is currently a tiny proof of concept that can just
about run a terminal.

[wlc]: https://github.com/Cloudef/wlc

