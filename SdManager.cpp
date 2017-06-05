#include "SdManager.h"

SDManager::SDManager(bool withSd,int logUpdateTime ){
    this->withSd = withSd;
    this->logUpdateTime = logUpdateTime;
    if(!withSd) return;
    //инициализация сд карты
    if (!sd.begin(SD_CHIP_SELECT, SPI_FULL_SPEED)) {
        sd.initErrorHalt();
        return;
    }
    file = sd.open(LOG_FILE, O_WRONLY | O_APPEND | O_CREAT);
    file.println("--- Arduino Start ---");
    file.close();
}

Co2Value SDManager::ReadCo2Value(){
  Co2Value data;
    data.headIndex = 0;
    for(int i = 0; i < HISTORY_LENGTH; i++)
      data.values[i] = 0;
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
    double time = logUpdateTime/60.;
    file.print(i*time); file.println(" min. ------------------");
    file.print("CO2: "); file.print(data.CO2); file.println("ppm");
    file.print("Temperature: "); file.print(data.Temperature); file.println("C");
    file.print("Humidity: "); file.print(data.Humidity); file.println("%");
    file.print("LightLevel: "); file.print(data.LightLevel); file.println("lux");
    file.print("StrobeLength: "); file.print(data.StrobeLength); file.println("ms");
    file.print("DelayLength: "); file.print(data.DelayLength); file.println("ms");
    file.close();
    i+=1.;
}

