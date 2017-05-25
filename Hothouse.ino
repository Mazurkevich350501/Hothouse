#include "ScreenManager.h"
#include "TemperatureAndHumiditySensor.h"
#include "LightSensor.h"
#include "LampManager.h"
#include "CO2History.h"


TemperatureAndHumiditySensor tempAndHumSensor;
LightSensor lightSensor;
LampManager lampManager;
SensorValues sensorValues;
  
void setup()
{
  Serial.begin(9600);
}

void loop()
{

ScreenManager screenManager;
  tempAndHumSensor.UpdateValue();
  sensorValues.Temperature = tempAndHumSensor.GetLastTemperature();
  sensorValues.Humidity = tempAndHumSensor.GetLastHumidity();
  sensorValues.LightLevel = lightSensor.GetLightLevel();
  //sensorValues.StrobeLength = lampManager.GetStrobeLength();
  //sensorValues.DelayLength = lampManager.GetDelayLength();
  screenManager.Show(sensorValues);
  delay(1000);
}
