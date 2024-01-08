#ifndef BLEADAPTER_H
#define BLEADAPTER_H

#pragma once

#include <godot_cpp/core/class_db.hpp>
#include <simpleble/Adapter.h>

#include <string>
#include <vector>

using namespace godot;

class BLEAdapter {

private:
  SimpleBLE::Adapter actualAdapter;
  std::vector<SimpleBLE::Adapter> adapters;

  Array *convertAdapterToArray(SimpleBLE::Adapter adapter);
  Array *convertVectorOfAdaptersToArray(std::vector<SimpleBLE::Adapter> adapters);
  bool setAdapter();
  void setCallbacks();
  void callbackOnStartedScan();
  void callbackOnScanFound(SimpleBLE::Peripheral peripheral);
  void callbackOnStoppedScan();

public:
  BLEAdapter();
  ~BLEAdapter();

  Array* getAdapterList();
  void scanPeripherals(int ms = 5000);
  std::vector<SimpleBLE::Peripheral> getScanResults();
  std::vector<SimpleBLE::Peripheral> getPairedPeripherals();
};
#endif // BLEADAPTER_CLASS_H
