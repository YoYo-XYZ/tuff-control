# Mecanum prototype

This sketch controls four DC motors through two L298N modules on an Arduino Uno R3. It uses open-loop motor effort. It does not measure speed, distance, or turning angle.

## Wiring

Wheel positions are relative to the robot facing forward. Mount the mecanum wheels with their roller axes forming an X when viewed from above.

| Wheel | Module/channel | Enable | IN1 / IN2 on that channel |
| --- | --- | --- | --- |
| Front-left | 1 A | ENA to D3 | D2 / D4 |
| Front-right | 1 B | ENB to D9 | D7 / D8 |
| Rear-left | 2 A | ENA to D10 | D12 / D13 |
| Rear-right | 2 B | ENB to D11 | A0 / A1 |

For channel B, the module normally labels the direction inputs IN3 and IN4. A0 and A1 act as digital outputs. Connect each motor to its channel's output terminals.

- Remove both modules' ENA and ENB jumpers so the Arduino can control enable/PWM.
- Connect Arduino GND, both driver grounds, and the motor supply ground together.
- Use a motor supply suitable for the motors and modules. Do not power motors from the Arduino 5V pin. Follow your module's instructions for its separate 5V regulator jumper and logic supply.
- D0 and D1 remain available for USB serial. Pin assignments and per-wheel inversion flags are in `RobotConfig.h`.

The output logic follows `../motor_code_ref.cpp`: direction pins select rotation and the enable pin sets PWM. This prototype disables enable when stopping, so the wheels coast. It does not actively brake.

## Run

1. Open `Prototype.ino` in Arduino IDE. Keep the other source files in this folder.
2. Select Arduino Uno and its serial port, then upload.
3. Open Serial Monitor at **115200 baud** with newline or both CR and LF enabled.
4. Start with the wheels raised off the ground. The robot starts stopped.

Send uppercase commands with three integer values between -255 and 255:

```text
MOVE 100 0 0
STOP
```

The arguments are forward, right, and clockwise motor effort. Negative values reverse those directions. Examples:

| Command | Motion |
| --- | --- |
| `MOVE 100 0 0` | Forward |
| `MOVE -100 0 0` | Backward |
| `MOVE 0 100 0` | Strafe right |
| `MOVE 0 0 100` | Turn clockwise |
| `MOVE 100 100 0` | Forward and right |
| `STOP` | Coast to a stop |

Each completed command returns `OK` or `ERR`. Invalid commands stop the motors. Lines longer than 63 characters stop the motors and are discarded through the next newline. An embedded NUL also invalidates the line.

Repeat movement commands faster than every **500 ms**, for example every 100 ms. Without a valid movement command for 500 ms, the robot stops. A single Serial Monitor command therefore produces only a short movement. Partial lines do not extend the timeout. `STOP` needs no arguments.

## Calibration and code

Check `MOVE 100 0 0` with the wheels raised. All four wheels should drive the chassis forward. If one wheel rotates backward, change only that wheel's `inverted` flag in `RobotConfig.h` and upload again. Increase effort if 100 is below a motor's starting threshold.

Then check strafe right and clockwise rotation. Lower the robot and repeat at low effort with space to move. If strafing is wrong after forward direction is calibrated, check wheel placement and the X roller layout.

`Prototype.ino` handles serial input and the timeout. `Drive.h/.cpp` exposes `begin()`, `move(forward, right, clockwise)`, and `stop()`, and contains the wheel mixing and driver outputs. Inputs to `move()` are clamped to -255 through 255. If a mixed wheel output exceeds 255, all four outputs scale together to preserve their proportions.

Wheel order is front-left, front-right, rear-left, rear-right. The mixing equations are:

```text
front-left  = forward + right + clockwise
front-right = forward - right - clockwise
rear-left   = forward - right + clockwise
rear-right  = forward + right - clockwise
```

Motor polarity, minimum starting effort, and mechanical differences need checking on the actual robot. Encoder motion and physical dimensions are deferred until distance and angle control are added.
