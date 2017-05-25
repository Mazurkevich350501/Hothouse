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

void CO2History::Update(int value){
    data.headIndex = data.headIndex > 0
        ? data.headIndex - 1
        : HISTORY_LENGTH;
    data.values[data.headIndex] = value;
    save();
}

void CO2History::save(){
    myFile = sd.open(FILE_NAME, O_WRITE | O_CREAT | O_TRUNC);
    myFile.write(&data, sizeof(Data));
    myFile.close();
}
