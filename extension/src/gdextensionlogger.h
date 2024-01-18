#pragma once

#include <godot_cpp/classes/ref.hpp>

using namespace godot;

class GDExtensionlogger {

public:
  GDExtensionlogger();
  ~GDExtensionlogger();

  static void log(String message);
};
