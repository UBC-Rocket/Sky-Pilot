/*Commands Header*/
#ifndef COMMANDS_H
#define COMMANDS_H

/*Includes------------------------------------------------------------*/
#include "sensors.h"

#include <Arduino.h>

/*Constants------------------------------------------------------------*/

#define ARM 'r'
#define CAMERAS_ON 'C'
#define CAMERAS_OFF 'O'
#define RESET 'R'
#define PING 'p'
#define MAIN 'm'
#define DROGUE 'd'
#define STATUS 'S'
#define STARTUP_BUZZER 'B'
#define RECOVERY_BUZZER 'b'
#define DO_NOTHING '\0'


/*Variables------------------------------------------------------------*/

/*Functions------------------------------------------------------------*/
// void doCommand(char,FlightStates * state, InitStatus *status);
void sendRadioResponse(const char*);
void communicateThroughSerial(FlightStates * state, InitStatus * status);
bool checkCommand(char*);

#endif
