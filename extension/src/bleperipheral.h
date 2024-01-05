#pragma once

// #include <godot_cpp/core/class_db.hpp>
#include <memory>
#include <simpleble/Service.h>
#include <simpleble/Peripheral.h>
#include <simpleble/Service.h>
#include <simpleble/Types.h>

#include <vector>

class BLEPeripheral{
    private:
    std::unique_ptr<SimpleBLE::Peripheral> peripheral_;

    public:
    void connect();
    void connectService();
    bool is_connected();
    std::vector<SimpleBLE::Service> getServices();
    SimpleBLE::ByteArray readPeripheral();

    BLEPeripheral(SimpleBLE::Peripheral* newPeripheral);
    ~BLEPeripheral();
};
