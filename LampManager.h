#include <avr/io.h>
#include <avr/interrupt.h>
#include <arduino.h>
#include <TimerThree.h>

#define LAMP_PIN 6			//пин управления лампой
#define RISING 3			//флаг того, что прерывание будет срабатывать по фронту (_Г)
#define MAX_VALUE 30000		//максимальное значение длительности горения и не горения 
#define MIN_VALUE 0			//мин значение
#define STEP 100			//шаг изменения значений

class LampManager{
    public:
        LampManager();			
        void Init();
        int GetStrobeLength();
        int GetDelayLength();       
};

/*
	используется счетчик3 для контроля за временем горения лампы
*/