#pragma once
#include "flash_memory_device.h"
#include <string>

class ReadFailException : public std::exception {
 public:
  explicit ReadFailException(const std::string& message) : message{message} {}
  const char* what() const noexcept override { return message.c_str(); }

 private:
  std::string message;
};

class DeviceDriver {
 public:
  DeviceDriver(FlashMemoryDevice* hardware);
  int read(long address);
  void write(long address, int data);

 protected:
  FlashMemoryDevice* m_hardware;
  void verifyResult(int result, long address);
};