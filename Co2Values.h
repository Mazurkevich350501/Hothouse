#ifndef CO2Val
#define CO2Val


#define HISTORY_LENGTH 470  //количество хранимых значений

struct Co2Value{                    //структура, которая записывается в файл
    int headIndex;              //голова кольца
    int values[HISTORY_LENGTH]; //массив значений
};

#endif
