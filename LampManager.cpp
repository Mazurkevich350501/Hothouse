#include "LampManager.h"

int strobeLength;
int delayLength;
bool isOn;
//обработчик прерывания(увеличивает время горения лампы)
void upStrobeLength(){
    if(strobeLength < MAX_VALUE) strobeLength += STEP;
}
//обработчик прерывания(уменьшает время горения лампы)
void downStrobeLength(){
    if(strobeLength > MIN_VALUE) strobeLength -= STEP;
}
//обработчик прерывания(увеличивает время не горения лампы)
void upDelayLength(){
    if(delayLength < MAX_VALUE) delayLength += STEP;
}
//обработчик прерывания(уменьшает время не горения лампы)
void downDelayLength(){
    if(delayLength > MIN_VALUE) delayLength -= STEP;
}
//обработчик прерывания таймера (меняте состояние лампы)
void changeLampState(){
    if(strobeLength == 0 || delayLength == 0){  //случай когда период равен 0, что не допустимо для счетчиков
        isOn = delayLength == 0;                //полностью включает или выключает лампу.
        double a = STEP;
        Timer3.setPeriod(a*1000);
    }
    else{
        isOn = isOn ? false : true;
        Timer3.setPeriod(((double)(isOn ? strobeLength : delayLength))*1000); //задается время до следующего срабатывания счетчика
    }
    digitalWrite(LAMP_PIN, isOn ? HIGH : LOW);
}
//конструктор
LampManager::LampManager(){
    int value = 1000;//((int)(MAX_VALUE/(2*STEP)))*STEP;   //среднее разперенное значение
    strobeLength = value;                           //время горения
    delayLength = value;                            //время не горения
   // attachInterrupt(0, downDelayLength, RISING);    //прерывания на кнопки.
   // attachInterrupt(1, upDelayLength, RISING);      //запускают обработчики прерываний, когда происходит нажатие на кнопку
   // attachInterrupt(4, downStrobeLength, RISING);
   // attachInterrupt(5, upStrobeLength, RISING);
}
//инициализация счетчика. (должен инициализироваться из сетапа)
void LampManager::Init(){
    isOn = true;
    pinMode(LAMP_PIN, OUTPUT);
    digitalWrite(LAMP_PIN, HIGH);
    //Timer3.initialize(strobeLength);            //инициализация с длительностью равной длительности горения
    //Timer3.attachInterrupt(changeLampState);    //объявляем обработчик рерывания таймера
}

int LampManager::GetStrobeLength(){
    return strobeLength;
}

int LampManager::GetDelayLength(){
    return delayLength;
}
