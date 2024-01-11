#pragma once

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <simpleble/SimpleBLE.h>
#include <simpleble/Utils.h>

using namespace godot;


class BLEManager : public RefCounted{
    GDCLASS(BLEManager, RefCounted);


protected:
  static void _bind_methods();

public:
  BLEManager();
  ~BLEManager();
};
