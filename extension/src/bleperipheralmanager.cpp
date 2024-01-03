// © Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community
// (CC-BY 3.0)
#include "bleperipheralmanager.h"
#include "bleadapter.h"
#include <memory>

#include "gdextensionlogger.h"

using namespace godot;

BLEPeripheralManager::BLEPeripheralManager() {
  std::unique_ptr<BLEAdapter> newAdapter{new BLEAdapter()};
  adapter_ = std::move(newAdapter);
};

BLEPeripheralManager::~BLEPeripheralManager(){};

// Scan for peripherals
void BLEPeripheralManager::scanPeripherals() {
  GDExtensionlogger::log("ScanPeripheral");

  adapter_->scanPeripherals();
};

// Get list of adapters which are returned as an array.
Array *BLEPeripheralManager::getAdapterList() {
  return adapter_->getAdapterList();
}

// Scan for this peripheral. Returns the peripheral when found. If not, an empty
// periphal is returned.
SimpleBLE::Peripheral
BLEPeripheralManager::scanForThisPeripheral(std::string wantedPeripheral) {
  GDExtensionlogger::log("Entered scanForThisPeripheral");

  bool isNotPeripheralFound = true;

  while (isNotPeripheralFound) {
    scanPeripherals();

    std::vector<SimpleBLE::Peripheral> peripherals = adapter_->getScanResults();

    if (!peripherals.empty()) {
      GDExtensionlogger::log(
          "scanforThisPeripheral: Following peripheral were found:");
      for (SimpleBLE::Peripheral peripheral : peripherals) {
        GDExtensionlogger::log(peripheral.identifier().c_str());
        std::string identifier = peripheral.identifier();

        if (identifier == wantedPeripheral) {
          GDExtensionlogger::log(
              "scanforThisPeripheral: wanted peripheral was found.");
          return peripheral;
        }
      }
    }
  }
  return SimpleBLE::Peripheral();
};

// TODO: Need to handle empty peripherals
// Search for specified peripheral and add it to addedPeripherals_. Returning
// bool if successful or not
bool BLEPeripheralManager::addPeripheral(std::string wantedPeripheral) {
  GDExtensionlogger::log("Entered addPeripheral");

  std::vector<SimpleBLE::Peripheral> pairedPeripherals =
      adapter_->getPairedPeripherals();

  for (auto &peripheral : pairedPeripherals) {
    std::string message =
        "Compare " + peripheral.identifier() + " with " + wantedPeripheral;
    GDExtensionlogger::log(message.c_str());
    if (peripheral.identifier().compare(wantedPeripheral) == 0) {
      GDExtensionlogger::log("They are equal.");
      addedPeripherals_.push_back(peripheral);
      return true;
    }
  }
  addedPeripherals_.push_back(scanForThisPeripheral(wantedPeripheral));
  return true;
};

// Try to connect peripherals which were added to the addedPeripherals_. Return
// true if successfull.
bool BLEPeripheralManager::connectAddedPeripherals() {
  GDExtensionlogger::log("Connect added peripherals");
  if (!addedPeripherals_.empty()) {
    for (auto &peripheral : addedPeripherals_) {
      if (!isThisPeripheralConnected(&peripheral)) {
        connectThisPeripheral(peripheral);
      }
    }
    return true;
  } else {
    GDExtensionlogger::log("No peripherals were added");
    return false;
  }
};

// Try to connect specified peripheral
bool BLEPeripheralManager::connectThisPeripheral(
    SimpleBLE::Peripheral &peripheral) {
  GDExtensionlogger::log("ConnectThisPeripheral");
  peripheral.connect();
  if (peripheral.is_connected()){
    GDExtensionlogger::log("Connected to peripheral");
    return true;
  } else {
    GDExtensionlogger::log("Couldn't connect to peripheral");
    return false;
  }
};

// TODO Implement correct!
bool BLEPeripheralManager::connectService() {
  GDExtensionlogger::log(
      "Entered connectService - WHICH IS NOT CORRECTLY IMPLEMENTED");

  uuidPeripheral1 = getServicesOfPeripheral(addedPeripherals_[0]);

  return true;
};

// Returns a vector with all services defined by service and characteristic uuid
// of the peripheral.
std::vector<std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID>>
BLEPeripheralManager::getServicesOfPeripheral(
    SimpleBLE::Peripheral &peripheral) {

  // Store all services and characterisitc uuids in a vector
  std::vector<std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID>>
      uuids;

  for (auto service : peripheral.services()) {
    for (auto characteristic : service.characteristics()) {
      uuids.push_back(std::make_pair(service.uuid(), characteristic.uuid()));
    }
  }

  return uuids;
}

// TODO: Write an proper implementation
// Reads only the first service of the list.
SimpleBLE::ByteArray BLEPeripheralManager::readThisPeripheral(std::string peripheralName) {

  SimpleBLE::Peripheral* peripheral = getPeripheralByName(peripheralName);
  SimpleBLE::ByteArray rx_data = SimpleBLE::ByteArray();

  if(peripheral == nullptr){
    GDExtensionlogger::log("BLEPeripheralManager: No data returned, because peripheral was not present");
    return rx_data;
  }

  //SimpleBLE::Peripheral peripheral = addedPeripherals_[0];
  // Needs no check if peripheral is connected, because SimpleBLE::Peripheral does it already.
  rx_data = peripheral->read(uuidPeripheral1[1].first, uuidPeripheral1[1].second);
  return rx_data;
}

// Check if readed data are empty
bool BLEPeripheralManager::isReadDataEmpty(SimpleBLE::ByteArray rx_data){
  SimpleBLE::ByteArray emptyData = SimpleBLE::ByteArray();

  if (rx_data == emptyData){
    return true;
  }
  return false;
}

// Returns peripheral which was added to the peripherals.
// Beware if no peripheral is found it returns a nullptr
SimpleBLE::Peripheral* BLEPeripheralManager::getPeripheralByName(std::string peripheralName){
  for (auto &peripheral : addedPeripherals_) {
    if (peripheral.identifier().compare(peripheralName) == 0) {
      return &peripheral;
    }
  }
  GDExtensionlogger::log("BLEPeripheralManager: No peripheral returned, because peripheral was not present");
  return nullptr;
}

bool BLEPeripheralManager::isThisPeripheralConnected(SimpleBLE::Peripheral* peripheral) {
  if (peripheral->is_connected()) {
    return true;
  }
  return false;
}


/*
// Needs to be fixed
std::vector<SimpleBLE::Peripheral>
GDExtensionSimpleBLE::getListOfPeripherals(SimpleBLE::Adapter *adapter) {
  return std::vector<SimpleBLE::Peripheral>{};
};



*/
