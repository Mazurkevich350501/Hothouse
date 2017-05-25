#include "CO2History.h"

CO2History::CO2History(){
    if (!SD.begin(SD_CHIP_SELECT)) return;
    myFile = SD.open(fileName, FILE_WRITE);
    if (myFile) {
        data = new int[HISTORY_LENGTH];
        while (myFile.available()) {
            Serial.write(myFile.read());
        }
        myFile.close();
    }
    myFile = SD.open(fileName);
    if (myFile) {
    
        while (myFile.available()) {
            Serial.write(myFile.read());
        }
        myFile.close();
    }
}

int CO2History::Read(int index){
    if(data == NULL) return 0;
    if(index > HISTORY_LENGTH || index < 0) return 0;
    return (index + headIndex) > HISTORY_LENGTH
        ? data[HISTORY_LENGTH - (index + headIndex)]
        : data[index + headIndex];
}

void CO2History::Update(int value){
    if(data == NULL) return;
    headIndex = headIndex > 0
        ? headIndex - 1
        : HISTORY_LENGTH;
    data[headIndex] = value;
}