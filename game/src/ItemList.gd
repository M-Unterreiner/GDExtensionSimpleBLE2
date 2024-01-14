extends ItemList

@onready
var peripheral_manager = get_node("../../../ble_peripheral_manager")

func init_new_item(peripheral : BLEPeripheral):
	var icon : Texture2D = load("res://icons/bluetooth.svg")
	var id = add_item(peripheral.identifier(),icon)

func _on_ble_peripheral_manager_new_peripheral_stored():
	for peripheral in peripheral_manager.peripherals_:
		init_new_item(peripheral)


func _on_ble_peripheral_manager_cleared_stored_peripherals():
	clear()
