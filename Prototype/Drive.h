#pragma once

namespace Drive {
void begin();
// Relative motor effort, -255 to 255. Positive means forward/right/clockwise.
void move(int forward, int right, int clockwise);
// Disable the driver outputs so the wheels coast.
void stop();
}  // namespace Drive
