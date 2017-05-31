#include "ScreenManager.h"
#include "TemperatureAndHumiditySensor.h"
#include "LightSensor.h"
#include "LampManager.h"

// Declare which fonts we will be using

ScreenManager screenManager;
TemperatureAndHumiditySensor tempAndHumSensor;
LightSensor lightSensor;
LampManager lampManager;
SensorValues sensorValues;
CO2History co2History;

int secondCount = 0; //количество секунд

void setup()
{
  Serial.begin(9600);
  screenManager.Init();
  lightSensor.Init();
  lampManager.Init();
  co2History.Update();
  pinMode(DHTPIN, INPUT);
}

void loop()
{
  if(secondCount >= 60) secondCount = 0; //раз в минуту счетчик секунд сбрасывается
  if(secondCount % 4 == 0) {
    tempAndHumSensor.UpdateValue();
    secondCount += 1;                   //каждую секунду счетчик увеличивается на 1
  }
  if(secondCount % 60 == 0) {
    co2History.Update();                  //раз в минуту читаются данные с датчика CO2 и сохрвняются
    screenManager.DrawGraph(co2History);  //рисует график
  }
  sensorValues.CO2 = co2History.GetLastValue();
  sensorValues.Temperature = tempAndHumSensor.GetLastTemperature();
  sensorValues.Humidity = tempAndHumSensor.GetLastHumidity();
  sensorValues.LightLevel = lightSensor.GetLightLevel();
  sensorValues.StrobeLength = lampManager.GetStrobeLength();
  sensorValues.DelayLength = lampManager.GetDelayLength();
  screenManager.Show(sensorValues);       //отображение данных датчиков на экране
  delay(500);
}
