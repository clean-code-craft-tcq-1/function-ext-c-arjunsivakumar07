#include <stdio.h>
#include <assert.h>
#include<stdbool.h>
#include "checker.h"

void DisplaybatteryStatus(float attribute_value, int IdxMessage)
{
    if (Sel_Language == ENGLISH)
    {
        printf("%f %s\n",attribute_value, BatteryStatus_English[IdxMessage]);
    }
    else{
        printf("%f %s\n",attribute_value,BatteryStatus_German[IdxMessage]);
    }
}

int LowerThresholdChecker(float attribute_value, float lowerthreshold)
{
  bool isValid = attribute_value < lowerthreshold;
  if(isValid)
  {
    DisplaybatteryStatus(attribute_value,0); 
    return 0; 
  }
    
  else return 1;
}

int Check_LowAttributeWarning(float attribute_value,float lowerthreshold_warning, float lowerthreshold)
{
   if((attribute_value<=lowerthreshold_warning) && (attribute_value > lowerthreshold))
   {
       DisplaybatteryStatus(attribute_value,2);
       return 0;
   }
   else
   {
       return 1;
   }
}


int UpperThresholdChecker(float attribute_value, float upperthreshold)
{
  bool isValid = attribute_value > upperthreshold;
  if(isValid)
  {
    DisplaybatteryStatus(attribute_value,1);
    return 0;
  }
  else return 1;
}

int Check_HighAttributeWarning(float attribute_value,float upperthreshold_warning,float upperthreshold)
{
   if((attribute_value >= upperthreshold_warning)&& (attribute_value < upperthreshold))
   {
        DisplaybatteryStatus(attribute_value,3);
       return 0;
   }
   else
   {
       return 1;
   }
}
int batteryIsOk(float temperature, float soc, float chargeRate) {
  
  int TemperatureLowerRange,TemperatureHigherRange,TemperatureStatus,SOCLowerRange,SOCHigherRange,SOCStatus,ChargeRateStatus,ValidityofBattery,TemperatureLowAttributeBreach,TemperatureHighAttributeBreach,SOCLowAttributeBreach,SOCHighAttributeBreach,ChargeRateLowerRange,ChargeRateHigherRange,CRLowAttributeBreach,CRHighAttributeBreach;

  TemperatureLowerRange  = LowerThresholdChecker(temperature,MINTEMP);
  TemperatureHigherRange = UpperThresholdChecker(temperature,MAXTEMP) ;
  TemperatureLowAttributeBreach = Check_LowAttributeWarning(temperature,TEMP_LOWER_WARNING,MINTEMP);
  TemperatureHighAttributeBreach = Check_HighAttributeWarning(temperature,TEMP_UPPER_WARNING, MAXTEMP);
  TemperatureStatus      = TemperatureLowerRange&TemperatureHigherRange&TemperatureLowAttributeBreach&TemperatureHighAttributeBreach;
  
  
  
  SOCLowerRange          = LowerThresholdChecker(soc,MINSOC) ;
  SOCHigherRange         = UpperThresholdChecker(soc,MAXSOC); 
  SOCLowAttributeBreach  = Check_LowAttributeWarning(soc,SOC_LOWER_WARNING,MINSOC);
  SOCHighAttributeBreach = Check_HighAttributeWarning(soc,SOC_UPPER_WARNING, MAXSOC);
  SOCStatus              = SOCLowerRange&SOCHigherRange&SOCLowAttributeBreach&SOCHighAttributeBreach;
  
  ChargeRateLowerRange   = LowerThresholdChecker(chargeRate,CRMIN);
  ChargeRateHigherRange  = UpperThresholdChecker(chargeRate,CHARGERATETHRESHOLD_MAX);
  CRLowAttributeBreach   = Check_LowAttributeWarning(chargeRate,CR_LOWER_WARNING,CRMIN);
  CRHighAttributeBreach  = Check_HighAttributeWarning(chargeRate,CR_UPPER_WARNING, CHARGERATETHRESHOLD_MAX);
  ChargeRateStatus       = ChargeRateLowerRange&ChargeRateHigherRange&CRLowAttributeBreach&CRHighAttributeBreach;
  
  ValidityofBattery = (TemperatureStatus)&(SOCStatus)&ChargeRateStatus;
  
  if(ValidityofBattery)
    printf(" Battery is ok\n");
  
 return ValidityofBattery;
  
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
