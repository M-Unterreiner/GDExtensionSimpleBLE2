#include "bleperipheral.h"
#include "bleservice.h"
#include "bleutils.h"
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
  emit_signal("services_send", services);
  UtilityFunctions::print("Emitted ", services.size(), " services");
}


// Gets all services from SimpleBLE of the peripheral
std::vector<SimpleBLE::Service> BLEPeripheral::getServices() {
    return peripheral_->services();
}

// TODO Not implemented for several services.
// Reads the peripheral
//String BLEPeripheral::read() {
//// TODO Is only using the first service
//    //BLEService service = services.front();
//    //SimpleBLE::BluetoothUUID serviceUUID = service.getUUIDs().first;
//    //SimpleBLE::BluetoothUUID characteristicUUID = service.getUUIDs().second;
//
//    //SimpleBLE::ByteArray data = peripheral_->read(serviceUUID,characteristicUUID);
//    return SimpleBLE::ByteArray().c_str();
//}

void BLEPeripheral::read(String serviceUUID , String characteristicUUID) {
// TODO Is only using the first service
    //BLEService service = services.front();
    //SimpleBLE::BluetoothUUID serviceUUID = service.getUUIDs().first;
    //SimpleBLE::BluetoothUUID characteristicUUID = service.getUUIDs().second;
    std::string service = serviceUUID.utf8().get_data();
    std::string characteristic = characteristicUUID.utf8().get_data();
    SimpleBLE::ByteArray byteData = peripheral_->read(service,characteristic);
    String data = byteData.c_str();
    emit_signal("received_data", data);
}


void BLEPeripheral::subscribe(String serviceUUID , String characteristicUUID){
    std::string service = serviceUUID.utf8().get_data();
    std::string characteristic = characteristicUUID.utf8().get_data();
    std::pair<std::string, std::string> subscribedUUIDs = std::make_pair(service, characteristic);

    peripheral_->notify(service, characteristic, [&](SimpleBLE::ByteArray bytes) {callbackOnDataReceived(bytes);});
    // subscribedServices_.push_back(subscribedUUIDs);
}


void BLEPeripheral::getNotifications(){
  if(!subscribedServices_.empty()){
    for(std::pair<std::string, std::string> uuids : subscribedServices_){
      peripheral_->notify(uuids.first, uuids.second, [&](SimpleBLE::ByteArray bytes) {callbackOnDataReceived(bytes);});
    }
  }
}

void BLEPeripheral::callbackOnDataReceived(SimpleBLE::ByteArray bytes){
    String data = bytes.c_str();
    emit_signal("received_data", data);
}


void BLEPeripheral::unsubscribe(String serviceUUID , String characteristicUUID){
    std::string service = serviceUUID.utf8().get_data();
    std::string characteristic = characteristicUUID.utf8().get_data();
    // std::pair<std::string, std::string> service = std::make_pair(service, characteristic);
    // peripheral_.push_back(service);

    // peripheral_->unsubscribe(service,characteristic);
    // emit_signal("received_data", "Unsubscribed service");
}

void BLEPeripheral::addServiceToServices(SimpleBLE::Service& service, SimpleBLE::Characteristic& characteristic ){
    BLEService* newBLEService = memnew(BLEService(service, characteristic));
    services.append(newBLEService);
}


void BLEPeripheral::initServices(){
  std::vector<SimpleBLE::Service> services = getServices();

  UtilityFunctions::print("Init services, services known:", services.size());
  std::vector<SimpleBLE::Characteristic> characteristics;
  for (SimpleBLE::Service& service : services) {
    characteristics = service.characteristics();
    for (SimpleBLE::Characteristic& characteristic : characteristics) {
      addServiceToServices(service, characteristic);
    }
  }
}




BLEPeripheral::BLEPeripheral(){
}

BLEPeripheral::BLEPeripheral(SimpleBLE::Peripheral& newPeripheral){
    peripheral_ = std::make_shared<SimpleBLE::Peripheral>(newPeripheral);
   //peripheral_ = std::shared_ptr<SimpleBLE::Peripheral>(newPeripheral);
   // initServices();
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
  ClassDB::bind_method(D_METHOD("init_services"), &BLEPeripheral::initServices);
  ClassDB::bind_method(D_METHOD("read", "serviceUUID", "characteristicUUID"), &BLEPeripheral::read);
  ClassDB::bind_method(D_METHOD("subscribe", "serviceUUID", "characteristicUUID"), &BLEPeripheral::subscribe);
  ClassDB::bind_method(D_METHOD("unsubscribe", "serviceUUID", "characteristicUUID"), &BLEPeripheral::unsubscribe);
  ClassDB::bind_method(D_METHOD("get_notifications"), &BLEPeripheral::getNotifications);
  ADD_SIGNAL(MethodInfo("peripheral_is_connected", PropertyInfo(Variant::STRING, "identifier")));
  ADD_SIGNAL(MethodInfo("peripheral_is_disconnected", PropertyInfo(Variant::STRING, "identifier")));
  ADD_SIGNAL(MethodInfo("services_send", PropertyInfo(Variant::ARRAY, "services")));
  ADD_SIGNAL(MethodInfo("received_data", PropertyInfo(Variant::ARRAY, "data")));
}
