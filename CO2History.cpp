#include "CO2History.h"

MQ135 sensor(0);

//с картой 
/*
CO2History::CO2History(){
    withSd = true;
    //инициализация сд карты
    if (!sd.begin(SD_CHIP_SELECT, SPI_FULL_SPEED)) {
        sd.initErrorHalt();
        return;
    }
    // чтение данных из файла
    if(sd.exists(FILE_NAME)){  
        myFile = sd.open(FILE_NAME);
        myFile.read(&data, sizeof(Data)); 
        myFile.close();
    }
    else{
        //если файла нет, то инициализируем нулями
        data.headIndex = 0;
        for(int i = 0; i < HISTORY_LENGTH; i++)
            data.values[i] = 0;
    }
}
*/

CO2History::CO2History(){
    //если файла нет, то инициализируем нулями
    data.headIndex = 0;
    for(int i = 0; i < HISTORY_LENGTH; i++)
        data.values[i] = 0;
}



//извлекает значение из кольца
/*
    индекс равный рулю = голова кольца
    остальные элементы = голова кольца + индекс
    если выход за пределы массива = голова кольца + индекс - длина массива
*/
int CO2History::Read(int index){
    if(index > HISTORY_LENGTH) return 0;
    return (index + data.headIndex) >= HISTORY_LENGTH
        ? data.values[(index + data.headIndex) - HISTORY_LENGTH]
        : data.values[index + data.headIndex];
}
//чтение и сохранение данных о co2
void CO2History::Update(){
    data.headIndex = data.headIndex > 0
        ? data.headIndex - 1
        : HISTORY_LENGTH;
    data.values[data.headIndex] = sensor.getPPM();
    if(withSd) save();
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
