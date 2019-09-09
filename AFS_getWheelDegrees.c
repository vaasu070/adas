
#include"AFS_adc.h"
#include"AFS_getWheelDegrees.h"


float wheelDegrees(){

AFS_InitADC();
float steernig_value=AFS_ReadADC(1);

float steeringDegrees = (steernig_value*960.0)/1023.0;
float wheelDegrees = steeringDegrees/STEERINGRATIO;


return wheelDegrees-30;

 }
