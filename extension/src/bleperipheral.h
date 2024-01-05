#pragma once

// #include <godot_cpp/core/class_db.hpp>
#include <simpleble/Service.h>
#include <simpleble/Peripheral.h>
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
};