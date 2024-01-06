#pragma

#include <simpleble/Service.h>
#include <simpleble/Characteristic.h>
#include <simpleble/Types.h>

#include <utility>

class BLEService {
    private:
    SimpleBLE::Characteristic* characteristic_;
    SimpleBLE::Service* service_;
    SimpleBLE::BluetoothUUID serviceUUID;
    SimpleBLE::BluetoothUUID characteristicUUID;
    std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID> uuids_;

    public:
    std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID> getUUIDs();
    bool canNotify();
    bool canRead();

    BLEService(SimpleBLE::BluetoothUUID serviceUUID, SimpleBLE::BluetoothUUID characteristicUUID);
    ~BLEService();
};
