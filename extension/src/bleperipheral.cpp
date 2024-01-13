#include "bleperipheral.h"
#include <memory>
#include <utility>
#include <vector>
#include <string>


BLEPeripheral::~BLEPeripheral(){

}

// Connect service
void BLEPeripheral::connectService() {
    // Implementation goes here
}

// Connect peripheral
void BLEPeripheral::connect() {
    peripheral_->connect();
}

// This method is implemented avoid unkown connections states to avoid throwing
// exceptions by SimpleBLE
void BLEPeripheral::setIsConnectedTo(bool connectionState){
    isConnected = connectionState;
}


// Returns if peripheral is connected.
bool BLEPeripheral::is_connected() {
    setIsConnectedTo(peripheral_->is_connected());
    return isConnected;
}

// Disconnects peripheral
void BLEPeripheral::disconnect() {
    peripheral_->disconnect();
}

// Returns the identifiere / name of the peripheral
std::string BLEPeripheral::identifier(){
    if(is_connected()){
        return peripheral_->identifier();
    }
    return std::string{"Not Connected"};
}

// TODO Correct implementation
// Gets all services from SimpleBLE of the peripheral
std::vector<SimpleBLE::Service> BLEPeripheral::getServices() {
    if(is_connected()){
        return std::vector<SimpleBLE::Service>();
    }
    return std::vector<SimpleBLE::Service>();
}

// TODO Not implemented for several services.
// Reads the peripheral
SimpleBLE::ByteArray BLEPeripheral::read() {
    if (is_connected()){
        // TODO Is only using the first service
        BLEService service = services.front();
        SimpleBLE::BluetoothUUID serviceUUID = service.getUUIDs().first;
        SimpleBLE::BluetoothUUID characteristicUUID = service.getUUIDs().second;

        SimpleBLE::ByteArray data = peripheral_->read(serviceUUID,characteristicUUID);
        return data;
    }
    return SimpleBLE::ByteArray();
}

BLEPeripheral::BLEPeripheral(){
}

BLEPeripheral::BLEPeripheral(SimpleBLE::Peripheral& newPeripheral){
   peripheral_ = std::unique_ptr<SimpleBLE::Peripheral>(&newPeripheral);
   peripheral_->set_callback_on_connected([&](){callback_on_connected();});
   peripheral_->set_callback_on_disconnected([&](){callback_on_disconnected();});
}

// Callback function which is called when peripheral is connected
void BLEPeripheral::callback_on_connected(){
   setIsConnectedTo(true);
}

// Callback function which is called when peripheral disconnects
void BLEPeripheral::callback_on_disconnected(){
   setIsConnectedTo(false);
}

void BLEPeripheral::_bind_methods() {
  //ClassDB::bind_method(D_METHOD("init"), &BLEManager::init);
  //ADD_SIGNAL(
  //    MethodInfo("updateAdapters", PropertyInfo(Variant::STRING, "Updated Adapters")));
  //    MethodInfo("BLEManager_log", PropertyInfo(Variant::STRING, "message")));
}
