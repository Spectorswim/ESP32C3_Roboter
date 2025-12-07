// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
// ================================================= File Sensors.cpp ============================================== //
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
#include "Sensors.h"
#include <Arduino.h>

Sensors::Sensors(uint8_t sensorFrontPin, uint8_t sensorBackPin, uint8_t& sensorsON, uint8_t& lineDetector)
  : m_sensorFrontPin(sensorFrontPin), m_sensorBackPin(sensorBackPin), 
  m_sensorsON(sensorsON), m_lineDetector(lineDetector)
{
  BLACK_F = analogRead(m_sensorFrontPin) + 40;
  BLACK_B = analogRead(m_sensorBackPin)  + 40;
  // everything is already initialized in the initialization list
}

bool Sensors::chekSensorsInput()
{
  m_lineDetector = (analogRead(m_sensorFrontPin) > BLACK_F || analogRead(m_sensorBackPin) > BLACK_B);
  return m_sensorsON && m_lineDetector;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //
// ================================================ END File Sensors.cpp =========================================== //
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //