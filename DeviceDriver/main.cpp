#include "device_driver.h"
#include "gmock/gmock.h"

using namespace testing;

class MockFlashMemory : public FlashMemoryDevice {
 public:
  MOCK_METHOD(unsigned char, read, (long address), (override));
  MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriver, ReadFromHW) {
  // TODO : replace hardware with a Test Double
  MockFlashMemory hardware;
  EXPECT_CALL(hardware, read(_)).WillRepeatedly(Return(0));
  DeviceDriver driver{&hardware};
  int data = driver.read(0xFF);
  EXPECT_EQ(0, data);
}

TEST(DeviceDriver, READFAIL) { FlashMemoryDevice* brokenHardware = nullptr;
  DeviceDriver driver{brokenHardware};
  
}

int main() {
  ::testing::InitGoogleMock();
  return RUN_ALL_TESTS();
}