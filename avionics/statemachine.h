/*State Machine Header*/
#ifndef STATEMACHINE_H
#define STATEMACHINE_H

/*Includes------------------------------------------------------------*/

/*Constants------------------------------------------------------------*/
#define LAUNCH_CHECKS 4
#define MACH_CHECKS 3
#define APOGEE_CHECKS   5
#define MACH_LOCK_CHECKS 10
#define MAIN_CHECKS     10
#define LAND_CHECKS     20

#define LAUNCH_THRESHOLD 150 // in meters
#define MACH_THRESHOLD 275 //in meters per second ??
#define MACH_LOCK_THRESHOLD 250 //in meters per second??
#define FINAL_DESCENT_THRESHOLD 200 //meters
#define LAND_HEIGHT_THRESHOLD 50 //meters
#define LAND_VELOCITY_THRESHOLD 1  //m/s

#define SEA_PRESSURE 1013 //TODO: calibrate

/*Variables------------------------------------------------------------*/
enum FlightStates {
  STANDBY,
  ARMED,
  ASCENT,
  MACH_LOCK,
  INITIAL_DESCENT,
  FINAL_DESCENT,
  LANDED
};

/*Functions------------------------------------------------------------*/
void switchState(FlightStates new_state);
void stateMachine(float*, float*, float*, float*, float*);

#endif