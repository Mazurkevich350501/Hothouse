#include "TemperatureAndHumiditySensor.h"

float TemperatureAndHumiditySensor::GetLastHumidity(){
	return humidity;
}

float TemperatureAndHumiditySensor::GetLastTemperature(){
	return temperature;
}

void TemperatureAndHumiditySensor::UpdateValue(){
	byte temp, hum;
	if(dht11.read(DHTPIN, &temp, &hum, NULL)){
		temperature = temp;
		humidity = hum;
	}
}
