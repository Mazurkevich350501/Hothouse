#include "ScreenManager.h"
#include "TemperatureAndHumiditySensor.h"
#include "LightSensor.h"
#include "LampManager.h"
#include "CO2History.h"

// Declare which fonts we will be using

ScreenManager screenManager;
TemperatureAndHumiditySensor tempAndHumSensor;
LightSensor lightSensor;
LampManager lampManager;
SensorValues sensorValues;
CO2History co2History;

void setup()
{
  Serial.begin(9600);
  screenManager.Init();
  lightSensor.Init();
}

void loop()
{
  tempAndHumSensor.UpdateValue();
  sensorValues.Temperature = tempAndHumSensor.GetLastTemperature();
  sensorValues.Humidity = tempAndHumSensor.GetLastHumidity();
  sensorValues.LightLevel = lightSensor.GetLightLevel();
  sensorValues.StrobeLength = lampManager.GetStrobeLength();
  sensorValues.DelayLength = lampManager.GetDelayLength();
  screenManager.Show(sensorValues);
  Serial.print(sensorValues.Temperature);
  Serial.print(" - ");
  Serial.println(sensorValues.Humidity);
  delay(1000);
}
