#pragma once

// #include <godot_cpp/core/class_db.hpp>
#include <memory>
#include <simpleble/Service.h>
#include <simpleble/Characteristic.h>
#include <simpleble/Peripheral.h>
#include <simpleble/Types.h>

#include <utility>
#include <vector>
#include <string>

class BLEPeripheral{
    private:
    std::unique_ptr<SimpleBLE::Peripheral> peripheral_;
    bool isConnected = false;
    std::vector<std::pair<SimpleBLE::Service, SimpleBLE::Characteristic>> services;

    void setIsConnectedTo(bool connectionState);
    void callback_on_connected();
    void callback_on_disconnected();

    public:
    void connect();
    void connectService();
    bool is_connected();
    void disconnect();
    std::string identifier();
    std::vector<SimpleBLE::Service> getServices();
    SimpleBLE::ByteArray read();

    BLEPeripheral(SimpleBLE::Peripheral* newPeripheral);
    ~BLEPeripheral();
};
