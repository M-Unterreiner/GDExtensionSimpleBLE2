#include "gdextensionlogger.h"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

GDExtensionlogger::GDExtensionlogger(){};

GDExtensionlogger::~GDExtensionlogger(){};

void GDExtensionlogger::log(String message) {
  UtilityFunctions::print(message);
};
