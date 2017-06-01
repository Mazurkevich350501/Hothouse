#include "LightSensor.h"

int LightSensor::GetLightLevel(){
	  return lightMeter.readLightLevel();
}

void LightSensor::Init(){
    lightMeter.begin();
}
