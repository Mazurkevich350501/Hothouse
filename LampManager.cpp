#include "LampManager.h"

int strobeLength;
int delayLength;

void upStrobeLength(){
    if(strobeLength < MAX_VALUE) strobeLength += STAP;
}

void downStrobeLength(){
    if(strobeLength > MIN_VALUE) strobeLength -= STAP;
}
void upDelayLength(){
    if(delayLength < MAX_VALUE) delayLength += STAP;
}

void downDelayLength(){
    if(delayLength > MIN_VALUE) delayLength -= STAP;
}

LampManager::LampManager(){
    int value = ((int)(MAX_VALUE/(2*STAP)))*STAP;
    strobeLength = value;
    delayLength = value;
    attachInterrupt(0, downDelayLength, RISING);
    attachInterrupt(1, upDelayLength, RISING);
    attachInterrupt(4, downStrobeLength, RISING);
    attachInterrupt(5, upStrobeLength, RISING);
}

short int LampManager::GetStrobeLength(){
    return strobeLength;
}

short int LampManager::GetDelayLength(){
    return delayLength;
}
