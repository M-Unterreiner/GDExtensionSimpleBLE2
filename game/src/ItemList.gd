extends ItemList


#func _on_ble_adapter_found_new_peripheral(peripheral):
	#print(peripheral)
	#add_item(peripheral)


func _on_ble_adapter_started_scan():
	clear()


func _on_ble_peripheral_manager_new_peripheral_stored():
	var peripheral_manager : Node = get_node("../../../ble_peripheral_manager")
	for peripheral in peripheral_manager.peripherals_:
		add_item(peripheral.identifier())
