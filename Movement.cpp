// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
// ================================================ File Movement.cpp ============================================== //
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
#include "Motor.h"
#include "Movement.h"
#include <cstdint>

constexpr int SPEED_CURVE = 15; // this is the percentage of joystick tilt to get 50% power
constexpr int LOW_SPEED_TO_INPLACE = 128;
constexpr int REVERSE_SPEED = 255;

// smoother speed curve
int16_t Movement::speedCalculation(int8_t x)
{
  int8_t ax = (x < 0) ? -x : x;
  int16_t sign = (x < 0) ? -1 : 1;
  int y;

  if(ax <= SPEED_CURVE)
    y = (127 * ax + SPEED_CURVE / 2) / SPEED_CURVE;
  else
    y = 127 + (128 * (ax - SPEED_CURVE) + (100 - SPEED_CURVE) / 2) / (100 - SPEED_CURVE);

  return ((y > 255) ? 255 : y) * sign;
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
                   int8_t& movementSpeed, int8_t& turnRate, int8_t turnDeadZone)
  : m_left(Motor(LA, LB)),
    m_right(Motor(RA, RB)),
    m_movementSpeed(movementSpeed),
    m_turnRate(turnRate),
    m_turnDeadZone(turnDeadZone)
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
  if ((linearSpeed >= 0 ? linearSpeed : -linearSpeed) <= LOW_SPEED_TO_INPLACE && angularSpeed != 0)
  {
    if (inputTurn > 0)
    {
      leftSpeed  = -angularSpeed;
      rightSpeed =  angularSpeed;
    } 
    else 
    {
      leftSpeed  = -angularSpeed;
      rightSpeed =  angularSpeed;
    }
  }
  else
  {
    angularSpeed /= 4;  // because more precise control is required while driving
    if(linearSpeed < 0) // reverse angularSpeed ​​when reversing for more intuitive control
    {
      angularSpeed = -angularSpeed;
    } 
    
    // slows down the turning side and speeds up the other
    leftSpeed  = linearSpeed - angularSpeed;
    rightSpeed = linearSpeed + angularSpeed;
    // Note: values may exceed the -255..255 range here,
    // but Motor::write() will internally clamp them,
    // so no explicit constrain() is required.
  }

  m_left.write(leftSpeed);
  m_right.write(rightSpeed);
}

void Movement::performEscapeMove(int8_t& direction)
{
  if (direction = 0) return;
  if(direction > 0)
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