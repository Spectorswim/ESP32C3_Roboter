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
uint8_t RemoteXY_CONF[] =   // 67 bytes
  { 255,4,0,1,0,60,0,19,0,0,0,69,83,80,95,70,66,48,51,95,
  49,52,45,67,0,26,1,106,200,1,1,4,0,5,2,8,60,60,32,16,
  26,31,3,3,156,97,36,131,62,26,70,74,25,26,26,144,26,37,0,10,
  73,88,24,24,0,4,26 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t linearSpeed; // from -100 to 100
  int8_t angularSpeed; // from -100 to 100
  uint8_t position; // from 0 to 2
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