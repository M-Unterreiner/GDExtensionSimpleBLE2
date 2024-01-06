#include "bleservice.h"

BLEService::BLEService(SimpleBLE::BluetoothUUID serviceUUID, SimpleBLE::BluetoothUUID characteristicUUID) {
    uuids_ = std::make_pair(serviceUUID, characteristicUUID);
}

BLEService::~BLEService() {
    // Clean up your service and characteristic here
}

std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID> BLEService::getUUIDs() {
    return uuids_;
}

bool BLEService::canNotify() {
    return characteristic_->can_notify();
}

bool BLEService::canRead() {
    return characteristic_->can_read();
}
