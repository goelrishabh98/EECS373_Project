/*
 * Distance sensor: A0
 * PWM: D5
 * Comms: TX/RX
 */
#define servoPin 5
#define distanceSensorPin A0
#define armExtendVal 255
#define armRetractVal 128

void setup() {
  pinMode(servoPin, OUTPUT);
}

void loop() {

}

int readDistanceSensor() {
  return analogRead(distanceSensorPin);
}

void extendArm() {
  analogWrite(servoPin, armExtendVal);
}

void retractArm() {
  analogWrite(serviPin, armRetractVal);
}

