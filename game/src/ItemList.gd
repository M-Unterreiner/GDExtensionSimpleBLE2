extends ItemList

@onready
var peripheral_manager = get_node("../../../ble_peripheral_manager")

func init_new_item(peripheral : BLEPeripheral):
	var icon : Texture2D = load("res://icons/bluetooth.svg")
	var id = add_item(peripheral.identifier(),icon)
	set_item_custom_bg_color(id,Color.DARK_RED)
	connect_peripheral_to_signals(peripheral)

func _on_ble_peripheral_manager_new_peripheral_stored():
	for peripheral in peripheral_manager.peripherals_:
		init_new_item(peripheral)


func connect_peripheral_to_signals(peripheral : BLEPeripheral):
	print_debug("Connect ", peripheral.identifier(), " to signals.")
	#if (peripheral.is_connected("peripheral_is_connected", _on_peripheral_is_connected)):
	peripheral.connect("peripheral_is_connected", _on_peripheral_is_connected)
	#if (peripheral.is_connected("peripheral_is_disconnected", _on_peripheral_is_disconnected)):
	peripheral.connect("peripheral_is_disconnected", _on_peripheral_is_disconnected)


func _on_ble_peripheral_manager_cleared_stored_peripherals():
	clear()


func _on_peripheral_is_connected(identifier : String):
	print_debug(identifier, " connected.")
	change_color_of_itemtext_to(identifier, Color.DARK_GREEN)
	


func _on_peripheral_is_disconnected(identifier : String):
	print_debug(identifier, " disconnected.")
	change_color_of_itemtext_to(identifier, Color.DARK_RED)


## TODO: When change colour back, the ListItem is not updated.
func change_color_of_itemtext_to(itemtext : String, colour : Color):
	for idx in range(item_count): 
		if (get_item_text(idx) == itemtext):
			set_item_custom_bg_color(idx, colour)
