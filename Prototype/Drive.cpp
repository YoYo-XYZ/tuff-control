#include "Drive.h"
#include "RobotConfig.h"

namespace {
void writeMotor(const RobotConfig::MotorPins& pins, int speed) {
  if (pins.inverted) speed = -speed;

  // Disable the channel before changing its direction.
  analogWrite(pins.enable, 0);
  digitalWrite(pins.in1, speed > 0 ? HIGH : LOW);
  digitalWrite(pins.in2, speed < 0 ? HIGH : LOW);
  analogWrite(pins.enable, abs(speed));
}

int limitInput(int value) {
  if (value > 255) return 255;
  if (value < -255) return -255;
  return value;
}
}  // namespace

void Drive::begin() {
  for (const auto& pins : RobotConfig::motors) {
    digitalWrite(pins.enable, LOW);
    pinMode(pins.enable, OUTPUT);
    digitalWrite(pins.in1, LOW);
    digitalWrite(pins.in2, LOW);
    pinMode(pins.in1, OUTPUT);
    pinMode(pins.in2, OUTPUT);
  }
  stop();
}

void Drive::move(int forward, int right, int clockwise) {
  forward = limitInput(forward);
  right = limitInput(right);
  clockwise = limitInput(clockwise);

  // X roller layout, viewed from above.
  int wheels[] = {
      forward + right + clockwise,
      forward - right - clockwise,
      forward - right + clockwise,
      forward + right - clockwise,
  };

  int largest = 255;
  for (int speed : wheels) {
    if (abs(speed) > largest) largest = abs(speed);
  }
  for (uint8_t i = 0; i < 4; ++i) {
    // Use long arithmetic to avoid overflowing the Uno's 16-bit int.
    const int speed = static_cast<long>(wheels[i]) * 255 / largest;
    writeMotor(RobotConfig::motors[i], speed);
  }
}

void Drive::stop() {
  for (const auto& pins : RobotConfig::motors) {
    writeMotor(pins, 0);
  }
}
