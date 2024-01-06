#pragma once

// #include <godot_cpp/core/class_db.hpp>
#include <memory>
#include <simpleble/Service.h>
#include <simpleble/Characteristic.h>
#include <simpleble/Peripheral.h>
#include <simpleble/Types.h>

#include "bleservice.h"

#include <utility>
#include <vector>
#include <string>

class BLEPeripheral{
    private:
    bool isConnected = false;
    std::unique_ptr<SimpleBLE::Peripheral> peripheral_;
    std::vector<BLEService> services;

    void setIsConnectedTo(bool connectionState);
    void callback_on_connected();
    void callback_on_disconnected();
    std::vector<SimpleBLE::Service> getServices();

    public:
    void connect();
    void connectService();
    bool is_connected();
    void disconnect();
    std::string identifier();
    SimpleBLE::ByteArray read();

    BLEPeripheral(SimpleBLE::Peripheral* newPeripheral);
    ~BLEPeripheral();
};
