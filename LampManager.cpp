#include "LampManager.h"
#include "Arduino.h"
#include "HardwareSerial.h"



int strobeLength;
int delayLength;
bool isOn;

void upStrobeLength(){
    if(strobeLength < MAX_VALUE) strobeLength += STEP;
}

void downStrobeLength(){
    if(strobeLength > MIN_VALUE) strobeLength -= STEP;
}
void upDelayLength(){
    if(delayLength < MAX_VALUE) delayLength += STEP;
}

void downDelayLength(){
    if(delayLength > MIN_VALUE) delayLength -= STEP;
}

void changeLampState(){
    if(strobeLength == 0 || delayLength == 0){
        isOn = delayLength == 0;
        Timer3.setPeriod(STEP);
    }
    else{
        isOn = isOn ? false : true;
        Timer3.setPeriod((isOn ? strobeLength : delayLength));
    }
    digitalWrite(LAMP_PIN, isOn ? HIGH : LOW);
}

LampManager::LampManager(){
    int value = ((int)(MAX_VALUE/(2*STEP)))*STEP;
    strobeLength = value;
    delayLength = value;
    attachInterrupt(0, downDelayLength, RISING);
    attachInterrupt(1, upDelayLength, RISING);
    attachInterrupt(4, downStrobeLength, RISING);
    attachInterrupt(5, upStrobeLength, RISING);
}

void LampManager::Init(){
    isOn = true;
    pinMode(LAMP_PIN, OUTPUT);
    digitalWrite(LAMP_PIN, HIGH);
    Timer3.initialize(strobeLength);
    Timer3.attachInterrupt(changeLampState);
}

int LampManager::GetStrobeLength(){
    return strobeLength;
}

int LampManager::GetDelayLength(){
    return delayLength;
}
