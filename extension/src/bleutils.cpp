#include "bleutils.h"

// Copied from BLEUtils GDSimpleBLE
PackedByteArray
BLEUtils::stringToByteArray(const SimpleBLE::ByteArray &p_bytes) {
  PackedByteArray l_byte_array;

  char const *l_bytes = p_bytes.c_str();
  for (int l_index = 0; l_index < p_bytes.size(); l_index++) {
    l_byte_array.append(l_bytes[l_index]);
  }

  return l_byte_array;
}
