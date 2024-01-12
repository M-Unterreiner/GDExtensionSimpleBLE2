extends BLEAdapter

var ms_to_scan = 2500

func _ready():
	var adapterList = getAdapterList()


func _on_btn_start_scan_button_down():
	start_scan(ms_to_scan)

#
#func _on_found_new_peripheral(message):
	#print(message)


func _on_spin_box_value_changed(ms):
	ms_to_scan = ms


func _on_item_list_item_selected(index):
	var item_list : ItemList = get_node("../BLE GUI/VBoxContainer/ItemList")
	print("Item ", item_list.get_item_text(index) ," selected")
	
