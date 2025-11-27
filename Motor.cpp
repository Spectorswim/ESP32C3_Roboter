// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
// ================================================= File Motor.cpp ================================================ //
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
#include "Motor.h"
#include "PWM.h"
#include <cstdint>



Motor::Motor(int8_t pinForward, int8_t pinBackward)
: m_forward(PWM(pinForward)), m_backward(PWM(pinBackward))
{
  // everything is already initialized in the initialization list
}

void Motor::write(int16_t value)
{
  if(value == 0)
  {
    m_forward.write(0);
    m_backward.write(0);
  }
  else if(value > 0)
  {
    value = (value > 255) ? 255 : value;
    m_forward.write(value);
    m_backward.write(0);
  }
  else
  {
    value = (value < -255) ? 255 : -value;
    m_forward.write(0);
    m_backward.write(value);
  }
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //
// =============================================== END File Motor.cpp ============================================== //
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //