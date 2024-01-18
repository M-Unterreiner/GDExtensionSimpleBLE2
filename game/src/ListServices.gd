extends ItemList

func _on_btn_start_scan_button_down():
	clear()


func _on_ble_peripheral_manager_updated_peripheral_services(services : Array):
	clear()
	print_debug("Received services: ", services)
	for service : BLEService in services:
		var uuids : Array= service.get_uuids()
		print_debug(service.get_uuids())
		var uuids_string = uuids[0] +":" +  uuids[1]
		add_item(uuids_string)
