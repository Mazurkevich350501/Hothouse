#include "LightSensor.h"

int LightSensor::GetLightLevel(){
	  return lightMeter.readLightLevel();
}

void LightSensor::Init(){
    lightMeter.begin(BH1750_CONTINUOUS_HIGH_RES_MODE);
}
