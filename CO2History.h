#include <SdFat.h>
#include "customMQ135.h"

#define HISTORY_LENGTH 470  //количество хранимых значений
#define SD_CHIP_SELECT  53  //порт для карты пямяти
#define FILE_NAME "CO2History.bin" //имя файла где хранятся значения
#define SENSOR_PIN 0    //пин датчика MQ135

//класс содержит в себе историю о значениях CO2
class CO2History {
    public:
        CO2History();                   //конструктор
        int Read(int index);            //читает из истории значение с индексом index, если index=10, то вернется занчение измеренное 10 раз назад
        void Update();                  //считывает показание и сохраняет его на карту памяти
        int GetHistoryLength();         //возвращает длину истории
        int GetLastValue();             //возвращает последнее измеренное значение (тоже самое что Read(0) )
    private:
        bool withSd = false;
        void save();                    //запись истории в файл
        SdFat sd;                       //класс, который пишет и читает с флешки
        File myFile;                    //файл который используется для хранения данных
        struct Data{                    //структура, которая записывается в файл
            int headIndex;              //голова кольца
            int values[HISTORY_LENGTH]; //массив значений
        } data;
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
