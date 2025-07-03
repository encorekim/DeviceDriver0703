#pragma once
#include <string>

#include "flash_memory_device.h"

class ReadFailException : public std::exception {
 public:
  explicit ReadFailException(const std::string& message) : message{message} {}
  const char* what() const noexcept override { return message.c_str(); }

 private:
  std::string message;
};

class WriteFailException : public std::exception {
 public:
  explicit WriteFailException(const std::string& message) : message{message} {}
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
  void verifyRead(int result, long address);
  void checkAddressEmpty(long address);
};