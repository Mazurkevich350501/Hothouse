#include <UTFT.h>
#include "SensorValues.h"
#include "CO2History.h"

#define MAX_GRAPH_VALUE 5000
#define MIN_GRAPH_VALUE 0

class ScreenManager{
    public:
        void Init();
        void Show(SensorValues sensorValues);
        void DrawGraph(CO2History &history);
};
