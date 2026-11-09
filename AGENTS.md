# Project context

This project controls the robot's four magnum wheels.

The current hardware stack is Arduino uno r3 -> 12V motor driver -> DC motor connected with magnum wheels

`motor_code_ref.cpp` contains motor driver's official documentation best-practice reference code. Read it when implementing or changing motor control code.

# Coding guidelines

- Prioritize lean, simple, maintainable code.
- Use clear names and straightforward control flow.
- Make surgical changes. Edit only what the task requires and avoid unrelated refactoring or formatting changes.