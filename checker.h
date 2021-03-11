#ifndef BatteryHealthCheck_h
#define BatteryHealthCheck_h

#include <stdio.h>


#define ENGLISH 1
#define GERMAN  2
int Sel_Language = ENGLISH;

#define MAXTEMP 45.0F
#define MINTEMP 0.0F
#define MAXSOC 80.0F
#define MINSOC 20.0F
#define CHARGERATETHRESHOLD_MAX 0.8F
#define CRMIN 0.0F
#define TEMP_UPPER_WARNING 42.75F
#define TEMP_LOWER_WARNING 2.25F
#define SOC_UPPER_WARNING 76.0F
#define SOC_LOWER_WARNING 24.0F
#define CR_UPPER_WARNING 0.76F
#define CR_LOWER_WARNING 0.04F

const char *BatteryStatus_English[] =
{
    "has breached lower limit ",
    "has breached higher limit",
    "has approached lower limit",
    "has approachied higher limit",
    "battery is ok"
};

const char *BatteryStatus_German[] =
{
    "ishat die Untergrenze überschritten",
    "ishat die Obergrenze überschritten",
    "hat sich der Untergrenze genähert",
    "hat sich der Obergrenze genähert",
    "Batterie ist in Ordnung"
};

void DisplaybatteryStatus(float attribute_value, int IdxMessage);
int Check_Attributelow(float attribute_value, float lowerthreshold);
int Check_AttributeHigh(float attribute_value, float upperthreshold);
int batteryIsOk(float attribute_value, float lowerthreshold, float higherthreshold);
int Check_LowAttributeWarning(float attribute_value,float lowerthreshold_warning, float lowerthreshold);
int Check_HighAttributeWarning(float attribute_value, float upperthreshold_warning, float upperthreshold);


#endif
