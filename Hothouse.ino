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

int secondCount = 0;

void setup()
{
  Serial.begin(9600);
  screenManager.Init();
  lightSensor.Init();
  lampManager.Init();
}

void loop()
{
  if(secondCount >= 60) secondCount = 0;
  if(secondCount % 2 == 0) tempAndHumSensor.UpdateValue();
  if(secondCount % 60 == 0) co2History.Update();
  sensorValues.CO2 = co2History.GetLastValue();
  sensorValues.Temperature = tempAndHumSensor.GetLastTemperature();
  sensorValues.Humidity = tempAndHumSensor.GetLastHumidity();
  sensorValues.LightLevel = lightSensor.GetLightLevel();
  sensorValues.StrobeLength = lampManager.GetStrobeLength();
  sensorValues.DelayLength = lampManager.GetDelayLength();
  screenManager.Show(sensorValues);
  delay(500);
}
