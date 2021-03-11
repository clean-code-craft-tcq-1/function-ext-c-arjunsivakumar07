#ifndef BatteryHealthCheck_h
#define BatteryHealthCheck_h

#include <stdio.h>

#define MAXTEMP 45.0F
#define MINTEMP 0.0F
#define MAXSOC 80.0F
#define MINSOC 20.0F
#define CHARGERATETHRESHOLD 0.8F

int Check_Attributelow(float attribute_value, float lowerthreshold);
int Check_AttributeHigh(float attribute_value, float upperthreshold);
int batteryIsOk(float attribute_value, float lowerthreshold, float higherthreshold);

#endif
