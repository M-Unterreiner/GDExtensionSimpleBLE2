extends Node
class utility:
	
	func string_to_quaternion(data : String) -> Quaternion:
		if (data.length() > 0):
			var sArray : PackedFloat64Array = data.split_floats(",",false)
			var quat : Quaternion = Quaternion(sArray[0],sArray[1],sArray[2],sArray[3])
			return quat
		return Quaternion.IDENTITY
