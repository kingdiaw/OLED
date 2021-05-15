#include "picuno.h"
#include "OLED.h"         
#include "font.h"
#include "Wire.h"

//void DisplayData(void);
char buf[32];

void setup(){
    Serial_begin(9600);  
    Wire_begin(100000);
    Oled_init();
    Oled_clear(); 
    Serial_println("\nTESTING OLED");
}
void loop(){

    if(timerUp(0)){
        timerSet(0,1000);
        Oled_selectPage(0); //page 1 Select page/line 0-7
        Oled_writeString("Hello World");
        Oled_selectPage(1);
        Oled_writeString("Line 2");
        Oled_selectPage(2);
        Oled_writeString("Line 3");
        Oled_selectPage(3);
        Oled_writeString("0123456789ABCDEF");
              
    }  
}
