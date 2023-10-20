extends Node

var ble : GDExtensionSimpleBLE
var data
var peripherals : Array = ["2_Device"]  
func _ready() -> void:
	ble = GDExtensionSimpleBLE.new()
	ble.print_message.connect(_print_message)
	ble.connectPeripherals(peripherals)
	ble.connectService()
	
	
func _process(delta):
	while(true):
		var data : PackedByteArray= ble.readPeripheral()
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
	
	
