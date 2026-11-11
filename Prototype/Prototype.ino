#include "Drive.h"
#include "RobotConfig.h"
#include <stdlib.h>
#include <string.h>

namespace {
char line[64];
uint8_t lineLength = 0;
bool discardingLine = false;
bool moving = false;
unsigned long lastMoveMs = 0;

void stopRobot() {
  Drive::stop();
  moving = false;
}

bool executeCommand(char* command) {
  const char* separators = " \t\r";
  char* token = strtok(command, separators);
  if (!token) return false;

  if (strcmp(token, "STOP") == 0) {
    if (strtok(nullptr, separators)) return false;
    stopRobot();
    return true;
  }
  if (strcmp(token, "MOVE") != 0) return false;

  int values[3];
  for (uint8_t i = 0; i < 3; ++i) {
    token = strtok(nullptr, separators);
    if (!token) return false;
    char* end;
    const long value = strtol(token, &end, 10);
    if (end == token || *end != '\0' || value < -255 || value > 255) {
      return false;
    }
    values[i] = static_cast<int>(value);
  }
  if (strtok(nullptr, separators)) return false;

  Drive::move(values[0], values[1], values[2]);
  lastMoveMs = millis();
  moving = true;
  return true;
}

void readSerial() {
  // Limit work per loop so a continuous stream cannot delay timeout checks.
  for (uint8_t count = 0; count < sizeof(line) && Serial.available(); ++count) {
    const char character = Serial.read();
    if (character == '\n') {
      line[lineLength] = '\0';
      if (!discardingLine && executeCommand(line)) {
        Serial.println(F("OK"));
      } else {
        stopRobot();
        Serial.println(F("ERR"));
      }
      lineLength = 0;
      discardingLine = false;
    } else if (!discardingLine) {
      if (lineLength < sizeof(line) - 1 && character != '\0') {
        line[lineLength++] = character;
      } else {
        stopRobot();
        discardingLine = true;
      }
    }
  }
}
}  // namespace

void setup() {
  Drive::begin();
  Serial.begin(RobotConfig::serialBaud);
}

void loop() {
  if (moving && millis() - lastMoveMs >= RobotConfig::commandTimeoutMs) {
    stopRobot();
  }
  readSerial();
}
