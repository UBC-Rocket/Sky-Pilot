/*Sensors Header*/
#ifndef CALCULATIONS_H
#define CALCULATIONS_H

/*Includes------------------------------------------------------------*/
#include <stdint.h>
#include "sensors.h"

/*Constants------------------------------------------------------------*/
#define PRESSURE_AVG_SET_SIZE   15

/*Functions------------------------------------------------------------*/
void calculateValues(float*, float*, float*, float*, float*, float*, float*, unsigned long*, float*);
void addToPressureSet(float*, float);
float calculatePressureAverage(float*);

#endif
