#include <avr/io.h>
#include <avr/interrupt.h>
#include <arduino.h>

#define LAMP_PIN 6
#define RISING 3
#define MAX_VALUE 1000
#define MIN_VALUE 0
#define STAP 100

class LampManager{
    public:
        LampManager();
        short int GetStrobeLength();
        short int GetDelayLength();       
};
