#include "device_driver.h"

#include <stdexcept>
#include <string>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware)
    : m_hardware(hardware) {}

int DeviceDriver::read(long address) {
  int result = (int)(m_hardware->read(address));
  verifyRead(result, address);
  return result;
}

void DeviceDriver::write(long address, int data) {
  checkAddressEmpty(address);
  m_hardware->write(address, (unsigned char)data);
}

void DeviceDriver::checkAddressEmpty(long address) {
  if (read(address) != 0xFF) {
    throw(WriteFailException("Write Failed"));
  }
}

void DeviceDriver::verifyRead(int result, long address) {
  for (int i = 0; i < 4; i++) {
    if (result != (int)(m_hardware->read(address))) {
      throw(ReadFailException("Read Failed"));
    }
  }
}