#pragma once

#include <Arduino.h>

namespace RobotConfig {
struct MotorPins {
  uint8_t enable;
  uint8_t in1;
  uint8_t in2;
  bool inverted;
};

// Wheel order: front-left, front-right, rear-left, rear-right.
// Set inverted to true if a wheel spins backward during calibration.
constexpr MotorPins motors[] = {
    {3, 2, 4, false},
    {9, 7, 8, false},
    {10, 12, 13, false},
    {11, A0, A1, false},
};

constexpr unsigned long serialBaud = 115200;
constexpr unsigned long commandTimeoutMs = 500;
}  // namespace RobotConfig
