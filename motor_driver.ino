/*
  L298N Dual Motor Controller
  Automatic Speed and Direction Changes

  Motor A: ENA, IN1, IN2
  Motor B: ENB, IN3, IN4
*/

// Motor A
const int ENA = 9;
const int IN1 = 7;
const int IN2 = 8;

// Motor B
const int ENB = 10;
const int IN3 = 4;
const int IN4 = 5;

// PWM settings
const int maxSpeed = 255;
const int speedStep = 5;
const int rampDelay = 100;

// Set motor directions
// 1 = Forward, -1 = Reverse, 0 = Stop
void setDirection(int motorA, int motorB) {

  // Disable motor outputs before
  // changing direction
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, motorA == 1 ? HIGH : LOW);
  digitalWrite(IN2, motorA == -1 ? HIGH : LOW);

  digitalWrite(IN3, motorB == 1 ? HIGH : LOW);
  digitalWrite(IN4, motorB == -1 ? HIGH : LOW);
}

// Set PWM speed
void setSpeed(int speedA, int speedB) {
  analogWrite(ENA, constrain(speedA, 0, 255));
  analogWrite(ENB, constrain(speedB, 0, 255));
}

// Stop motors
void stopMotors() {
  setSpeed(0, 0);
  setDirection(0, 0);
}

// Gradually increase speed
void accelerate() {
  for (int speed = 0; speed <= maxSpeed;
       speed += speedStep) {

    setSpeed(speed, speed);

    Serial.print("Accelerating PWM: ");
    Serial.println(speed);

    delay(rampDelay);
  }
}

// Gradually decrease speed
void decelerate() {
  for (int speed = maxSpeed; speed >= 0;
       speed -= speedStep) {

    setSpeed(speed, speed);

    Serial.print("Decelerating PWM: ");
    Serial.println(speed);

    delay(rampDelay);
  }

  setSpeed(0, 0);
}

void setup() {

  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();

  Serial.println("L298N Motor Test Started");
}

void loop() {

  // FORWARD
  Serial.println("Moving Forward");

  setDirection(1, 1);
  accelerate();

  delay(2000);

  decelerate();
  stopMotors();

  delay(1000);

  // REVERSE
  Serial.println("Moving Backward");

  setDirection(-1, -1);
  accelerate();

  delay(2000);

  decelerate();
  stopMotors();

  delay(1000);

  // TURN LEFT
  Serial.println("Turning Left");

  setDirection(-1, 1);
  setSpeed(180, 180);

  delay(2000);

  stopMotors();
  delay(1000);

  // TURN RIGHT
  Serial.println("Turning Right");

  setDirection(1, -1);
  setSpeed(180, 180);

  delay(2000);

  stopMotors();
  delay(1000);

  Serial.println("Cycle Complete");
  Serial.println("-----------------");
}
