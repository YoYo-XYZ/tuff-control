see software-chart.png

## Repo structure

mecanum_robot/
│
├── ros2_ws/
│   └── src/
│       └── mecanum_robot/
│           │
│           ├── config/
│           │   └── controllers.yaml
│           │
│           ├── description/
│           │   └── robot.urdf.xacro
│           │
│           ├── launch/
│           │   └── robot.launch.py
│           │
│           ├── include/mecanum_robot/
│           │   └── serial_hardware.hpp
│           │
│           ├── src/
│           │   └── serial_hardware.cpp
│           │
│           ├── plugin.xml
│           ├── CMakeLists.txt
│           └── package.xml
│
├── firmware/
│   ├── src/
│   │   └── main.cpp
│   ├── include/
│   │   └── config.h
│   └── platformio.ini
│
└── README.md

## Design principles
1. One ROS 2 package: Keep configuration, launch files, and hardware integration together.
2. One ESP32 firmware project: Use a single main.cpp initially.
3. Reuse libraries: Don't implement mecanum kinematics, PID, or encoder decoding from scratch.
4. Separate responsibilities: Jetson handles robot movement; ESP32 handles individual motors.
5. Keep configuration centralized: Put adjustable parameters in controllers.yaml and config.h.
6. Avoid unnecessary abstractions: Add additional modules only when the existing code becomes difficult to maintain.

## ROS 2 — Jetson
File	Purpose
controllers.yaml	Configure the mecanum controller and wheel parameters.
robot.urdf.xacro	Define the robot's four wheel joints and hardware interfaces.
robot.launch.py	Start the ROS 2 system with one command.
serial_hardware.hpp	Declare the hardware interface class.
serial_hardware.cpp	Send wheel speed commands to ESP32 and receive encoder feedback through USB Serial.
plugin.xml	Register the hardware interface with ros2_control.
CMakeLists.txt	Build and install the ROS 2 package.
package.xml	Declare ROS 2 dependencies.

The existing mecanum_drive_controller handles mecanum kinematics and odometry. You don't need to implement these algorithms yourself.

## Firmware — ESP32
File	Purpose
main.cpp	Read encoders, execute four PID controllers, control motor PWM/direction, and handle USB Serial communication and safety.
config.h	Store GPIO pins, PID parameters, encoder resolution, and motor limits.
platformio.ini	Configure the ESP32 board and external libraries.







