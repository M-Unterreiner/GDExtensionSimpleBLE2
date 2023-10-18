#ifndef GDEXTENSIONLOGGER_H
#define GDEXTENSIONLOGGER_H

#include <godot_cpp/classes/ref.hpp>

using namespace godot;

class GDExtensionlogger {

public:
  GDExtensionlogger();
  ~GDExtensionlogger();

  static void log(String message);
};
#endif // GDEXTENSIONLOGGER_H
