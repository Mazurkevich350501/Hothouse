#include "CO2History.h"

MQ135 sensor(0);

CO2History::CO2History(){
  data.headIndex = 0;
  for(int i = 0; i < HISTORY_LENGTH; i++)
      data.values[i] = 0;
}

int CO2History::GetCurrentValue(){
    return sensor.getPPM();
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
void CO2History::Update(float t, float h){
    data.headIndex = data.headIndex > 0
        ? data.headIndex - 1
        : HISTORY_LENGTH;
    data.values[data.headIndex] = sensor.getCorrectedPPM(t, h);
}

int CO2History::GetHistoryLength(){
    return HISTORY_LENGTH;
}

int CO2History::GetLastValue(){
    return Read(0);
}

void CO2History::SetVal(Co2Value data){
    this->data = data;  
}

Co2Value CO2History::GetVal(){
    return data;
}

