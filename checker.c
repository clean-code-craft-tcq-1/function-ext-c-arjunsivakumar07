#include <stdio.h>
#include <assert.h>
#include<stdbool.h>
#include "checker.h"

int LowerThresholdChecker(float attribute_value, float lowerthreshold)
{
  bool isValid = attribute_value < lowerthreshold;
  if(isValid)
    return 0;
  else return 1;
}

int UpperThresholdChecker(float attribute_value, float upperthreshold)
{
  bool isValid = attribute_value > upperthreshold;
  if(isValid)
    return 0;
  else return 1;
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
  
  int TemperatureLowerRange,TemperatureHigherRange,TemperatureStatus,SOCLowerRange,SOCHigherRange,SOCStatus,ChargeRateStatus,ValidityofBattery;

  TemperatureLowerRange  = LowerThresholdChecker(temperature,MINTEMP);
  TemperatureHigherRange = UpperThresholdChecker(temperature,MAXTEMP) ;
  TemperatureStatus      = TemperatureLowerRange&TemperatureHigherRange;
  
  
  SOCLowerRange          = LowerThresholdChecker(soc,MINSOC) ;
  SOCHigherRange         = UpperThresholdChecker(soc,MAXSOC); 
  SOCStatus              = SOCLowerRange&SOCHigherRange;
  
  
  ChargeRateStatus       = UpperThresholdChecker(chargeRate,CHARGERATETHRESHOLD);
  ValidityofBattery = (TemperatureStatus)&(SOCStatus)&ChargeRateStatus;
  
  if(ValidityofBattery)
    printf("Battery is ok");
  
 return ValidityofBattery;
  
}


int main() {
    assert(batteryIsOk(45,70,0.7));   
    assert(!batteryIsOk(50, 70, 0.7));
    assert(!batteryIsOk(45, 85, 0.7));
    assert(!batteryIsOk(45, 30, 1));
    assert(!batteryIsOk(0, 10, 0));
    assert(!batteryIsOk(50, 85, 0.9));
}
