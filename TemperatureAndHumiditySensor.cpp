#include "TemperatureAndHumiditySensor.h"

DHT dhtSensor(DHT22);

float TemperatureAndHumiditySensor::GetLastHumidity(){
	return humidity;
}

float TemperatureAndHumiditySensor::GetLastTemperature(){
	return temperature;
}

void TemperatureAndHumiditySensor::UpdateValue(){
  temperature = dhtSensor.readTemperature(DHTPIN);
  humidity = dhtSensor.readHumidity(DHTPIN);
}

