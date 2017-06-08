#include <UTFT.h>
#include "SensorValues.h"
#include "CO2History.h"

#define MAX_GRAPH_VALUE 3000 //максимальное значение ppm
#define MIN_GRAPH_VALUE 0 // минимально значение ppm

class ScreenManager{
    public:
        void Init(int updateDelay);		//инициализация экрана
        void Show(SensorValues sensorValues);	// отображенеи показаний датчиков
        void DrawGraph(CO2History &history);	//Отрисовка графика
};
