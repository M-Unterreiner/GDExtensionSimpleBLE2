#pragma once

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>

#include <simpleble/Service.h>
#include <simpleble/Characteristic.h>
#include <simpleble/Types.h>


#include <utility>

using namespace godot;

class BLEService : public Node{
        GDCLASS(BLEService, Node);

private:
    std::shared_ptr<SimpleBLE::Characteristic> characteristic_;
    std::shared_ptr<SimpleBLE::Service> service_;
    Array uuids_ = Array();
    void setUUIDs();
protected:
  static void _bind_methods();

public:
    Array getUUIDsInArray();
    bool can_notify();
    bool can_read();

    BLEService();
    BLEService(SimpleBLE::Service& service, SimpleBLE::Characteristic& characteristic);
    ~BLEService();
};
