/*
 * Distance sensor: A0
 * PWM: D5
 * Comms: TX/RX
 */
#include <Servo.h>
 
#define servoPin 5
#define distanceSensorPin A0
#define distanceThreshold 20  //About 100mV
#define armExtendVal 160
#define armRetractVal 180
#define receiveSize 8
int receiveCounter = 0;
int tempReceive;

Servo servo;
char receivedData[receiveSize];
String servoExtend = String("servoExt");
String servoRetract = String("servoRet");

void setup() {
  servo.attach(servoPin);
  Serial.begin(57600);
}

void loop() { 
  //Serial.write("Board");
  //delay(2000); 
  /*
  if(readDistanceSensor() < distanceThreshold) {
    Serial.println("Triggered");
  }
  extendArm();
  delay(2000);
  retractArm();
  delay(2000);
  */
  
  while(Serial.available() > 0) {
    
    for(int i = 0; i < 8; ++i) {
      tempReceive = Serial.read();
      Serial.println(tempReceive);
      delay(10); 
    }
    
    tempReceive = Serial.read();
    delay(10);
    Serial.print("Ninth ");
    Serial.println(tempReceive);
    if(tempReceive == 'r') {
      retractArm();
    }
    else if(tempReceive == 'e') {
      extendArm();
    }
    while(Serial.available() > 0) {
      tempReceive = Serial.read();
      delay(10);
    }
  }
       
    
    /*
    receivedData[receiveCounter] = Serial.read();
    receiveCounter++;
    if(receiveCounter >= receiveSize) {
      receiveCounter = 0;
    }
    */
  /*
  receiveCounter = 0;
  if(compareReceived(servoRetract)) {
    retractArm();
  }
  else if(compareReceived(servoExtend)) {
    extendArm();
  }
  */
  /*
  else {
    Serial.write("Last Data:");
    Serial.write(receivedData);
    Serial.write("\r\n");
  }
  */
}

bool compareReceived(String cmp) {
  for(int i = 0; i < cmp.length(); ++i) {
    if(cmp.charAt(i) != receivedData[i]) {
      return false;
    }
  }
  return true;
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

