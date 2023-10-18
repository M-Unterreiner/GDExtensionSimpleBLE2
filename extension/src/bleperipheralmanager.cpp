// © Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community
// (CC-BY 3.0)
#include "bleperipheralmanager.h"
#include "bleadapter.h"
#include <memory>

#include "gdextensionlogger.h"

using namespace godot;

BLEPeripheralManager::BLEPeripheralManager() {
  std::unique_ptr<BLEAdapter> newAdapter {new BLEAdapter()};
  adapter_ = std::move(newAdapter); 
};

BLEPeripheralManager::~BLEPeripheralManager(){};

void BLEPeripheralManager::scanPeripherals() {
  GDExtensionlogger::log("ScanPeripheral");

  adapter_->scanPeripherals();
};

Array* BLEPeripheralManager::getAdapterList(){
  return adapter_->getAdapterList();

}


SimpleBLE::Peripheral BLEPeripheralManager::scanForThisPeripheral(std::string wantedPeripheral) {
  GDExtensionlogger::log("Entered scanForThisPeripheral");

  bool isNotPeripheralFound = true;

  while (isNotPeripheralFound) {
    scanPeripherals();

    std::vector<SimpleBLE::Peripheral> peripherals = adapter_->getScanResults();

    if (!peripherals.empty()) {
      GDExtensionlogger::log("scanforThisPeripheral: Following peripheral were found:");
      for (SimpleBLE::Peripheral peripheral : peripherals) {
        GDExtensionlogger::log(peripheral.identifier().c_str());
        std::string identifier = peripheral.identifier();

        if (identifier == wantedPeripheral) {
          GDExtensionlogger::log("scanforThisPeripheral: wanted peripheral was found.");
          return peripheral;
        }
      }
    }
  }
  return SimpleBLE::Peripheral();
};

//TODO: Need to handle empty peripherals
bool BLEPeripheralManager::addPeripheral(std::string wantedPeripheral){
  GDExtensionlogger::log("Entered addPeripheral");  

  std::vector<SimpleBLE::Peripheral> pairedPeripherals = adapter_->getPairedPeripherals();

  for (auto & peripheral : pairedPeripherals){
    std::string message = "Compare " + peripheral.identifier() + " with " + wantedPeripheral;
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

bool BLEPeripheralManager::connectAddedPeripherals(){
  GDExtensionlogger::log("Connect added peripherals");
  if (!addedPeripherals_.empty()){
     for (auto & peripheral : addedPeripherals_) {
        if (!isThisPeripheralConnected(peripheral)){
          connectThisPeripheral(peripheral);
        }
      }
    return true;
  } else {
    GDExtensionlogger::log("No peripherals were added");
    return false;
  }
};

bool BLEPeripheralManager::connectThisPeripheral(
    SimpleBLE::Peripheral& peripheral) {
  GDExtensionlogger::log("ConnectThisPeripheral");
  try {
    peripheral.connect();
    return true;
  } catch (std::exception &l_exception) {
    GDExtensionlogger::log("Couldn't connect to peripheral");
    return false;
  }
};


// TODO Implement correct!
bool BLEPeripheralManager::connectService() {
  GDExtensionlogger::log("Entered connectService - WHICH IS NOT CORRECTLY IMPLEMENTED");

  uuidPeripheral1 = getServicesOfPeripheral(addedPeripherals_[0]);

  return true;
};


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

SimpleBLE::ByteArray BLEPeripheralManager::readPeripheral() {
  SimpleBLE::ByteArray rx_data = addedPeripherals_[0].read(uuidPeripheral1[1].first, uuidPeripheral1[1].second);
  return rx_data;
};

bool BLEPeripheralManager::isThisPeripheralConnected(SimpleBLE::Peripheral &peripheral) {
  if(peripheral.is_connected()){
    return true;
  }
  return false;
};

/*
// Needs to be fixed
std::vector<SimpleBLE::Peripheral>
GDExtensionSimpleBLE::getListOfPeripherals(SimpleBLE::Adapter *adapter) {
  return std::vector<SimpleBLE::Peripheral>{};
};



*/
