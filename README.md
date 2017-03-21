# Asc
### A simple compositor

I felt like trying Wayland. There were no compositors I liked. I'd been
wanting to try writing a WM. Hence, asc.

Asc uses [wlc][wlc] for handling the boring stuff, meaning it can
dedicate its precious lines of code to making cool stuff happen with
your windows.

## Status

In a few hundred lines of code, I've got something that can run Lua
code and host both Wayland and X11 programs. X11 compatibility is
achieved through Xwayland.

[wlc]: https://github.com/Cloudef/wlc

