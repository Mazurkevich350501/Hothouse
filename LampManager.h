#include <avr/io.h>
#include <avr/interrupt.h>
#include <arduino.h>
#include <TimerThree.h>

#define LAMP_PIN 6
#define RISING 3
#define MAX_VALUE 50000
#define MIN_VALUE 0
#define STEP 1000

class LampManager{
    public:
        LampManager();
        void Init();
        int GetStrobeLength();
        int GetDelayLength();       
};

