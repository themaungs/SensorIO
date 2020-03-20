#ifndef MovePlatform_h
#define MovePlatform_h
#include "Servo.h"

enum DeviceType {WHEEL, TRACK, MECANUM};
enum DeviceDirection {STOP, FORWARD, BACKWARDS, TURN_LEFT, TURN_RIGHT, UP, DOWN};
class MovePlatform{
  public:
    MovePlatform(String platformName, DeviceType dType);
    String GetPlatformName();
    void SetServoLimiter(float value);
    void InverseLeftRightServo(bool value);
    void InverseForwardBackward(bool value);
    void SetWheelDeviceGPIO(int leftrightPin, int forwardbackwardPin );
    void SetTrackDeviceGPIO();
    void SetMecanumDeviceGPIO();
    void MoveDevice(DeviceDirection dir, float value);
  private:
    Servo leftrightServo;
    Servo fwdServo;
    String PlatformName;
    DeviceType Device_Type;
    float servoLimiter = 0.00;
    bool isLeftRightInversed = false;
    bool isForwardBackwardInversed = false;
    float currentFwdBackValue=0.00;
    void WheelTurnDevice(float value);
    void WheelTurnLeft(float value);
    void WheelTurnRight(float value);
    void WheelStop();  
    void WheelForward(float value);
    void WheelBackward(float value);
    void WheelMove(float value);
};
#endif
