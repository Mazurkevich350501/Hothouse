#include "SdManager.h"

SDManager::SDManager(bool withSd){
    this->withSd = withSd;
    if(!withSd) return;
    //инициализация сд карты
    if (!sd.begin(SD_CHIP_SELECT, SPI_FULL_SPEED)) {
        sd.initErrorHalt();
        return;
    }
    file = sd.open(LOG_FILE, O_WRITE | O_CREAT);
    file.println("--- Arduino Start ---");
    file.close();
}

Co2Value SDManager::ReadCo2Value(){
  Co2Value data;
  if(sd.exists(CO2_FILE) && withSd){  
        file = sd.open(CO2_FILE);
        file.read(&data, sizeof(Co2Value)); 
        file.close();
    }
  return data;
}

void SDManager::WriteCo2Value(Co2Value data){
    if(!withSd) return;
    file = sd.open(CO2_FILE, O_WRITE | O_CREAT | O_TRUNC);
    file.write(&data, sizeof(Co2Value));
    file.close();
}

void SDManager::WriteToLog(SensorValues data){
    if(!withSd) return;
    file = sd.open(LOG_FILE, O_WRONLY | O_APPEND | O_CREAT);
    file.print(++i); file.println(". ------------------");
    file.print("Temperature: "); file.print(sensorValues.Temperature); file.println("C");
    file.print("Humidity: "); file.print(sensorValues.Humidity); file.println("%");
    file.print("LightLevel: "); file.print(sensorValues.LightLevel); file.println("lux");
    file.print("StrobeLength: "); file.print(sensorValues.StrobeLength); file.println("ms");
    file.print("DelayLength: "); file.print(sensorValues.DelayLength); file.println("ms");
    file.close();
}

