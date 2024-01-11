#ifndef BLEPERIPHERALMANAGER_H
#define BLEPERIPHERALMANAGER_H
#pragma once

#include "bleperipheral.h"
#include <memory>

#include "bleadapter.h"
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <simpleble/SimpleBLE.h>
#include <simpleble/Utils.h>

#include <string>
#include <vector>

using namespace godot;

class BLEPeripheralManager : public RefCounted{
    GDCLASS(BLEPeripheralManager, RefCounted);

private:
  std::unique_ptr<BLEAdapter> adapter_;
  std::vector<BLEPeripheral> addedPeripherals_;
  //std::vector<std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID>> uuidPeripheral1;
  SimpleBLE::Peripheral scanForThisPeripheral(std::string wantedPeripheral);
  BLEPeripheral* getPeripheralByName(std::string peripheralName);
  bool isThisPeripheralConnected(BLEPeripheral* peripheral);

protected:
  static void _bind_methods();

public:
  void scanPeripherals();
  bool addPeripheral(std::string wantedPeripheral);
    std::vector<SimpleBLE::Peripheral> getListOfPeripherals(SimpleBLE::Adapter *adapter);
    bool connectThisPeripheral(BLEPeripheral* peripheral);
    bool isThisDeviceConnected(SimpleBLE::Peripheral& peripheral);
    Array* getAdapterList();
    bool connectAddedPeripherals();
    bool connectService();
    SimpleBLE::ByteArray readThisPeripheral(std::string peripheralName);
    bool isReadDataEmpty(SimpleBLE::ByteArray rx_data);

    std::vector<std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID>>
    getServicesOfPeripheral(SimpleBLE::Peripheral& peripheral);

    BLEPeripheralManager();
    ~BLEPeripheralManager();
  };
  #endif // BLEPERIPHERALMANAGER_H
