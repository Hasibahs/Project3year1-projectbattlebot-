#include <analogWrite.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_VL53L0X.h>

// Screen Size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

// Reset Pin
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#define MH_SENSOR_RIGHT 39
#define MH_SENSOR_LEFT 34
#define MOTOR_SPEED 180

//Right motor
int enableRightMotor=6;
int rightMotorPinF=18;
int rightMotorPinB=5;

//Left motor
int enableLeftMotor=6;
int leftMotorPinF=16;
int leftMotorPinB=17;

void setup()
{
  //Set up Serial Monitor
  Serial.begin(9600);

  //Put Setup code here to run once
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPinF, OUTPUT);
  pinMode(rightMotorPinB, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPinF, OUTPUT);
  pinMode(leftMotorPinB, OUTPUT);

  pinMode(MH_SENSOR_RIGHT, INPUT);
  pinMode(MH_SENSOR_LEFT, INPUT);
  rotateMotor(0,0);
}

void loop()
{
  int rightMHSensorValue = digitalRead(MH_SENSOR_RIGHT);
  int leftMHSensorValue = digitalRead(MH_SENSOR_LEFT);

  //If no black line detected then go straight
  if (rightMHSensorValue == 0 && leftMHSensorValue == 0)
  {
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
  }
  //if right snesore detects black line, then turn right
  else if (rightMHSensorValue == 1 && leftMHSensorValue == 0)
  {
    rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
  }
  //if left snesore detects a black line, then turn left
  else if (rightMHSensorValue == 0 && leftMHSensorValue == 1)
  {
    rotateMotor(MOTOR_SPEED, -MOTOR_SPEED);
  }
  //if both the sensor detect black line, then stop
  else
  {
    rotateMotor(0,0);
  }
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{

  if (rightMotorSpeed < 0)
  {
    analogWrite(rightMotorPinF, 0);
    analogWrite(rightMotorPinB, 50);
  }
  else if (rightMotorSpeed > 0)
  {
    analogWrite(rightMotorPinF, 50);
    analogWrite(rightMotorPinB, 0);
  }
  else
  {
    analogWrite(rightMotorPinF, 0);
    analogWrite(rightMotorPinB, 0);
  }

  if (leftMotorSpeed < 0)
  {
    analogWrite(leftMotorPinF, 0);
    analogWrite(leftMotorPinB, 50);
  }
  else if (leftMotorSpeed > 0)
  {
    analogWrite(leftMotorPinF, 50);
    analogWrite(leftMotorPinB, 0);
  }
  else
  {
    analogWrite(leftMotorPinF, 0);
    analogWrite(leftMotorPinB, 0);
  }
}
