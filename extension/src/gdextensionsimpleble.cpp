// © Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community
// (CC-BY 3.0)
#include "gdextensionsimpleble.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

GDExtensionSimpleBLE::GDExtensionSimpleBLE() { count = 0; }

GDExtensionSimpleBLE::~GDExtensionSimpleBLE() {}

void GDExtensionSimpleBLE::add(int p_value) { count += p_value; }

void GDExtensionSimpleBLE::reset() { count = 0; }

int GDExtensionSimpleBLE::get_total() const { return count; }

void GDExtensionSimpleBLE::_bind_methods() {
  ClassDB::bind_method(D_METHOD("add", "value"), &GDExtensionSimpleBLE::add,
                       DEFVAL(1));
  ClassDB::bind_method(D_METHOD("reset"), &GDExtensionSimpleBLE::reset);
  ClassDB::bind_method(D_METHOD("get_total"), &GDExtensionSimpleBLE::get_total);
}
