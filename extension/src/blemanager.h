#pragma once

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>
#include <memory>
#include <simpleble/SimpleBLE.h>
#include <simpleble/Utils.h>


#include "bleadapter.h"

using namespace godot;


class BLEManager : public Node{
    GDCLASS(BLEManager, Node);

protected:
  static void _bind_methods();

private:
  void log_message(String logMessage);
  std::unique_ptr<BLEAdapter> bleadapter_;

public:
  Variant init();
  BLEManager();
  ~BLEManager();
};
