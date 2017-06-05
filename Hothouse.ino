#include "ScreenManager.h"
#include "TemperatureAndHumiditySensor.h"
#include "LightSensor.h"
#include "LampManager.h"
#include "SdManager.h"

#define GRAPH_UPDATE_TIME 60
#define LOG_TIME 60

ScreenManager screenManager;
TemperatureAndHumiditySensor tempAndHumSensor;
LightSensor lightSensor;
LampManager lampManager;
SensorValues sensorValues;
CO2History co2History;
SDManager sdManager(true, (int)LOG_TIME);

int secondCount = 0; //количество секунд

void setup()
{
  Serial.begin(9600);
  screenManager.Init();
  lampManager.Init();
  co2History.SetVal(sdManager.ReadCo2Value());
  co2History.Update();
  pinMode(DHTPIN, INPUT);
  lightSensor.Init();
}

void loop()
{
  if(secondCount >= 120) secondCount = 0; //раз в минуту счетчик секунд сбрасывается
  if(secondCount % 4 == 0) {
    tempAndHumSensor.UpdateValue();
                   //каждую секунду счетчик увеличивается на 1
  }
  if(secondCount % (GRAPH_UPDATE_TIME*2) == 0) {
    co2History.Update();                  //раз в минуту читаются данные с датчика CO2 и сохрвняются
    sdManager.WriteCo2Value(co2History.GetVal());
    screenManager.DrawGraph(co2History);  //рисует график
  }
  sensorValues.CO2 = co2History.GetCurrentValue();
  sensorValues.Temperature = tempAndHumSensor.GetLastTemperature();
  sensorValues.Humidity = tempAndHumSensor.GetLastHumidity();
  sensorValues.LightLevel = lightSensor.GetLightLevel();
  sensorValues.StrobeLength = lampManager.GetStrobeLength();
  sensorValues.DelayLength = lampManager.GetDelayLength();
  screenManager.Show(sensorValues);       //отображение данных датчиков на экране
  if(secondCount % (LOG_TIME*2) == 0){
    sdManager.WriteToLog(sensorValues);
  }
  delay(500);
  secondCount += 1;
}
