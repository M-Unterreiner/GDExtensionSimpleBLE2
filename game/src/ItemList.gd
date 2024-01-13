extends ItemList


#func _on_ble_adapter_found_new_peripheral(peripheral):
	#print(peripheral)
	#add_item(peripheral)


func _on_ble_adapter_started_scan():
	clear()
