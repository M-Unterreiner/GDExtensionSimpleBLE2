#include "bleadapter.h"
#include <algorithm>

#include "gdextensionlogger.h"
#include <simpleble/SimpleBLE.h>

  BLEAdapter::BLEAdapter() {
    GDExtensionlogger::log("Adapter instantiated");
    setAdapter();
    setCallbacks();
}

BLEAdapter::~BLEAdapter() {}

// Converts SimpleBLE::Adapter to Godot::Array with following structure
// [[String identifier, String Address, SimpleBLE::Adapter adapter]]
Array *BLEAdapter::convertAdapterToArray(SimpleBLE::Adapter adapter) {
  std::string identifier = adapter.identifier();
  std::string address = adapter.address();

  Array *newAdapter = memnew(Array);

  newAdapter->push_front(identifier.c_str());
  newAdapter->push_back(address.c_str());

  return newAdapter;
}

// Converts a vector of SimpleBLE::Adapter to Godot::Array
Array *BLEAdapter::convertVectorOfAdaptersToArray(
    std::vector<SimpleBLE::Adapter> adapters) {
  Array *adapterList = memnew(Array);

  for (SimpleBLE::Adapter adapter : adapters) {
    Array *convertedAdapter = convertAdapterToArray(adapter);
    adapterList->push_back(convertedAdapter);
  }

  return adapterList;
}

// SimpleBLE stores adapters in a vector. This function gets from SimpleBLE
// the adapters and returns them in a Godot::Array
// Returns an Array with following structure
// [[identifier, address],[identifier, address]]
Array *BLEAdapter::getAdapterList() {
  adapters = SimpleBLE::Adapter::get_adapters();

  if (!adapters.empty()) {
    return convertVectorOfAdaptersToArray(adapters);
  }

  Array *emptyArray = memnew(Array);
  return emptyArray;
}

// Set actual adapter.
bool BLEAdapter::setAdapter() {
  adapters = SimpleBLE::Adapter::get_adapters();

  GDExtensionlogger::log("SetAdapter: ");
  if (!adapters.empty()) {
    actualAdapter = adapters[0];

    GDExtensionlogger::log(adapters[0].identifier().c_str());
    return true;
  } else {
    GDExtensionlogger::log("No adapter found!");
  }
  return false;
}

// Scans for peripherals in miniseconds
void BLEAdapter::scanPeripherals(int ms) { actualAdapter.scan_for(ms); }

// Retrieve the scanned peripherals within a vector.
std::vector<SimpleBLE::Peripheral> BLEAdapter::getScanResults() {
  return actualAdapter.scan_get_results();
}

// Retrieve the paired peripherals within a vector
std::vector<SimpleBLE::Peripheral> BLEAdapter::getPairedPeripherals() {
  GDExtensionlogger::log("GetPairedPeripherals");
  return actualAdapter.get_paired_peripherals();
};

void BLEAdapter::callbackOnStartedScan(){
  GDExtensionlogger::log("Scan started.");
}

void BLEAdapter::callbackOnScanFound(SimpleBLE::Peripheral peripheral){
  GDExtensionlogger::log("Peripheral found");
}


void BLEAdapter::callbackOnStoppedScan(){
  GDExtensionlogger::log("Scan stopped.");
}

// Set callbacks when scan started, scan stopped and on scan found.
void BLEAdapter::setCallbacks() {
  GDExtensionlogger::log("Set callbacks.");
  actualAdapter.set_callback_on_scan_start(
      [&]() { callbackOnStartedScan(); });

  actualAdapter.set_callback_on_scan_stop(
      [&]() { callbackOnStoppedScan(); });

  actualAdapter.set_callback_on_scan_found(
      [&](SimpleBLE::Peripheral peripheral) {
       callbackOnScanFound(peripheral);
      });
};


void BLEAdapter::_bind_methods() {
  ADD_SIGNAL(
      MethodInfo("updateAdapters", PropertyInfo(Variant::STRING, "Updated Adapters")));
}
