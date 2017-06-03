#ifndef SensorVal
#define SensorVal


//структура, которая хранит данные с датчиков для отображения на экране 
struct SensorValues{
    float Temperature;
    float Humidity;
    int StrobeLength;
    int DelayLength;
    int LightLevel;
    int CO2;
};

#endif
