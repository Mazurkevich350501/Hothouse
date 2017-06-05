#include "ScreenManager.h"


// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];

UTFT myGLCD(CTE32HR,38,39,40,41);

void InitScreen();
//инициализация экрана
void ScreenManager::Init(){
    randomSeed(analogRead(1));
    myGLCD.InitLCD();
    InitScreen();
} 
//расчитывает позицию по вертикали пикселя по его значению
int GetYPosition(int value, int height){
    int span = (MAX_GRAPH_VALUE - MIN_GRAPH_VALUE);
    double result = value;
    result /= span;
    return result * height;
}
//Рисует точку на графике
void DrawPixel(int x, int y){
    int startX = 72,  startY = 250; // начало координат графика
    myGLCD.setColor(255,255,255);
    myGLCD.drawPixel(startX + x, startY - y);
}
//закрашивает пиксель в цвет сетки на графике (удаляет точку)
void RemovePixel(int x, int y){
    int startX = 72,  startY = 250;
    byte color = 0;
    if(!x % 30) color = 205;
    else if (!x % 10) color = 60;
    else if (!y % 50) color = 205;
    else if (!y % 25) color = 60;
    if(color == 0) myGLCD.setColor(0, 0, color);
    else myGLCD.setColor(60, 60, color);
    myGLCD.drawPixel(startX + x, startY - y);
}

void DrawLine(int xPos, int starY, int endY){
    if(starY > endY){
        starY += endY;
        endY = starY - endY;
        starY -= endY;
    }

    DrawPixel(xPos, starY);

    for (int i = starY + 1; i < endY; i+=1)
        DrawPixel(xPos, i);
}

void RemoveLine(int xPos, int starY, int endY){
    if(starY > endY){
        starY += endY;
        endY = starY - endY;
        starY -= endY;
    }

    RemovePixel(xPos, starY);

    for (int i = starY + 1; i < endY; i+=1)
        RemovePixel(xPos, i);
}

// Рисуем график
void ScreenManager::DrawGraph(CO2History &history){
    //размеры графика по ширине и высоте
    int xWidth = 360, yHeight = 200;
    //если в истории нету записей на всю ширину графика, то тогда ширина выбиается равной длине истории
    xWidth = xWidth > history.GetHistoryLength()
        ? history.GetHistoryLength()
        : xWidth;
    //Рисуем точку графика
    for(int i = 0; i < xWidth; i++){
        int yPos0 = GetYPosition(history.Read(i), yHeight);
        int yPos1 = GetYPosition(history.Read(i + 1), yHeight);
        int yPos2 = GetYPosition(history.Read(i + 2), yHeight);
        RemoveLine(i + 1, yPos1, yPos2); 
        DrawLine(i, yPos0, yPos1);
    }
}

//Рисует задний фон экрана
void InitScreen(){
    int xg, tg;
    int yg;
    int pH_g = MAX_GRAPH_VALUE, step = (MAX_GRAPH_VALUE - MIN_GRAPH_VALUE)/8;
    // Clear the screen and draw the frame
    myGLCD.clrScr();
    myGLCD.setFont(BigFont);
    // Сетка графика
    myGLCD.setColor(0,0,0);
    myGLCD.fillRect(32,50,479,250);
    // Горизонтальные линии
    tg=50;
    myGLCD.setFont(BigFont);
    for (yg=50; yg<=250; yg=yg+25)
    {
        myGLCD.setBackColor(0, 0, 0);
        if (yg==tg)
        {
            myGLCD.setColor(60, 60, 205);
            myGLCD.drawLine(72, yg, 478, yg);
            myGLCD.print(String(pH_g), 2, yg-4);
            tg=tg+50;
        }
        else
        {
            myGLCD.setColor(60, 60, 60);
            myGLCD.drawLine(72, yg, 478, yg);
            myGLCD.print(String(pH_g), 2, yg-4);
        }
        pH_g=pH_g-step;
    }
    // Вертикальные линии
    myGLCD.setFont(SmallFont);
    myGLCD.setBackColor(0, 0, 0);
    tg=0;
    for (xg=72; xg<=472; xg=xg+10)
    {
        if ((xg-72)==tg)
        {        
            myGLCD.setColor(60, 60, 255);
            myGLCD.drawLine(xg,50, xg, 254);
            myGLCD.print(String(tg), xg-8, 255);
            tg=tg+30;
        }
        else 
        {
            myGLCD.setColor(60, 60, 60);
            myGLCD.drawLine(xg,50, xg, 250);
        } 
    }

    myGLCD.setFont(BigFont);
    // Рисуем верхние большие квадраты
    myGLCD.setColor(25, 25, 255);
    myGLCD.setBackColor(25, 25, 255);
    myGLCD.fillRect(1, 2, 479, 44);
    myGLCD.setColor(255, 255, 0);
    myGLCD.print("Temp", 10, 2);
    myGLCD.print("Hum", 130, 2);
    myGLCD.print("Light", 250, 2);
    myGLCD.print("CO2", 370, 2); 

        // Рисуем нижние квадраты
    myGLCD.setColor(25, 25, 112);
    myGLCD.setBackColor(25, 25, 112);
    myGLCD.fillRect(1, 274, 240, 318);
    myGLCD.fillRect(242, 274, 479, 318);
    myGLCD.setColor(255, 255, 255);
    myGLCD.print("Strobe:", 5, 286);
    myGLCD.print("Delay:", 247, 286);
}
//Выводит значения датчиков и длительности свечения
void ScreenManager::Show(SensorValues sensorValues){
    myGLCD.setFont(BigFont);
        
    myGLCD.setColor(240, 255, 240);
    myGLCD.setBackColor(0, 128, 0);
    myGLCD.print(String(sensorValues.Temperature) + "c ", 8, 24);           //temp
    myGLCD.print(String(sensorValues.LightLevel)+ "   ", 248, 24);          //Ligth

    myGLCD.setBackColor(128, 0, 0);
    myGLCD.print(String(sensorValues.Humidity) + "% ", 128, 24);            //Hum
    myGLCD.print(String(sensorValues.CO2) + "   ", 368, 24);                //co2
    
    myGLCD.setBackColor(25, 25, 112);
    myGLCD.setColor(255, 255, 255);
    myGLCD.print(String(sensorValues.StrobeLength) + "ms ", 120, 286);      //strobe
    myGLCD.print(String(sensorValues.DelayLength) + "ms    ", 347, 286);    //delay
}
