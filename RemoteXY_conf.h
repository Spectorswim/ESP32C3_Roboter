// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
// ============================================= File RemoteXY_conf.h ============================================== //
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
#ifndef REMOTEXY_CONF_H
#define REMOTEXY_CONF_H

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP32CORE_BLE

#include <BLEDevice.h>

// RemoteXY connection settings 
#define REMOTEXY_BLUETOOTH_NAME "14-C"
#define REMOTEXY_ACCESS_PASSWORD "14-C_password"


#include <RemoteXY.h>

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t const PROGMEM RemoteXY_CONF_PROGMEM[] =   // 109 bytes V19 
  { 255,4,0,1,0,102,0,19,0,0,0,82,111,98,111,116,101,114,32,49,
  52,45,67,0,26,2,200,84,200,92,1,1,4,0,5,5,22,60,60,2,
  24,66,66,32,16,26,31,3,152,1,45,82,149,1,50,90,2,62,26,70,
  28,3,14,14,27,3,15,15,144,26,37,0,10,90,6,20,20,89,6,22,
  22,48,4,26,24,83,101,110,115,111,114,115,32,79,78,0,31,83,111,110,
  100,111,114,115,32,79,70,70,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t linearSpeed; // from -100 to 100
  int8_t angularSpeed; // from -100 to 100
  uint8_t position; // from 0 to 1
  uint8_t sensorsON; // =1 if state is ON, else =0, from 0 to 1

    // output variables
  uint8_t lineDetector; // from 0 to 1

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
#endif // REMOTEXY_CONF_H
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //
// ========================================== END File RemoteXY_conf.h ============================================= //
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //