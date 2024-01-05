#include "bleperipheral.h"
#include <memory>
#include <vector>


// Connect service
void BLEPeripheral::connectService() {
    // Implementation goes here
}

// Returns if peripheral is connected.
bool BLEPeripheral::is_connected() {
    return true;
}

// Gets all services of the peripheral
std::vector<SimpleBLE::Service> BLEPeripheral::getServices() {
    return std::vector<SimpleBLE::Service>();
}

// Reads the peripheral
SimpleBLE::ByteArray BLEPeripheral::readPeripheral() {
    return SimpleBLE::ByteArray();
}

BLEPeripheral::BLEPeripheral(SimpleBLE::Peripheral* newPeripheral){
   peripheral_ = std::unique_ptr<SimpleBLE::Peripheral>(newPeripheral);
}
