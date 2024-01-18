#pragma once

#include <godot_cpp/classes/ref.hpp>
#include <simpleble/SimpleBLE.h>
#include <simpleble/Utils.h>

using namespace godot;

class BLEUtils {
public:
  static PackedByteArray stringToByteArray(const SimpleBLE::ByteArray &p_bytes);
};
