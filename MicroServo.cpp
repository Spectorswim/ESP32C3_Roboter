// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
// =============================================== File MicroServo.cpp ============================================= //
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
#include "MicroServo.h"

MicroServo::MicroServo(int8_t servoPin, uint8_t& positionNumber)
:  m_positionNumber(positionNumber)
{
  m_servo.attach(servoPin);
  m_servo.write(15);
}

void MicroServo::checkPosition()
{
  switch(m_positionNumber)
  {
    case 0: // change to POSITION_B
    {
      m_position = slowTurnTo(POSITION_B);
      m_servo.write(m_position);
      break;
    }
    case 1: // change to POSITION_A
    {
      m_position = POSITION_A;
      m_servo.write(m_position);
      break;
    }
  }
}

int MicroServo::slowTurnTo(int desiredPosition)
{
  int distance = desiredPosition - m_position;

  if (distance > 0) 
  {
    if (distance > SLOW_TURN_RATE_PER_CAL) 
    {
      return m_position + SLOW_TURN_RATE_PER_CAL;
    } 
    else 
    {
      return m_position + distance;
    }
  } 
  else if (distance < 0) 
  {
    if (distance < -SLOW_TURN_RATE_PER_CAL) 
    {
      return m_position - SLOW_TURN_RATE_PER_CAL;
    } 
    else 
    {
      return m_position + distance;
    }
  }
  return m_position;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //
// ============================================= END File MicroServo.cpp =========================================== //
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //