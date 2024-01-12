extends BLEAdapter

func _ready():
	var adapterList = getAdapterList()


func _on_btn_start_scan_button_down():
	scanPeripherals(5000)


func _on_btn_stop_scan_button_down():
	pass # Replace with function body.
