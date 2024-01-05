#pragma once

// #include <godot_cpp/core/class_db.hpp>
#include <simpleble/ServiceBase.h>
#include <simpleble/PeripheralBase.h>
#include <simpleble/Service.h>
#include <simpleble/Types.h>

#include <vector>

class BLEPeripheral{
    private:
    SimpleBLE::Peripheral* peripheral_;

    public:
    void connectService();
    bool isPeripheralConnected();
    std::vector<SimpleBLE::Service> getServices();
    SimpleBLE::ByteArray readPeripheral();
}:
