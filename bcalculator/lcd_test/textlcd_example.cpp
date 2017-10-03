#include "mbed.h"
#include "TextLCD.h"
TextLCD lcd(PB_6, PC_7, PA_9, PA_8, PB_10, PB_4); // RS, E, D4-D7
 
DigitalOut rw(PA_9); // RW
 
int main() {
     
    lcd.cls(); wait(2);
     
    lcd.locate(0,0); 
    lcd.printf("I think it works?");
     
    while(1); 
}