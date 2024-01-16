#include "blemanager.h"
#include "bleadapter.h"
#include "gdextensionlogger.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <memory>


BLEManager::BLEManager(){
}

BLEManager::~BLEManager(){
}

void BLEManager::log_message(String logMessage){
  emit_signal("BLEManager_log", "BLEManager initialized");
}

BLEAdapter* BLEManager::init(){
  //log_message("BLEManager initialized");
  BLEAdapter* newAdapter = memnew(BLEAdapter);
  UtilityFunctions::print(newAdapter);
  return newAdapter;

}

void BLEManager::_bind_methods() {
  ClassDB::bind_method(D_METHOD("init"), &BLEManager::init);
  ADD_SIGNAL(
  //    MethodInfo("updateAdapters", PropertyInfo(Variant::STRING, "Updated Adapters")));
      MethodInfo("BLEManager_log", PropertyInfo(Variant::STRING, "message")));
}
