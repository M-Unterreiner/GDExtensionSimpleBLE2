#include "bleservice.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <memory>


BLEService::BLEService() {
    // Clean up your service and characteristic here
}

BLEService::BLEService(SimpleBLE::Service& service, SimpleBLE::Characteristic& characteristic){
  characteristic_ = std::make_shared<SimpleBLE::Characteristic>(characteristic);
  service_ = std::make_shared<SimpleBLE::Service>(service);
  setUUIDs();
}

BLEService::~BLEService() {
    // Clean up your service and characteristic here
}

void BLEService::setUUIDs() {
  String service = service_->uuid().c_str();
  uuids_.append(service);
  String characteristic = characteristic_->uuid().c_str();
  uuids_.append(characteristic);
  UtilityFunctions::print("UUIDs were set: ", service, "; ", characteristic);
}


Array BLEService::getUUIDsInArray() {
  return uuids_;
}

bool BLEService::can_notify() {
    return characteristic_->can_notify();
}

bool BLEService::can_read() {
    return characteristic_->can_read();
}

void BLEService::_bind_methods() {
  //ClassDB::bind_method(D_METHOD("get_uuids"), &BLEService::getUUIDsInArray);
  ClassDB::bind_method(D_METHOD("get_uuids"), &BLEService::getUUIDsInArray);
  ClassDB::bind_method(D_METHOD("can_notiy"), &BLEService::can_notify);
  ClassDB::bind_method(D_METHOD("can_read"), &BLEService::can_read);
}
