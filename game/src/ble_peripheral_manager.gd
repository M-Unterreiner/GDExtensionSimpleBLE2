extends Node

## This node is responsible for holding all the BLEPeripherals
var peripherals_ : Array = []

signal new_peripheral_stored
signal cleared_stored_peripherals

func _on_ble_adapter_found_new_peripheral(id):
	var new_peripheral : BLEPeripheral = instance_from_id(id)
	print("Created new peripheral with id:", new_peripheral.get_instance_id())
	store_new_peripheral(new_peripheral)
	
func store_new_peripheral(new_peripheral : BLEPeripheral):
	peripherals_.append(new_peripheral)
	print(new_peripheral.identifier())
	emit_signal("new_peripheral_stored")


func _on_ble_adapter_started_scan():
	peripherals_.clear()
	emit_signal("cleared_stored_peripherals")
