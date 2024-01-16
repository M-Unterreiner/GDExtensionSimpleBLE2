#include "gmock/gmock.h"
#include "../src/bleperipheral.h"

class MockPeripheral : public BLEPeripheral {
public:
    MOCK_METHOD(void, connectService, ());
    MOCK_METHOD(bool, isPeripheralConnected, ());
    MOCK_METHOD(std::vector<SimpleBLE::Service>, getServices, ());
    MOCK_METHOD(SimpleBLE::ByteArray, readPeripheral, ());
};

TEST(BLEPeripheralTest, TestConnectService) {
    MockPeripheral mockPeripheral;
    EXPECT_CALL(mockPeripheral, connectService()).Times(1);
    mockPeripheral.connectService();
}

TEST(BLEPeripheralTest, TestIsPeripheralConnected) {
    MockPeripheral mockPeripheral;
    EXPECT_CALL(mockPeripheral, isPeripheralConnected()).Times(1);
    mockPeripheral.isPeripheralConnected();
}

TEST(BLEPeripheralTest, TestGetServices) {
    MockPeripheral mockPeripheral;
    EXPECT_CALL(mockPeripheral, getServices()).Times(1);
    mockPeripheral.getServices();
}

TEST(BLEPeripheralTest, TestReadPeripheral) {
    MockPeripheral mockPeripheral;
    EXPECT_CALL(mockPeripheral, readPeripheral()).Times(1);
    mockPeripheral.readPeripheral();
}
