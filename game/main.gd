extends Node

var ble : GDExtensionSimpleBLE
var data

func _ready() -> void:
	ble = GDExtensionSimpleBLE.new()
#	print(ble.getAdapterList())
#
#
#	ble.print_message.connect(_print_message)
#
#	var adapterList : Array= ble.getAdapterList()
#	print(adapterList.size())
#	for adapter in adapterList:
#		print(adapter)
#
	ble.connectPeripherals()
#
	ble.connectService()
	
	
	
func _process(delta):
	var i = 0


	while(true):
		var data : PackedByteArray= ble.readPeripheral()
		var quat = string_to_quaternion(data.get_string_from_ascii())
		print(quat)


func string_to_quaternion(data : String):
	var sArray : PackedFloat64Array = data.split_floats(",",false)
	var quat : Quaternion = Quaternion(sArray[0],sArray[1],sArray[2],sArray[3])
	return quat
	
func _print_message(message):
	print(message)
	
	
