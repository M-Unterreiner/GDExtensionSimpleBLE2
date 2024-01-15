extends ItemList


func connect_peripheral_to_signals(peripheral : BLEPeripheral):
	print_debug("Connect ", peripheral.identifier(), " to service signals.")
	#if (peripheral.is_connected("peripheral_is_connected", _on_peripheral_is_connected)):
	peripheral.connect("services_send", _on_services_send)
	print_debug("Is connected to services_send: ", peripheral.is_connected("services_send", _on_services_send))
	#if (peripheral.is_connected("peripheral_is_disconnected", _on_peripheral_is_disconnected)):
	#peripheral.connect("peripheral_is_disconnected", _on_peripheral_is_disconnected)

func _on_services_send(services : Array):
	print_debug("Received services: ", services)
	for service : BLEService in services:
		var uuids = service.getUUIDsInArray()
		var uuids_string = uuids[0] +":" +  uuids[1]
		add_item(uuids_string)
		

