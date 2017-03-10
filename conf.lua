-- An example Asc config file

Asc.on("view_created", function (view)
  output = Asc.lowlevel.view_get_output(view)
  mask = Asc.lowlevel.output_get_mask(output)
  Asc.lowlevel.view_set_mask(view, mask) -- Display the window

  Asc.lowlevel.view_bring_to_front(view)

  return true
end)

Asc.on("view_focus", function (view, focus)
  Asc.lowlevel.view_set_state(view, Asc.const.ACTIVATED)
end)

Asc.on("pointer_motion", function (window, time, pos)
  Asc.lowlevel.view_focus(window)
  Asc.lowlevel.set_pointer_position(pos.x, pos.y)
  return false
end)

Asc.exec("st", {})
-- Asc.exec("echo", {"abc"})

