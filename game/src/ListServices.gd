extends ItemList


func connect_peripheral_to_signals(peripheral : BLEPeripheral):
	print_debug("Connect ", peripheral.identifier(), " to service signals.")
	#if (peripheral.is_connected("peripheral_is_connected", _on_peripheral_is_connected)):
	peripheral.connect("services_send", _on_service_send)
	#if (peripheral.is_connected("peripheral_is_disconnected", _on_peripheral_is_disconnected)):
	#peripheral.connect("peripheral_is_disconnected", _on_peripheral_is_disconnected)

func _on_service_send():
	print_debug("Services were emitted and received")

