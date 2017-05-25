#include <SPI.h>
#include <SD.h>

#define HISTORY_LENGTH 470
#define SD_CHIP_SELECT  53

class CO2History {
    public:
        CO2History();
        int Read(int index);
        void Update(int value);
    private:
        const char* fileName = "CO2History.bin";
        File myFile;
        int headIndex;
        int* data;
};