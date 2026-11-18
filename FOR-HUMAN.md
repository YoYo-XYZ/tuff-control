How the system works

Suppose you want your robot to move sideways at 0.2 m/s.

1. **Jetson:** Sends a movement command specifying `Vx = 0`, `Vy = 0.2`, `ω = 0`.
2. **ROS 2:** Calculates the required speed of each wheel, accounting for wheel radius and robot geometry.
3. **Arduino:** Receives four target wheel speeds through USB Serial.
4. **PID controllers:** Independently adjust each motor's PWM using encoder feedback.
5. **Arduino:** Returns measured wheel velocities to the Jetson for odometry.

This design prevents uneven motor speeds from causing unnecessary drifting.
