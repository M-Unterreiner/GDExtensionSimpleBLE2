extends Node

## This node is responsible for holding all the BLEPeripherals
var peripherals_ : Array = []
var selected_peripheral_ : BLEPeripheral = null
var selected_peripheral_services : Array
var selected_service_ : BLEService = null

var maximum_attempts : int = 5

var is_reconnect_active = true

@onready
var list_of_services : ItemList = get_node("../BLEUI/ListServices")


signal new_peripheral_stored
signal cleared_stored_peripherals
signal updated_peripheral_services(selected_peripehral_services : Array)
signal data_received(data : String)
signal peripheral_disconnected(identifier : String)

func _on_ble_adapter_found_new_peripheral(id):
	var new_peripheral : BLEPeripheral = instance_from_id(id)
	#new_peripheral.init_services()
	store_new_peripheral(new_peripheral)
	
func store_new_peripheral(new_peripheral : BLEPeripheral):
	peripherals_.append(new_peripheral)
	emit_signal("new_peripheral_stored")


func _on_ble_adapter_started_scan():
	peripherals_.clear()
	emit_signal("cleared_stored_peripherals")

func connect_peripheral(peripheral : BLEPeripheral):
	if (!peripheral.is_peripheral_connected()):
		peripheral.connect_peripheral()
		peripheral.init_services()
	else:
		print_debug(peripheral.identifier(), " is already connected")
		peripheral.init_services()
		peripheral.emit_signal("peripheral_is_connected", peripheral.identifier())


func _on_item_list_item_selected(index):
	var peripheral_list : ItemList = get_node("../BLEUI/VBoxContainer/ListPeripherals")
	for peripheral : BLEPeripheral in peripherals_:
		var id = peripheral.get_instance_id()
		if(peripheral.identifier() == peripheral_list.get_item_text(index)):
			select_peripheral(id)


func select_peripheral(id : int):
	selected_peripheral_ = instance_from_id(id)
	print_debug(selected_peripheral_.identifier() ," was selected.")
	connect_peripheral(selected_peripheral_)
	connect_peripheral_to_signals(selected_peripheral_)
	selected_peripheral_.emit_services()


func connect_peripheral_to_signals(peripheral : BLEPeripheral):
	print_debug("Connect ", peripheral.identifier(), " to service signals.")
	peripheral.connect("services_send", _on_services_send)
	peripheral.connect("received_data", _on_received_data)
	peripheral.connect("peripheral_is_disconnected", _on_peripheral_is_disconnected)
	print_debug("Is connected to services_send: ", peripheral.is_connected("services_send", _on_services_send))

func _on_services_send(services : Array):
	selected_peripheral_services = services
	emit_signal("updated_peripheral_services",selected_peripheral_services)


func _on_list_services_item_selected(index):
	selected_service_ = selected_peripheral_services[index]
	print_debug(selected_service_.get_uuids())


func _on_received_data(data : String):
	call_deferred("emit_signal","data_received", data)


func _on_button_subscribe_button_up():
	var uuids = selected_service_.get_uuids()
	selected_peripheral_.subscribe(uuids[0],uuids[1])


func _on_button_unsubscribe_button_down():
	var uuids = selected_service_.get_uuids() 
	selected_peripheral_.unsubscribe(uuids[0],uuids[1])

func _get_peripheral_in_peripherals(identifier : String) -> BLEPeripheral:
	for peripheral in peripherals_:
		if (peripheral.identifier() == identifier):
			return peripheral
	return null

func try_to_reconnect(peripheral : BLEPeripheral):
	var attempts : int = 0
	while attempts != maximum_attempts:
		print_debug(attempts)
		attempts += 1
		connect_peripheral(peripheral)
		if peripheral.is_peripheral_connected():
			break
		

func _on_peripheral_is_disconnected(identifier : String):
	var peripheral : BLEPeripheral = _get_peripheral_in_peripherals(identifier)
	print_debug("Try to reconnect: ", peripheral.identifier())
	
	if (peripheral and is_reconnect_active):
		try_to_reconnect(peripheral)
	if not is_reconnect_active:
		peripheral_disconnected.emit(identifier)
		


func _on_check_button_toggled(toggled_on):
	is_reconnect_active = toggled_on
