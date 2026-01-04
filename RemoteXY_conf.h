// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
// ============================================= File RemoteXY_conf.h ============================================== //
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
#ifndef REMOTEXY_CONF_H
#define REMOTEXY_CONF_H

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP32CORE_BLE

#include <BLEDevice.h>

// RemoteXY connection settings 
#define REMOTEXY_BLUETOOTH_NAME "Roboter 14-C"
#define REMOTEXY_ACCESS_PASSWORD "password_14-C"


#include <RemoteXY.h>

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t const PROGMEM RemoteXY_CONF_PROGMEM[] =   // 92 bytes V19 
  { 255,5,0,0,0,85,0,19,0,0,0,82,111,98,111,116,101,114,32,49,
  52,45,67,0,26,2,200,84,106,200,1,1,4,0,5,6,21,60,60,203,
  50,143,143,32,119,26,31,10,106,5,15,15,20,7,57,57,48,4,26,31,
  79,78,0,31,79,70,70,0,3,164,7,35,64,71,43,39,105,2,119,26,
  4,138,42,13,38,58,95,7,86,0,119,28 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t angularSpeed; // from -100 to 100
  int8_t linearSpeed; // from -100 to 100
  uint8_t sensorsON; // =1 if state is ON, else =0, from 0 to 1
  uint8_t position; // from 0 to 2
  int8_t gearBox; // from 0 to 100

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
#endif // REMOTEXY_CONF_H
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //
// ========================================== END File RemoteXY_conf.h ============================================= //
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //