#pragma once

#include <simpleble/Service.h>
#include <simpleble/Characteristic.h>
#include <simpleble/Peripheral.h>
#include <simpleble/Types.h>

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "bleservice.h"

#include <memory>
#include <utility>
#include <vector>
#include <string>

using namespace godot;

class BLEPeripheral : public RefCounted {
    GDCLASS(BLEPeripheral, RefCounted);

private:
    bool isConnected = false;
    std::unique_ptr<SimpleBLE::Peripheral> peripheral_;
    std::vector<BLEService> services;

    void setIsConnectedTo(bool connectionState);
    void callback_on_connected();
    void callback_on_disconnected();
    std::vector<SimpleBLE::Service> getServices();


protected:
    static void _bind_methods();

public:
    void connect();
    void connectService();
    bool is_connected();
    void disconnect();
    std::string identifier();
    SimpleBLE::ByteArray read();

    BLEPeripheral();
    BLEPeripheral(SimpleBLE::Peripheral *newPeripheral);
    ~BLEPeripheral();
};
