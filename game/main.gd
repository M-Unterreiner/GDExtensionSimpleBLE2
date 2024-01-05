extends Node

var ble_manager : GDExtensionSimpleBLE
var data
var device_2 : String = "2_Device"
var peripherals : Array = [device_2]
 
func _ready() -> void:
	ble_manager = GDExtensionSimpleBLE.new()
	ble_manager.print_message.connect(_print_message)
	ble_manager.connectPeripherals(peripherals)
	ble_manager.connectService()
	
	
func _process(delta):
	while(true):
		var data : PackedByteArray= ble_manager.readPeripheral(device_2)
		var quat = string_to_quaternion(data.get_string_from_ascii())
		if(quat != Quaternion.IDENTITY):
			print(quat)


func string_to_quaternion(data : String):
	if (data.length() > 0):
		var sArray : PackedFloat64Array = data.split_floats(",",false)
		var quat : Quaternion = Quaternion(sArray[0],sArray[1],sArray[2],sArray[3])
		return quat
	return Quaternion.IDENTITY
	
func _print_message(message):
	print(message)
	
	
