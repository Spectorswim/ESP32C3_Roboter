// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
// ================================================ File MicroServo.h ============================================== //
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
#ifndef MICROSERVO_H
#define MICROSERVO_H

#include <ESP32Servo.h>

class MicroServo
{
  private:
    const int SLOW_TURN_RATE_PER_CAL = 1;

    // standart positions in degree

    const int POSITION_A = 15;
    const int POSITION_B = 0;

    Servo m_servo;
    uint8_t& m_positionNumber;
    
    int slowTurnTo(int desiredPosition);

  public:
    int m_position = POSITION_B;             // in degree
    MicroServo(int8_t servoPin, uint8_t& m_positionNumber);
    void checkPosition();
};

#endif // MICROSERVO_H
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //
// ============================================== END File MicroServo.h ============================================ //
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //