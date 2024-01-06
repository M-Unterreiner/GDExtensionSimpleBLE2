#include <gmock/gmock.h>
#include "BLEService.h"

class MockBLEService : public BLEService {
public:
    MOCK_METHOD(std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID>, getUUIDs, (), (override));
    MOCK_METHOD(bool, canNotify, (), (override));
    MOCK_METHOD(bool, canRead, (), (override));
};
