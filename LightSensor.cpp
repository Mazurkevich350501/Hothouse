#include "LightSensor.h"

int LightSensor::GetLightLevel(){
	  return lightMeter->readLightLevel();
}

LightSensor::LightSensor(){
    lightMeter = new BH1750(0x23);
    lightMeter->begin(BH1750_CONTINUOUS_HIGH_RES_MODE);
}
