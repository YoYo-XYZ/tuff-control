# Project context

This project controls the robot's four mecanum wheels.

- The current hardware stack is ESP32 S3(as main) and Arduino uno r3(as prototype) -> XY160D Motor Driver Module -> 12 DC motor connected with magnum wheels

- `motor_code_ref.cpp` contains motor driver's official documentation best-practice reference code. Read it when implementing or changing control code.

# Coding guidelines

- Prioritize lean, simplicity, easy-to maintain code, easy to understand for a single person who is a beginner at robot controls
- Use clear names and straightforward control flow.
- Make surgical changes. Edit only what the task requires and avoid unrelated refactoring or formatting changes.