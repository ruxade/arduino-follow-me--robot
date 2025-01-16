## Arduino Follow-Me Robot
### Overview
This project is part of a university course during my Master's in Architecture, where we explored digital design and interactive systems. The main goal of this project was to design and build a follow-me robot that can autonomously navigate its environment by detecting obstacles and adjusting its movement. Using Arduino and various sensors, the robot is able to sense its surroundings, process the data, and take actions such as moving forward, turning, and avoiding obstacles.

### Project Details
The follow-me robot utilizes:

Ultrasonic Sensors: To detect objects and measure distances in its environment.
Servo Motor: To change the direction of the robot by scanning the environment.
DC Motors: To control movement (forward and backward).
Arduino Board (Uno): As the main controller to manage sensor data and motor commands.

### Main Features:
Obstacle Detection & Avoidance: The robot uses an ultrasonic sensor to detect obstacles and avoid collisions.
Autonomous Movement: Based on the sensor input, the robot can move forward, backward, or turn to avoid obstacles.
Servo-Controlled Vision: The servo motor allows the robot to scan its environment to the left and right to determine the best path.
Speed Control: The speed of the motors is gradually increased to avoid sudden changes that could destabilize the robot.

### Motivation
The project was developed for a course that examined digital design techniques and interactive technologies. The goal was to merge architectural thinking with engineering principles by creating a physical model that responds to its environment, mimicking basic autonomous navigation systems used in architectural spaces and smart environments.
