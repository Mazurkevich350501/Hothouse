#include <UTFT.h>
#include "SensorValues.h"

class ScreenManager{
    public:
        void Init();
        void Show(SensorValues sensorValues);
};
