#ifndef BatteryHealthCheck_h
#define BatteryHealthCheck_h

#include <stdio.h>


#define ENGLISH 1
#define GERMAN  2
int Language = ENGLISH;

struct attribute
{
    char attribute_name[20];
    float attribute_maxvalue;
    float attribute_minvalue;
    float attribute_HighWarning;
    float attribute_LowWarning;
   
}battery_attribute;

struct attribute battery_temperature ={"temperature",45,0,42.75,2.25};
struct attribute battery_soc = {"soc",80,20,76,24};
struct attribute battery_chargeRate = {"chargeRate",0.8,0,0.76,0.04};

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

void DisplaybatteryStatus(struct attribute battery_attribute, int IdxMessage);
int Check_Attributelow(float attribute_value, struct attribute battery_attribute);
int Check_AttributeHigh(float attribute_value, struct attribute battery_attribute);
int batteryIsOk(float temperature, float soc, float chargeRate);
int Check_LowAttributeWarning(float attribute_value,struct attribute battery_attribute);
int Check_HighAttributeWarning(float attribute_value, struct attribute battery_attribute);


#endif
