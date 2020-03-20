#include "Arduino.h"
#include "Servo.h"
#include "MovePlatform.h"

MovePlatform::MovePlatform(String platformName, DeviceType dType){
    PlatformName = platformName;
    Device_Type = dType;
};
void MovePlatform::SetServoLimiter(float value){
    servoLimiter = value;
}
void MovePlatform::SetWheelDeviceGPIO(int leftrightPin, int forwardbackwardPin ){
    leftrightServo.attach(leftrightPin);
    fwdServo.attach(forwardbackwardPin);
}
void MovePlatform::InverseLeftRightServo(bool value){
    isLeftRightInversed = value;
}
void MovePlatform::InverseForwardBackward(bool value){
    isForwardBackwardInversed = value;
}
void MovePlatform::SetTrackDeviceGPIO(){
}
void MovePlatform::SetMecanumDeviceGPIO(){
}
String MovePlatform::GetPlatformName(){
    return PlatformName;
}
void MovePlatform:: MoveDevice(DeviceDirection dir, float value){
  if(value>100)
    value = 100;
  if (Device_Type == WHEEL)
  {
    switch (dir) {
      case STOP:
          WheelStop();
        break;
      case FORWARD:
        if(isForwardBackwardInversed)
            WheelBackward(value);
        else
            WheelForward(value);
        break;
      case BACKWARDS:
        if(isForwardBackwardInversed)
            WheelForward(value);
        else
            WheelBackward(value);
        break;
      case TURN_LEFT:
        if(isLeftRightInversed)
            WheelTurnRight(value);
        else
            WheelTurnLeft(value);
        break;
      case TURN_RIGHT:
        if(isLeftRightInversed)
            WheelTurnLeft(value);
        else
            WheelTurnRight(value);
        break;
      default:
        break;
    }
  }
  else if (Device_Type == TRACK)
  {
    Serial.println("-----TRACKED-----");
  }
  else
  {
    Serial.println("-----MECHANUM-----");
  }
}

void MovePlatform::WheelStop(){
  bool morethan90 = false;
  if(currentFwdBackValue >=90 )
    morethan90 = true;
  float diffValue =(currentFwdBackValue-90)/5;
  Serial.println(diffValue);
  Serial.println("Stopping");
  Serial.println(currentFwdBackValue);
  Serial.println("Stopping");
  for(int i = 0; i< 5; i++){
    currentFwdBackValue = currentFwdBackValue - diffValue;
    Serial.println(currentFwdBackValue);
    fwdServo.write(currentFwdBackValue);
    delay(100);
  }
  fwdServo.write(90);
}

void MovePlatform::WheelForward(float value){
  value = 90-map(value, 0,100,0,90);
    if(value<=servoLimiter)
        value = servoLimiter;
    Serial.println(value);
    WheelMove(value);
}

void MovePlatform::WheelBackward(float value){
  value = 90 + map(value, 0,100,0,90);
    if(value >= 180 - servoLimiter){
        value = 180 - servoLimiter;
    }
    Serial.println(value);
    WheelMove(value);
}

void MovePlatform::WheelMove(float value){
  currentFwdBackValue = value;
  fwdServo.write(value);
}


void MovePlatform::WheelTurnLeft(float value){
    value = 90-map(value, 0,100,0,90);
    if(value<=servoLimiter)
        value = servoLimiter;
    WheelTurnDevice(value);
}
void MovePlatform::WheelTurnRight(float value){
    value = 90 + map(value, 0,100,0,90);
    if(value >= 180 - servoLimiter){
        value = 180 - servoLimiter;
    }
    WheelTurnDevice(value);
}
void MovePlatform::WheelTurnDevice(float value){
    leftrightServo.write(value);
}