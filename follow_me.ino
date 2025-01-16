#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

// Constants and Configurations
#define TRIG_PIN A4             // Ultrasonic sensor trigger pin
#define ECHO_PIN A5             // Ultrasonic sensor echo pin
#define MAX_DISTANCE 1000       // Maximum measurable distance in cm
#define MAX_SPEED 210           // Maximum motor speed (82% of full speed)
#define MAX_SPEED_OFFSET 20     // Speed offset for motor balancing
#define SERVO_CENTER 115        // Servo position for straight
#define SERVO_RIGHT 50          // Servo position for right turn
#define SERVO_LEFT 170          // Servo position for left turn
#define CLOSE_DISTANCE 30       // Threshold for very close objects
#define MID_DISTANCE 60         // Threshold for mid-range objects

// Objects and Variables
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(3, MOTOR34_1KHZ);
Servo myservo;

boolean goesForward = false;
int distance = 100;

// Function Declarations
void moveForward();
void moveBackward();
void moveStop();
void turnRight();
void turnLeft();
int readPing();
int lookDirection(int angle);

// Function Definitions
void moveForward() {
    if (!goesForward) {
        goesForward = true;
        motor1.run(FORWARD);
        motor2.run(FORWARD);
        for (int speed = 0; speed <= MAX_SPEED; speed += 2) {
            motor1.setSpeed(speed);
            motor2.setSpeed(speed + MAX_SPEED_OFFSET);
            delay(100);
        }
    }
}

void moveBackward() {
    goesForward = false;
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    for (int speed = 0; speed <= MAX_SPEED; speed += 2) {
        motor1.setSpeed(speed);
        motor2.setSpeed(speed + MAX_SPEED_OFFSET);
        delay(5);
    }
}

void moveStop() {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
}

int readPing() {
    delay(70);
    int cm = sonar.ping_cm();
    return (cm == 0) ? MAX_DISTANCE : cm;  // Return max distance if no valid reading
}

int lookDirection(int angle) {
    myservo.write(angle);
    delay(500); // Allow servo to move
    int dist = readPing();
    delay(100); // Stabilization delay
    myservo.write(SERVO_CENTER); // Reset to center
    return dist;
}

void turnRight() {
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    delay(800); // Turning duration
    moveForward();
}

void turnLeft() {
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    delay(800); // Turning duration
    moveForward();
}

void setup() {
    myservo.attach(9);
    myservo.write(SERVO_CENTER); // Initialize servo to center
    delay(2000);                 // Allow initialization
    distance = readPing();       // Initialize distance reading
}

void loop() {
    delay(40); // Main loop execution delay
    if (distance >= MID_DISTANCE) {
        moveForward(); // No obstacle detected
    } else if (distance >= CLOSE_DISTANCE) {
        // Mid-range obstacle handling
        moveStop();
        delay(100);
        moveBackward();
        delay(300);
        moveStop();
        delay(200);

        int distanceR = lookDirection(SERVO_RIGHT);
        int distanceL = lookDirection(SERVO_LEFT);

        // Decide direction based on obstacle distances
        if (distanceR >= distanceL) {
            turnRight();
        } else {
            turnLeft();
        }
    } else {
        // Very close obstacle handling
        moveStop();
        delay(100);
        moveBackward();
        delay(300);
    }

    // Update distance reading
    distance = readPing();
}
