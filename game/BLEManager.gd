extends BLEManager

var ble_adapter : BLEAdapter

func _ready():
	ble_adapter = init()
