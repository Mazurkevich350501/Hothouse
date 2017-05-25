#include <SdFat.h>

#define HISTORY_LENGTH 470
#define SD_CHIP_SELECT  53
#define FILE_NAME "CO2History.bin"



class CO2History {
    public:
        CO2History();
        int Read(int index);
        void Update(int value);
    private:
        void save();
        SdFat sd;
        File myFile;
        struct Data{
            int headIndex;
            int values[HISTORY_LENGTH];
        } data;

};
