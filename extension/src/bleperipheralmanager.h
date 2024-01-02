#ifndef BLEPERIPHERALMANAGER_H
#define BLEPERIPHERALMANAGER_H

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
  std::vector<SimpleBLE::Peripheral> addedPeripherals_;
  std::vector<std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID>>
      uuidPeripheral1;
  SimpleBLE::Peripheral scanForThisPeripheral(std::string wantedPeripheral);
  bool isThisPeripheralConnected(SimpleBLE::Peripheral& peripheral);

public:
  void scanPeripherals();
  bool addPeripheral(std::string wantedPeripheral);
  std::vector<SimpleBLE::Peripheral> getListOfPeripherals(SimpleBLE::Adapter *adapter);
  bool connectThisPeripheral(SimpleBLE::Peripheral& peripheral);
  bool isThisDeviceConnected(SimpleBLE::Peripheral& peripheral);
  Array* getAdapterList();
  bool connectAddedPeripherals();
  bool connectService();
  SimpleBLE::ByteArray readThisPeripheral(SimpleBLE::Peripheral &peripheral);
  bool isReadDataEmpty(SimpleBLE::ByteArray rx_data);

  std::vector<std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID>>
  getServicesOfPeripheral(SimpleBLE::Peripheral& peripheral);

  BLEPeripheralManager();
  ~BLEPeripheralManager();
};
#endif // BLEPERIPHERALMANAGER_H
