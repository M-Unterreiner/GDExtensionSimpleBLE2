extends Node

# This node is responsible for holding all the BLEPeripherals
var peripherals_ : Array = []

func _on_ble_adapter_found_new_peripheral(id):
	var new_peripheral : BLEPeripheral = instance_from_id(id)
	print("Created new peripheral with id:", new_peripheral.get_instance_id())
