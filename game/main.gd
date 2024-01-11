extends Node

var ble_manager : GDExtensionSimpleBLE
var data
var device_2 : String = "2_Device"
var peripherals : Array = [device_2]
 
func _ready() -> void:
	ble_manager = GDExtensionSimpleBLE.new()
	ble_manager.print_message.connect(_print_message)
	var ble_adapter : BLEAdapter = BLEAdapter.new()
	
func string_to_quaternion(data : String):
	if (data.length() > 0):
		var sArray : PackedFloat64Array = data.split_floats(",",false)
		var quat : Quaternion = Quaternion(sArray[0],sArray[1],sArray[2],sArray[3])
		return quat
	return Quaternion.IDENTITY
	
func _print_message(message):
	print(message)
	
	
