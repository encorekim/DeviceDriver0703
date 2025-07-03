#include "device_driver.h"
#include "gmock/gmock.h"
#include <stdexcept>

using namespace testing;

class MockFlashMemory : public FlashMemoryDevice {
 public:
  MOCK_METHOD(unsigned char, read, (long address), (override));
  MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriver, ReadFromHW) {
  MockFlashMemory hardware;
  EXPECT_CALL(hardware, read(_)).WillRepeatedly(Return(0));
  DeviceDriver driver{&hardware};
  int data = driver.read(0xFF);
  EXPECT_EQ(0, data);
}

TEST(DeviceDriver, READFAIL) {
  MockFlashMemory hardware;
  EXPECT_CALL(hardware, read(_))
      .WillOnce(Return(0))
      .WillOnce(Return(1))
      .WillRepeatedly(Return(0));
  DeviceDriver driver{&hardware};
  EXPECT_THROW(driver.read(0xFF), ReadFailException);
}

int main() {
  ::testing::InitGoogleMock();
  return RUN_ALL_TESTS();
}