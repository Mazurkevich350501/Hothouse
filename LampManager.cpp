#include "LampManager.h"

int strobeLength;
int delayLength;

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

LampManager::LampManager(){
    int value = ((int)(MAX_VALUE/(2*STEP)))*STEP;
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
