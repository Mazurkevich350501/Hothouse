#include "ScreenManager.h"

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];

UTFT myGLCD(CTE32HR,38,39,40,41);

void InitScreen();

ScreenManager::ScreenManager(){
    randomSeed(analogRead(0));
    // Setup the LCD
    myGLCD.InitLCD();
    InitScreen();
} 

void DrawGraph(){
    // Рисуем график
    int x=72;
    int buf_pH_ai_sec[407], buf_pH_sp_sec[407];
    int buf_pH_ai_min[407], buf_pH_sp_min[407];
    int buf_pH_ai_hour[407], buf_pH_sp_hour[407];
    int xg, tg;
    int y, y2, yg;
    int r, lvl_ai=100, lvl_sp=100;
    float pH_ai=14.00, pH_sp=6.40, TDS_ai=2.00, TDS_sp=2.00, pH_g;
    boolean b1;
    for (int i=1; i<(478*15); i++) 
    {
        if (x==480)
        {
            x=72;
        }
        for (int x2=0; x2<=407; x2++)
        {
            buf_pH_ai_sec[(407-x2)]=buf_pH_ai_sec[(406-x2)];
            buf_pH_sp_sec[(407-x2)]=buf_pH_sp_sec[(406-x2)];
        }
        buf_pH_ai_sec[1]=159+(sin(((i*0.7)*3.14)/180)*(90-(i / 100)));
        buf_pH_sp_sec[1]=250-int((pH_sp-4.0)*50);
        for (int x3=0; x3<=405; x3++)
        {
            if ((buf_pH_ai_sec[x3]>0)&&(buf_pH_sp_sec[x3]>0))
            {
                y=constrain(buf_pH_ai_sec[x3],50,250);
                y2=constrain(buf_pH_sp_sec[x3],50,250);
                myGLCD.setColor(0,255,255);
                if ((y>=50)&&(y<+250)) myGLCD.drawPixel(x3+72,y);
                myGLCD.setColor(255,0,0);
                if ((y2>=50)&&(y2<+250)) myGLCD.drawPixel(x3+72,y2);
                if (buf_pH_ai_sec[x3] != buf_pH_ai_sec[x3+1])
                {
                    if ((x3==0)||(x3==30)||(x3==60)||(x3==90)||(x3==120)||(x3==150)||(x3==180)||(x3==210)||(x3==240)||(x3==270)||(x3==300)||(x3==330)||(x3==360)||(x3==390))
                    {
                        myGLCD.setColor(0,0,205);
                    }
                    else if ((buf_pH_ai_sec[x3+1]==50)||(buf_pH_ai_sec[x3+1]==150)||(buf_pH_ai_sec[x3+1]==250)||(buf_pH_ai_sec[x3+1]==100)||(buf_pH_ai_sec[x3+1]==200))
                    {
                        myGLCD.setColor(0,0,205);
                    }
                    else if ((x3==10)||(x3==20)||(x3==40)||(x3==50)||(x3==70)||(x3==80)||(x3==100)||(x3==110)||(x3==130)||(x3==140)||(x3==160)||(x3==170)||(x3==190))
                    {
                        myGLCD.setColor(0,0,60);
                    }
                    else if ((x3==200)||(x3==220)||(x3==230)||(x3==250)||(x3==70)||(x3==260)||(x3==280)||(x3==290)||(x3==310)||(x3==320)||(x3==340)||(x3==350)||(x3==370)||(x3==380))
                    {
                        myGLCD.setColor(0,0,60);
                    }
                    else if ((buf_pH_ai_sec[x3+1]==75)||(buf_pH_ai_sec[x3+1]==125)||(buf_pH_ai_sec[x3+1]==175)||(buf_pH_ai_sec[x3+1]==225))
                    {
                        myGLCD.setColor(0, 0, 60);
                    }
                    else myGLCD.setColor(0,0,0);
                    if ((buf_pH_ai_sec[x3+1]>=50)&&(buf_pH_ai_sec[x3+1]<+250)) myGLCD.drawPixel(x3+72,buf_pH_ai_sec[x3+1]);
                }
            }
        }
    x++;
  }
}

void InitScreen()
{
    int x, xg, tg;
    int y, y2, yg;
    int r, lvl_ai=100, lvl_sp=100;
    float pH_ai=14.00, pH_sp=6.40, TDS_ai=2.00, TDS_sp=2.00, pH_g;
    boolean b1;
    unsigned long time;
    time = millis();
    // Clear the screen and draw the frame
    myGLCD.clrScr();

    myGLCD.setFont(BigFont);
    // Сетка графика
    myGLCD.setColor(0,0,0);
    myGLCD.fillRect(32,50,479,250);
    // Горизонтальные линии
    tg=50;
    pH_g=8.0;
    myGLCD.setFont(BigFont);
    for (yg=50; yg<=250; yg=yg+25)
    {
        myGLCD.setBackColor(0, 0, 0);
        if (yg==tg)
        {
            myGLCD.setColor(0, 0, 205);
            myGLCD.drawLine(72, yg, 478, yg);
            myGLCD.print(String(pH_g), 2, yg-4);
            tg=tg+50;
        }
        else
        {
            myGLCD.setColor(0, 0, 60);
            myGLCD.drawLine(72, yg, 478, yg);
            myGLCD.print(String(pH_g), 2, yg-4);
        }
        pH_g=pH_g-0.5;
    }
    // Вертикальные линии
    myGLCD.setFont(SmallFont);
    myGLCD.setBackColor(0, 0, 0);
    tg=0;
    for (xg=72; xg<=472; xg=xg+10)
    {
        if ((xg-72)==tg)
        {        
            myGLCD.setColor(0, 0, 255);
            myGLCD.drawLine(xg,50, xg, 254);
            myGLCD.print(String(tg), xg-8, 255);
            tg=tg+30;
        }
        else 
        {
            myGLCD.setColor(0, 0, 60);
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

void ScreenManager::Show(SensorValues sensorValues){
    myGLCD.setFont(BigFont);
        
    // Рисуем квадраты под показания
    myGLCD.setColor(0, 128, 0);
    myGLCD.fillRect(5, 20, 120, 42);
    myGLCD.setColor(240, 255, 240);
    myGLCD.setBackColor(0, 128, 0);
    myGLCD.print(String(sensorValues.Temperature) + "c", 8, 24);

    myGLCD.setColor(128, 0, 0);
    myGLCD.fillRect(125, 20, 240, 42);
    myGLCD.setColor(240, 255, 240);
    myGLCD.setBackColor(128, 0, 0);
    myGLCD.print(String(sensorValues.Humidity) + "%", 128, 24);
    
    // Рисуем квадраты под показания
    myGLCD.setColor(0, 128, 0);
    myGLCD.fillRect(245, 20, 350, 42);
    myGLCD.setColor(240, 255, 240);
    myGLCD.setBackColor(0, 128, 0);
    myGLCD.print(String(sensorValues.LightLevel), 248, 24);

    myGLCD.setColor(128, 0, 0);
    myGLCD.fillRect(355, 20, 470, 42);
    myGLCD.setColor(240, 255, 240);
    myGLCD.setBackColor(128, 0, 0);
    myGLCD.print(String(sensorValues.CO2), 368, 24);

    myGLCD.setBackColor(25, 25, 112);
    myGLCD.setColor(255, 255, 255);
    myGLCD.print(String(sensorValues.StrobeLength) + "ms", 120, 286);
    myGLCD.print(String(sensorValues.DelayLength) + "ms", 347, 286);
}

