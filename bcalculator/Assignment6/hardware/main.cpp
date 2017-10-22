#include "mbed.h"
#include "uart.h"
#include "stepper.h"


//Pin definitions
DigitalIn button(PC_13);
Uart uart(USBTX, USBRX);

DigitalOut greenLED(PA_5);
DigitalOut blueLED(PA_7);


int main()
{
	Stepper sm(PC_0, PC_1, PC_2, PC_3, 5);
	
	
    while (1) {
		
        char string[10];
        if (uart.canReadLine()) {
            uart.readLine(string);
            string[strlen(string)-1] = '\0';
			//Get a string from the Serial & output arguments
			
			char cmd; int value;
			sscanf(string, "%c %d", &cmd, &value);
            
            
			//Match up the commands
			switch(cmd)
			{
				case 's':
				case 'S': {
					sm.ToggleStepperMotor();
					break;
				}
				case 't':
				case 'T': {
					sm.ToggleStepperDirection();
					break;              
				}
				case 'd':
				case 'D': {
					if (value > 0)
					{
						sm.SetStepperDelay(value);
					}
					break;
				}
				case 'g':
				case 'G': {
					if(greenLED) {
						greenLED.write(0);
					}
					else {
						greenLED.write(1);
					}
					break;
				}
				case 'b':
				case 'B': {
					if(blueLED) {
						blueLED.write(0);
					}
					else {
						blueLED.write(1);
					}
				}
			}
				
				
        }
    }
}
