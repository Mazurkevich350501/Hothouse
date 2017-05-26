#include "CO2History.h"

CO2History::CO2History(){
    if (!sd.begin(SD_CHIP_SELECT, SPI_FULL_SPEED)) {
        sd.initErrorHalt();
        return;
    }

    if(sd.exists(FILE_NAME)){  
        myFile = sd.open(FILE_NAME);
        myFile.read(&data, sizeof(Data)); 
        myFile.close();
    }
    else{
        data.headIndex = 0;
        for(int i = 0; i < HISTORY_LENGTH; i++)
            data.values[i] = 0;
    }
}

int CO2History::Read(int index){
    if(index > HISTORY_LENGTH || index < 0) return 0;
    return (index + data.headIndex) > HISTORY_LENGTH
        ? data.values[HISTORY_LENGTH - (index + data.headIndex)]
        : data.values[index + data.headIndex];
}

void CO2History::Update(){
    data.headIndex = data.headIndex > 0
        ? data.headIndex - 1
        : HISTORY_LENGTH;
    data.values[data.headIndex] = getPpmValue();
    save();
}

int CO2History::GetHistoryLength(){
    return HISTORY_LENGTH;
}

int CO2History::GetLastValue(){
    return Read(0);
}

void CO2History::save(){
    myFile = sd.open(FILE_NAME, O_WRITE | O_CREAT | O_TRUNC);
    myFile.write(&data, sizeof(Data));
    myFile.close();
}

int CO2History::getPpmValue(){
    return convertToPpm(analogRead(SENSOR_PIN));
}

int CO2History::convertToPpm(float Vout){
    int RL = 10;
    float R0 = 76.63;
    float Rs=( ( 5.0 * RL ) - ( RL * Vout ) ) / Vout;
    float ratio=Rs/R0;
    ratio=ratio*0.3611;
    return (146.15*(2.868-ratio)+10);
}