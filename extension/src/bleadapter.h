#ifndef BLEADAPTER_H
#define BLEADAPTER_H

#pragma once

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>

#include <simpleble/Adapter.h>
#include <simpleble/Peripheral.h>

#include <string>
#include <vector>

using namespace godot;

class BLEAdapter : public Node{
    GDCLASS(BLEAdapter, Node);

private:
  SimpleBLE::Adapter actualAdapter;
  std::vector<SimpleBLE::Adapter> adapters;
  std::vector<SimpleBLE::Peripheral> peripherals_;

  Array convertAdapterToArray(SimpleBLE::Adapter adapter);
  Array convertVectorOfAdaptersToArray(std::vector<SimpleBLE::Adapter> adapters);
  bool setAdapter();
  void setCallbacks();
  void callbackOnStartedScan();
  void callbackOnScanFound(SimpleBLE::Peripheral peripheral);
  void callbackOnStoppedScan();

protected:
  static void _bind_methods();

public:
  BLEAdapter();
  ~BLEAdapter();

  Array getAdapterList();
  void start_scan(int ms = 5000);
  std::vector<SimpleBLE::Peripheral> getScanResults();
  std::vector<SimpleBLE::Peripheral> getPairedPeripherals();
};
#endif // BLEADAPTER_CLASS_H
