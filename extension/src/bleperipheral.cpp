#include "bleperipheral.h"
#include "bleservice.h"
#include <memory>
#include <utility>
#include <vector>
#include <string>

#include <godot_cpp/variant/utility_functions.hpp>

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
bool BLEPeripheral::is_peripheral_connected() {
    setIsConnectedTo(peripheral_->is_connected());
    return isConnected;
}

// Disconnects peripheral
void BLEPeripheral::disconnect() {
    peripheral_->disconnect();
}

// Returns the identifiere / name of the peripheral
String BLEPeripheral::identifier(){
    return peripheral_->identifier().c_str();
}

// Emit services
void BLEPeripheral::emit_services(){

}


// TODO Correct implementation
// Gets all services from SimpleBLE of the peripheral
std::vector<SimpleBLE::Service> BLEPeripheral::getServices() {
    return peripheral_->services();
}

// TODO Not implemented for several services.
// Reads the peripheral
SimpleBLE::ByteArray BLEPeripheral::read() {
// TODO Is only using the first service
    BLEService service = services.front();
    SimpleBLE::BluetoothUUID serviceUUID = service.getUUIDs().first;
    SimpleBLE::BluetoothUUID characteristicUUID = service.getUUIDs().second;

    SimpleBLE::ByteArray data = peripheral_->read(serviceUUID,characteristicUUID);
    return data;
}

void addServiceToServices(SimpleBLE::Service& service, SimpleBLE::Characteristic& characteristic ){
    BLEService newBLEService = BLEService(service, characteristic);
}


void BLEPeripheral::initServices(){
  std::vector<SimpleBLE::Service> services = getServices();
  std::vector<SimpleBLE::Characteristic> characteristics;
  for (SimpleBLE::Service& service : services) {
    characteristics = service.characteristics();
    for (SimpleBLE::Characteristic& characteristic : characteristics) {
      addServiceToServices(service, characteristic);
    }
  }
}



BLEPeripheral::BLEPeripheral(){
  initServices();
}

BLEPeripheral::BLEPeripheral(SimpleBLE::Peripheral& newPeripheral){
    peripheral_ = std::make_shared<SimpleBLE::Peripheral>(newPeripheral);
   //peripheral_ = std::shared_ptr<SimpleBLE::Peripheral>(newPeripheral);
   peripheral_->set_callback_on_connected([&](){callback_on_connected();});
   peripheral_->set_callback_on_disconnected([&](){callback_on_disconnected();});
}

// Callback function which is called when peripheral is connected
void BLEPeripheral::callback_on_connected(){

    emit_signal("peripheral_is_connected", identifier());
}

// Callback function which is called when peripheral disconnects
void BLEPeripheral::callback_on_disconnected(){
    UtilityFunctions::print("Device was disconnected");
    emit_signal("peripheral_is_disconnected", identifier());
}

void BLEPeripheral::_bind_methods() {
  ClassDB::bind_method(D_METHOD("identifier"), &BLEPeripheral::identifier);
  ClassDB::bind_method(D_METHOD("connect_peripheral"), &BLEPeripheral::connect);
  ClassDB::bind_method(D_METHOD("disconnect_peripheral"), &BLEPeripheral::disconnect);
  ClassDB::bind_method(D_METHOD("is_peripheral_connected"), &BLEPeripheral::is_peripheral_connected);
  ClassDB::bind_method(D_METHOD("emit_services"), &BLEPeripheral::emit_services);
  ADD_SIGNAL(MethodInfo("peripheral_is_connected", PropertyInfo(Variant::STRING, "identifier")));
  ADD_SIGNAL(MethodInfo("peripheral_is_disconnected", PropertyInfo(Variant::STRING, "identifier")));
  ADD_SIGNAL(MethodInfo("send_services", PropertyInfo(Variant::ARRAY, "services")));
}
