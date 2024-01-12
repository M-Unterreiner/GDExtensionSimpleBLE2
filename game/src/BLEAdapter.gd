extends BLEAdapter

func _ready():
	var adapterList = getAdapterList()


func _on_btn_start_scan_button_down():
	start_scan(2500)
