#ifndef GDBLEUTILS_CLASS_H
#define GDBLEUTILS_CLASS_H

#include <godot_cpp/classes/ref.hpp>
#include <simpleble/SimpleBLE.h>
#include <simpleble/Utils.h>

using namespace godot;

class BLEUtils {
public:
  static PackedByteArray stringToByteArray(const SimpleBLE::ByteArray &p_bytes);
};
#endif // GDBLEUTILS_CLASS_H
