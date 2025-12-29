// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
// ================================================ File Movement.cpp ============================================== //
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
#include "Motor.h"
#include "Movement.h"
#include <cstdint>

constexpr int SPEED_CURVE = 15; // this is the percentage of joystick tilt to get 50% power
constexpr int LOW_SPEED_TO_INPLACE = 15;
constexpr int REVERSE_SPEED = 255;

int16_t Movement::speedCalculation(int8_t x)
{
  int32_t y = x * 255 / 100; 
  
  if (y > 255) y = 255;
  if (y < -255) y = -255;
  
  return (int16_t)y;
}

// dead zone consideration
int16_t Movement::turnRateCalculation(int8_t x)
{
  int8_t ax = (x < 0) ? -x : x;
  int16_t sign = (x < 0) ? -1 : 1;
  int y = 0;

  if(ax > m_turnDeadZone)
    y = ((ax - m_turnDeadZone) * 255 / (100 - m_turnDeadZone));

  return ((y > 255) ? 255 : y) * sign;
}

Movement::Movement(int8_t LA, int8_t LB, int8_t RA, int8_t RB,
                   int8_t& movementSpeed, int8_t& turnRate, int8_t turnDeadZone, int8_t& gearBox)
  : m_left(Motor(LA, LB)),
    m_right(Motor(RA, RB)),
    m_movementSpeed(movementSpeed),
    m_turnRate(turnRate),
    m_turnDeadZone(turnDeadZone),
    m_gearBox(gearBox)
{
  // No need for pinMode/analogWrite - class Motor configures everything itself
}

void Movement::processRemoteXYInput()
{
  int inputMove = m_movementSpeed; // -100..100
  int inputTurn = m_turnRate;      // -100..100

  int16_t linearSpeed  = speedCalculation(inputMove);     // -255..255
  int16_t angularSpeed = turnRateCalculation(inputTurn);  // -255..255

  int16_t leftSpeed  = 0;
  int16_t rightSpeed = 0;

  // In-place rotation
  if ((inputMove >= 0 ? inputMove : -inputMove) <= LOW_SPEED_TO_INPLACE && angularSpeed != 0)
  {
      leftSpeed  =  angularSpeed;
      rightSpeed = -angularSpeed;
  }
  else
  {
    angularSpeed /= 3;  // because more precise control is required while driving

    if (linearSpeed > 0) 
    {
      if (angularSpeed > 0) 
      {
        leftSpeed  = linearSpeed;            
        rightSpeed = linearSpeed - angularSpeed; 
      } 
      else 
      {
        leftSpeed  = linearSpeed + angularSpeed;
        rightSpeed = linearSpeed;        
      }
    }
    else
    {
      if (angularSpeed > 0) 
      {
        leftSpeed  = linearSpeed;            
        rightSpeed = linearSpeed + angularSpeed; 
      } 
      else 
      {
        leftSpeed  = linearSpeed - angularSpeed;
        rightSpeed = linearSpeed;        
      }
    }
    
    
    // Note: values may exceed the -255..255 range here,
    // but Motor::write() will internally clamp them,
    // so no explicit constrain() is required.
  }

  double multiplicator = (m_gearBox / 10 * 3 + 70.0) / 100.0;

  m_left.write(multiplicator * leftSpeed);
  m_right.write(multiplicator * rightSpeed);
}

void Movement::performEscapeMove(int8_t& direction)
{
  if (direction == 0) return;
  if(direction < 0)
  {      
    m_left.write(-REVERSE_SPEED);
    m_right.write(-REVERSE_SPEED);
  }
  else
  {
    m_left.write(REVERSE_SPEED);
    m_right.write(REVERSE_SPEED);
  }
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //
// ============================================ END File Movement.cpp ============================================== //
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //