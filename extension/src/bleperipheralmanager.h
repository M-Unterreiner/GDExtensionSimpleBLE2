#ifndef BLEPERIPHERALMANAGER_H
#define BLEPERIPHERALMANAGER_H

#include "bleperipheral.h"
#include <memory>
#pragma once

#include "bleadapter.h"
#include <godot_cpp/classes/ref.hpp>
#include <simpleble/SimpleBLE.h>
#include <simpleble/Utils.h>

#include <string>
#include <vector>

using namespace godot;

class BLEPeripheralManager {

private:
  std::unique_ptr<BLEAdapter> adapter_;
  std::vector<BLEPeripheral> addedPeripherals_;
  std::vector<std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID>>
      uuidPeripheral1;
  SimpleBLE::Peripheral scanForThisPeripheral(std::string wantedPeripheral);
  SimpleBLE::Peripheral* getPeripheralByName(std::string peripheralName);
  bool isThisPeripheralConnected(SimpleBLE::Peripheral* peripheral);

public:
  void scanPeripherals();
  bool addPeripheral(std::string wantedPeripheral);
  std::vector<SimpleBLE::Peripheral> getListOfPeripherals(SimpleBLE::Adapter *adapter);
  bool connectThisPeripheral(BLEPeripheral::BLEPeripheral* peripheral);
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
