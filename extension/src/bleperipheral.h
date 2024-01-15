#pragma once

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/node.hpp>
#include <memory>

#include <simpleble/Service.h>
#include <simpleble/Characteristic.h>
#include <simpleble/Peripheral.h>
#include <simpleble/Types.h>

#include "bleservice.h"

#include <utility>
#include <vector>
#include <string>

using namespace godot;

class BLEPeripheral : public Node{
    GDCLASS(BLEPeripheral, Node);

private:
    bool isConnected = false;
    std::shared_ptr<SimpleBLE::Peripheral> peripheral_;
    Array services;

    void setIsConnectedTo(bool connectionState);
    void callback_on_connected();
    void callback_on_disconnected();
    void initServices();
    void addServiceToServices(SimpleBLE::Service& service, SimpleBLE::Characteristic& characteristic);
    std::vector<SimpleBLE::Service> getServices();

protected:
  static void _bind_methods();

public:
    void connect();
    void connectService();
    bool is_peripheral_connected();
    void disconnect();
    String identifier();
    void emit_services();
    SimpleBLE::ByteArray read();

    BLEPeripheral();
    BLEPeripheral(SimpleBLE::Peripheral& newPeripheral);
    ~BLEPeripheral();
};
