// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
// =============================================== File main.ino =================================================== //
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> global variables and PINs definition >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //

// Sensors
constexpr byte SENSOR_FRONT = 0;      // GPIO0
constexpr byte SENSOR_BACK  = 1;      // GPIO1

// Left motor
constexpr byte MOTOR_LA = 18;         // GPIO18
constexpr byte MOTOR_LB = 19;         // GPIO19

// Right motor
constexpr byte MOTOR_RA = 3;          // GPIO3
constexpr byte MOTOR_RB = 2;          // GPIO2

// Micro Servo
constexpr byte SG90_PIN = 4;          // GPIO4

constexpr byte g_turnDeadZone = 10;

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< END global variables and PINs definition <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //

#include "RemoteXY_conf.h"
#include "Movement.h"
#include "MicroServo.h"
#include "Sensors.h"

#define DEBUG

Movement* movement;
MicroServo* servo;
Sensors* sensors;

void setup() 
{ 
  servo = new MicroServo(SG90_PIN, RemoteXY.position);
  movement = new Movement(MOTOR_LA, MOTOR_LB, MOTOR_RA, MOTOR_RB, 
      RemoteXY.linearSpeed, RemoteXY.angularSpeed, g_turnDeadZone);
  sensors = new Sensors(SENSOR_FRONT, SENSOR_BACK, RemoteXY.sensorsON, RemoteXY.lineDetector);
  RemoteXY_Init();                    // used to connect to RemoteXY
  Serial.begin(9600);
  delay(3000);
}

void loop()                           // do not call delay(), use instead RemoteXY_delay() 
{
  static bool processingEscapeMove = false; 
  static int8_t direction = 0;
  static unsigned long escapeMoveStartTime = 0;

  RemoteXY_Handler();
  if(sensors->chekSensorsInput()) //   if allowed and one of the sensors has detected a line
  {
    processingEscapeMove = true;
    direction = RemoteXY.linearSpeed;
    escapeMoveStartTime = millis();
  }

  if(processingEscapeMove)
  {
    if(millis() - escapeMoveStartTime < 500)
    {
      movement->performEscapeMove(direction);
    }
    else
    {
      processingEscapeMove = false;
    }
  }
  else
  {
    movement->processRemoteXYInput();
  }

  servo->checkPosition(); // puts the servo in one of the selected positions
#ifdef DEBUG
  Serial.print("Sensor front value: ");
  Serial.print(analogRead(SENSOR_FRONT));
  Serial.print("   \tSensor back value: ");
  Serial.print(analogRead(SENSOR_BACK));
  Serial.print("\n");
#endif
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //
// ============================================= END File main.ino ================================================= //
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //