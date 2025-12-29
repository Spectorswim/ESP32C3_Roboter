// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
// ================================================= File Movement.h =============================================== //
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Motor.h"
#include <cstdint>


class Movement
{
  private:
    Motor m_left;
    Motor m_right;

    int8_t& m_movementSpeed;
    int8_t& m_turnRate;
    int8_t& m_gearBox;
    int8_t  m_turnDeadZone;

    // smoother speed curve
    int16_t speedCalculation(int8_t x);

    // dead zone consideration
    int16_t turnRateCalculation(int8_t x);

  public:
    Movement(
      int8_t LA, int8_t LB, int8_t RA, int8_t RB, 
      int8_t& movementSpeed, int8_t& turnRate, 
      int8_t turnDeadZone, int8_t& gearBox);
    void processRemoteXYInput();
    void performEscapeMove(int8_t& direction);
};

#endif // MOVEMENT_H
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //
// =============================================== END File Movement.h ============================================= //
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //