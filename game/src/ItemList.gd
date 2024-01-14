extends ItemList

@onready
var peripheral_manager = get_node("../../../ble_peripheral_manager")


func _on_ble_peripheral_manager_new_peripheral_stored():
	for peripheral in peripheral_manager.peripherals_:
		add_item(peripheral.identifier())


func _on_ble_peripheral_manager_cleared_stored_peripherals():
	clear()
