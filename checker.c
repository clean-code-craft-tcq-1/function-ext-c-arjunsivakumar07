#include <stdio.h>
#include <assert.h>
#include "checker.h"

void DisplaybatteryStatus(struct attribute battery_attribute, int IdxMessage)
{
    if (Language == ENGLISH)
    {
        printf("%s %s\n", battery_attribute.attribute_name, BatteryStatus_English[IdxMessage]);
    }
    else{
        printf("%s %s\n", battery_attribute.attribute_name, BatteryStatus_German[IdxMessage]);
    }
}

int LowerThresholdChecker(float attribute_value,struct attribute battery_attribute)
{
  if(attribute_value < battery_attribute.attribute_minvalue)
    {
        DisplaybatteryStatus(battery_attribute,0);
        return 1;
    }
    else
    {
        return 0;
    }
}

int Check_LowAttributeWarning(float attribute_value,struct attribute battery_attribute)
{
    if((attribute_value <= battery_attribute.attribute_LowWarning) && (attribute_value > battery_attribute.attribute_minvalue))
   {
       DisplaybatteryStatus(battery_attribute,2);
       return 1;
   }
   else
   {
       return 0;
   }
}


int UpperThresholdChecker(float attribute_value, struct attribute battery_attribute)
{
  if(attribute_value > battery_attribute.attribute_maxvalue)
    {
        DisplaybatteryStatus(battery_attribute,1);
        return 1;
    }
    else
    {
        return 0;
    }
}

int Check_HighAttributeWarning(float attribute_value,struct attribute battery_attribute)
{
    if((attribute_value >= battery_attribute.attribute_HighWarning)&& (attribute_value < battery_attribute.attribute_maxvalue))
    {
       DisplaybatteryStatus(battery_attribute,3);
       return 1;
    }
   else
    {
       return 0;
    }
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
  
  int TemperatureStatus,SOCStatus,ChargeRateStatus = 0;

    TemperatureStatus =
    LowerThresholdChecker(temperature,battery_temperature) + UpperThresholdChecker(temperature,battery_temperature)+ Check_LowAttributeWarning(temperature,battery_temperature) + Check_HighAttributeWarning(temperature,battery_temperature);
    
    SOCStatus =
    LowerThresholdChecker(soc,battery_soc) + UpperThresholdChecker(soc,battery_soc)+Check_LowAttributeWarning(soc,battery_soc) + Check_HighAttributeWarning(soc,battery_soc);
    
    ChargeRateStatus =
    LowerThresholdChecker(chargeRate,battery_chargeRate)+UpperThresholdChecker(chargeRate,battery_chargeRate)+ Check_LowAttributeWarning(chargeRate,battery_chargeRate)+Check_HighAttributeWarning(chargeRate,battery_chargeRate);
  
    if((TemperatureStatus + SOCStatus + ChargeRateStatus)==0)
    {
       DisplaybatteryStatus(battery_attribute,4);
    }
    
    return!(TemperatureStatus + SOCStatus + ChargeRateStatus);
  
}


int main() {
    
    assert(batteryIsOk(40,70,0.7));    /*Battery is ok*/
    assert(!batteryIsOk(50, 70, 0.7));  /*Temperature high limit breach*/
    assert(!batteryIsOk(40, 85, 0.7));  /*SOC high limit breach*/
    assert(!batteryIsOk(30, 30, 1));    /*ChargeRate high limit breach*/
    assert(!batteryIsOk(-20, 70, 0.7));   /*Temperature low limit breach*/
    assert(!batteryIsOk(40, 10, 0.7));  /*SOC low limit breach*/
    assert(!batteryIsOk(30, 30, -1));    /*ChargeRate high limit breach*/
    assert(!batteryIsOk(50,-1,-1));    /*All attributes breached*/
    assert(!batteryIsOk(42.75, 70, 0.7));  /*Temperature high limit breach*/
    assert(!batteryIsOk(40, 77, 0.7));  /*SOC high limit breach*/
    assert(!batteryIsOk(30, 30, 0.77));    /*ChargeRate high limit breach*/
    assert(!batteryIsOk(2, 70, 0.7));   /*Temperature low limit breach*/
    assert(!batteryIsOk(40, 23, 0.7));  /*SOC low limit breach*/
    assert(!batteryIsOk(30, 30, 0.02));    /*ChargeRate high limit breach*/
    assert(!batteryIsOk(1.75,20,0.04)); /*All attributes on alert*/
}
