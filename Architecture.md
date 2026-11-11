This project use this flat codebase architecture to prioritize simplicity and maintainability:

tuff-control/
├── tuff-control.ino
├── RobotConfig.h
├── Drive.h
├── Drive.cpp
└── README.md

tuff-control.ino: Arduino setup() and loop(). It decides what the robot should do and calls the drive code.
RobotConfig.h: motor pins, wheel dimensions, and other settings that you may need to tune.
Drive.h/.cpp: controls the four motors and converts forward, sideways, and turning commands into wheel commands. Keep the L298N details and wheel-mixing math here.
README.md: pin wiring, wheel order, calibration notes, and how to run the project.

The encoder-based distance moves and angle-based turns module will be added after the project starts be stable
├── Motion.h
└── Motion.cpp