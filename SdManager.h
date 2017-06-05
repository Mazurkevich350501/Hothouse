#include <SdFat.h>
#include "Co2Values.h"
#include "SensorValues.h"

#define SD_CHIP_SELECT  53  //порт для карты пямяти
#define CO2_FILE "CO2History.bin" //имя файла где хранятся значения
#define LOG_FILE "Log.txt"
#


class SDManager {
    public:
        SDManager(bool withSd, int logUpdateTime);
        void WriteCo2Value(Co2Value val);
        Co2Value ReadCo2Value();
        void WriteToLog(SensorValues val);
    private:
        bool withSd = false;
        double i = 0;
        float logUpdateTime;
        SdFat sd;                       //класс, который пишет и читает с флешки
        File file;                    //файл который используется для хранения данных                    
        /*
            Здесь типа реализовано кольцо для хранения данных с минимальными перезаписями.
            Суть такова что пишутся значения по кругу в массив. 
            то есть занчения пишутся сначала 0,470,469,468, .... 3,2,1,0.
            При этом при записи нового значения это значение становится головой кольца.
            то есть если я записал значение по индексу 222, то голова в 222.
            и читаться данные будут 222 223 224 ....
            а снаружи класса голова всегда имеет индекс 0
            таким образом если я хочу получить голову я напишу Read(0) и получу значение в ячейке 222
            если Read(100) -> 322, Read(300) -> (222 + 300) - 470"HISTORY_LENGTH" = 82
        */
};
