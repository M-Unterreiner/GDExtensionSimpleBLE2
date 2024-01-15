extends ItemList



func connect_service_to_signals(service : BLEPeripheral):
	print_debug("Connect ", peripheral.identifier(), " to signals.")
	#if (peripheral.is_connected("peripheral_is_connected", _on_peripheral_is_connected)):
	peripheral.connect("peripheral_is_connected", _on_peripheral_is_connected)
	#if (peripheral.is_connected("peripheral_is_disconnected", _on_peripheral_is_disconnected)):
	peripheral.connect("peripheral_is_disconnected", _on_peripheral_is_disconnected)
