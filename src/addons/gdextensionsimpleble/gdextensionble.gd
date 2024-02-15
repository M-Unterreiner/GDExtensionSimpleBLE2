extends Window

signal data_received(data : String)

## GDExtensionSimpleBLE menu display style.
enum Style {
	HIDDEN,  ## menu is hidden.
	VISIBLE, ## menu is visible
	FULL,    ## menu is fullscreen
}

## The style to use when drawing the GDExtensionSimpleBLE menu.
var style := Style.HIDDEN:
	set(value):
		style = value
		match style:
			Style.HIDDEN:
				visible = false
			Style.VISIBLE:
				visible = true
				mode = Window.MODE_WINDOWED
			Style.FULL:
				visible = true
				mode = Window.MODE_FULLSCREEN

func _init() -> void:
	# This must be done here instead of `_ready()` to avoid having `visibility_changed` be emitted immediately.
	visible = true

	if not InputMap.has_action("cycle_gdextensionsimpleble_menu"):
		# Create default input action if no user-defined override exists.
		# We can't do it in the editor plugin's activation code as it doesn't seem to work there.
		InputMap.add_action("cycle_gdextensionsimpleble_menu")
		var event := InputEventKey.new()
		event.keycode = KEY_F4
		InputMap.action_add_event("cycle_gdextensionsimpleble_menu", event)
		print_debug("Action was added")


func _input(event: InputEvent) -> void:
	if event.is_action_pressed("cycle_gdextensionsimpleble_menu"):
		print_debug("Pressed F4")
		style = wrapi(style + 1, 0, Style.FULL) as Style


func _on_ble_peripheral_manager_data_received(data):
	data_received.emit(data)
