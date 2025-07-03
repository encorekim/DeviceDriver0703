#include <stdexcept>

#include "device_driver.h"
#include "gmock/gmock.h"

using namespace testing;

class MockFlashMemory : public FlashMemoryDevice {
 public:
  MOCK_METHOD(unsigned char, read, (long address), (override));
  MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class DeviceDriverFixture : public Test {
 public:
  MockFlashMemory HARDWARE;

 private:
};

TEST_F(DeviceDriverFixture, ReadFromHW) {
  EXPECT_CALL(HARDWARE, read(_)).Times(5).WillRepeatedly(Return(0));
  DeviceDriver driver{&HARDWARE};
  int data = driver.read(0xFF);
  EXPECT_EQ(0, data);
}

TEST_F(DeviceDriverFixture, ReadFailed) {
  EXPECT_CALL(HARDWARE, read(_))
      .WillOnce(Return(0))
      .WillOnce(Return(1))
      .WillRepeatedly(Return(0));
  DeviceDriver driver{&HARDWARE};
  EXPECT_THROW(driver.read(0xFF), ReadFailException);
}

TEST_F(DeviceDriverFixture, WriteToHW) {
  EXPECT_CALL(HARDWARE, read(_)).Times(5).WillRepeatedly(Return(0xFF));
  EXPECT_CALL(HARDWARE, write(_, _)).Times(1);
  DeviceDriver driver{&HARDWARE};
  driver.write(0xFF, 0);
}

TEST_F(DeviceDriverFixture, ReadErrorWhileWriting) {
  EXPECT_CALL(HARDWARE, read(_)).Times(5).WillRepeatedly(Return(0));
  DeviceDriver driver{&HARDWARE};
  EXPECT_THROW(driver.write(0xFF, 0), WriteFailException);
}

TEST_F(DeviceDriverFixture, WriteRejeced) {
  EXPECT_CALL(HARDWARE, read(_))
      .WillOnce(Return(0xFF))
      .WillOnce(Return(1))
      .WillRepeatedly(Return(0xFF));
  DeviceDriver driver{&HARDWARE};
  EXPECT_THROW(driver.write(0xFF, 0), ReadFailException);
}

int main() {
  ::testing::InitGoogleMock();
  return RUN_ALL_TESTS();
}