extends Node

## This node is responsible for holding all the BLEPeripherals
var peripherals_ : Array = []
var selected_peripheral_ : BLEPeripheral = null

signal new_peripheral_stored
signal cleared_stored_peripherals

func _on_ble_adapter_found_new_peripheral(id):
	var new_peripheral : BLEPeripheral = instance_from_id(id)
	print_debug("Created new peripheral with id:", new_peripheral.get_instance_id())
	store_new_peripheral(new_peripheral)
	
func store_new_peripheral(new_peripheral : BLEPeripheral):
	peripherals_.append(new_peripheral)
	print_debug(new_peripheral.identifier(), ":", new_peripheral.get_instance_id())
	emit_signal("new_peripheral_stored")


func _on_ble_adapter_started_scan():
	peripherals_.clear()
	emit_signal("cleared_stored_peripherals")


func _on_item_list_item_selected(index):
	var item_list : ItemList = get_node("../BLE GUI/VBoxContainer/ItemList")
	for peripheral : BLEPeripheral in peripherals_:
		var id = peripheral.get_instance_id()
		if(peripheral.identifier() == item_list.get_item_text(index)):
			selected_peripheral_ = instance_from_id(id)
			print_debug(selected_peripheral_.identifier() ," was selected.")
