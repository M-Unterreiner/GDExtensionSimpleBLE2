extends BLEManager

var ble_adapter

func _ready():
	ble_adapter = init()
