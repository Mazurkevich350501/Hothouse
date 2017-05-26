#include <SdFat.h>

#define HISTORY_LENGTH 470
#define SD_CHIP_SELECT  53
#define FILE_NAME "CO2History.bin"
#define SENSOR_PIN 0


class CO2History {
    public:
        CO2History();
        int Read(int index);
        void Update();
        int GetHistoryLength();
        int GetLastValue();
    private:
        void save();
        int getPpmValue();
        int convertToPpm(float Vout);
        SdFat sd;
        File myFile;
        struct Data{
            int headIndex;
            int values[HISTORY_LENGTH];
        } data;

};
