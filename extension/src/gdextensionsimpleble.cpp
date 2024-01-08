// © Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community
// (CC-BY 3.0)
#include "gdextensionsimpleble.h"
#include "bleperipheralmanager.h"
#include "gdextensionlogger.h"

#include <algorithm>
#include <cstdio>
#include <godot_cpp/core/class_db.hpp>
#include <memory>

using namespace godot;

GDExtensionSimpleBLE::GDExtensionSimpleBLE() {

  std::unique_ptr<BLEPeripheralManager> p{new BLEPeripheralManager()};
  peripheralManager_ = std::move(p);
}

GDExtensionSimpleBLE::~GDExtensionSimpleBLE() {}


void GDExtensionSimpleBLE::_bind_methods() {
  // ClassDB::bind_method(D_METHOD("reset"), &GDExtensionSimpleBLE::reset);

  ADD_SIGNAL(
      MethodInfo("print_message", PropertyInfo(Variant::STRING, "message")));
}
