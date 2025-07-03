#include "device_driver.h"

#include <stdexcept>
#include <string>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware)
    : m_hardware(hardware) {}

int DeviceDriver::read(long address) {
  int result = (int)(m_hardware->read(address));
  for (int i = 0; i < 4; i++) {
    if (result != (int)(m_hardware->read(address))) {
      throw(ReadFailException("Read Failed"));
    }
  }
  return result;
}

void DeviceDriver::write(long address, int data) {
  // TODO: implement this method
  m_hardware->write(address, (unsigned char)data);
}