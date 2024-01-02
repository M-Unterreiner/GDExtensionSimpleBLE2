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

// Should return Array
Array GDExtensionSimpleBLE::getAdapterList() {
  Array *myArray = peripheralManager_->getAdapterList();
  return *myArray;
}

// Copied from BLEUtils GDSimpleBLE
PackedByteArray GDExtensionSimpleBLE::stringToByteArray(const SimpleBLE::ByteArray &p_bytes) {
  PackedByteArray l_byte_array;

  char const *l_bytes = p_bytes.c_str();
  for (int l_index = 0; l_index < p_bytes.size(); l_index++) {
    l_byte_array.append(l_bytes[l_index]);
  }

  return l_byte_array;
}

bool GDExtensionSimpleBLE::connectPeripherals(Array peripherals) {
  GDExtensionlogger::log("Entered connectPeripherals");

  if (!peripherals.is_empty()) {
    for (unsigned int i = 0; i < peripherals.size(); i += 1) {
      String peripheral = peripherals[i];
      peripheralManager_->addPeripheral(peripheral.utf8().get_data());
    }
  }

  peripheralManager_->connectAddedPeripherals();

  return true;
}

// TODO: Is always returning true!
bool GDExtensionSimpleBLE::connectService() {
  if (peripheralManager_->connectService()) {
    GDExtensionlogger::log("Connected successfully to service");
    return true;
  } else {
    GDExtensionlogger::log("Connecting to service failed");
    return false;
  }
}

Variant GDExtensionSimpleBLE::readPeripheral() {
  SimpleBLE::ByteArray rx_data = peripheralManager_->readThisPeripheral(this);

  if(peripheralManager_->isReadDataEmpty(rx_data)){
    GDExtensionlogger::log("Read data is empty");
    return stringToByteArray(rx_data);
  }

  return stringToByteArray(rx_data);
};

void GDExtensionSimpleBLE::disconnectThisPeripheral(
    SimpleBLE::Peripheral &peripheral){};

void GDExtensionSimpleBLE::_bind_methods() {
  // ClassDB::bind_method(D_METHOD("reset"), &GDExtensionSimpleBLE::reset);
  ClassDB::bind_method(D_METHOD("getAdapterList"),
                       &GDExtensionSimpleBLE::getAdapterList);
  ClassDB::bind_method(D_METHOD("connectPeripherals", "peripherals"),
                       &GDExtensionSimpleBLE::connectPeripherals);
  ClassDB::bind_method(D_METHOD("connectService"),
                       &GDExtensionSimpleBLE::connectService);
  ClassDB::bind_method(D_METHOD("readPeripheral"),
                       &GDExtensionSimpleBLE::readPeripheral);
  ADD_SIGNAL(
      MethodInfo("print_message", PropertyInfo(Variant::STRING, "message")));
}
