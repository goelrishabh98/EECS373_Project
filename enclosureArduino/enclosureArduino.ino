/*
 * Distance sensor: A0
 * PWM: D5
 * Comms: TX/RX
 */
#include <Servo.h>
 
#define servoPin 5
#define distanceSensorPin A0
#define distanceThreshold 20  //About 100mV
#define armExtendVal 150
#define armRetractVal 35

Servo servo;
int receivedData = 0;

void setup() {
  servo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {  
  
  if(readDistanceSensor() < distanceThreshold) {
    Serial.println("Triggered");
  }
  extendArm();
  delay(2000);
  retractArm();
  delay(2000);
  
  if(Serial.available() > 0) {
    receivedData = Serial.read();
  }
  else {
    Serial.write("Last Data:");
    Serial.write(receivedData);
    Serial.write("\r\n");
  }
}

int readDistanceSensor() {
  return analogRead(distanceSensorPin);
}

void extendArm() {
  servo.write(armExtendVal);
}

void retractArm() {
  servo.write(armRetractVal);
}

