extends Control

func _ready():
	pass

func _on_ble_adapter_update_adapters(updated_adapters):
	print(updated_adapters)
