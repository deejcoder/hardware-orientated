/*
	Student ID: 16058989
	Dylan Tonks
	Hardware Oriented Computing, 159.270
	Assignment #3
*/


#include "mbed.h"



/*
 _____        __ _       _ _   _                 
|  __ \      / _(_)     (_) | (_)                
| |  | | ___| |_ _ _ __  _| |_ _  ___  _ __  ___ 
| |  | |/ _ \  _| | '_ \| | __| |/ _ \| '_ \/ __|
| |__| |  __/ | | | | | | | |_| | (_) | | | \__ \
|_____/ \___|_| |_|_| |_|_|\__|_|\___/|_| |_|___/
                                                 
	* Preprocessing constants
	* Function Prototypes
	* Enumerators
*/

#define LCD_DATA 1
#define LCD_INSTRUCTION 0

//What number to count upto?
#define MAX_COUNT		15
#define	MAX_COUNT_BITS	4 	//max# of bits





/*
	Function Prototypes
	=> LCD
*/

//Setup
void lcdinit();
static void lcdInit8Bit(unsigned char command); 

//Controlling data
void sendCommand(unsigned char command); 	//:= send a command to the lcd
void sendChar(unsigned char c);				//:= send a character to the lcd screen
void sendString(char *s);					//:= send a string of characters to the lcd screen
void cls();									//:= clear the LCD screen, set cursor @ (0,0)
static void lcdSetRS(int mode);				//:= switch between LCD_INSTRUCTION & LCD_DATA
static void lcdPulseEN(void);				//:= send a pulse signal to the lcd




/*
	Function Prototypes
	=> Counting, Modes & Conversions
*/
void Task_UpdateMode(void); 				//Task : updates the mode every 2 seconds
void BeginCounting(); 				//Initiates counting mode
void NextMode(); 							//Moves onto the next mode
int GetCurrentMode(); 						//Returns the current mode

void ShowDecimal(int num);
void ShowHexFromDecimal(int num);
void ShowBinaryFromDecimal(int num);



//Modes to count in
enum e_modes {HEX, BINARY, DECIMAL};


//Global variables

static int g_currentMode;					//static, stores current mode -> use functions to access this
Timer timer_UpdateMode;						//The timer moves onto the next mode every 2s

/*
	Pins IN/OUT & Buses
*/
//LCD
BusOut lcdData(PA_9, PA_8, PB_10, PB_4);
DigitalOut _en(PC_7), _rs(PB_6);

//BUTTON
DigitalIn _button(USER_BUTTON);




/*
  _____                 ______                    
 / ____|               |  ____|                   
| |     ___  _ __ ___  | |__ _   _ _ __   ___ ___ 
| |    / _ \| '__/ _ \ |  __| | | | '_ \ / __/ __|
| |___| (_) | | |  __/ | |  | |_| | | | | (__\__ \
 \_____\___/|_|  \___| |_|   \__,_|_| |_|\___|___/
                                                  
	* int main() ->>> Entry point
	* void Task_UpdateMode() updates the mode
	*	-> void NextMode() moves to the next mode of DEC, HEX, Binary
	* void GetCurrentMode() returns the current mode
	* void BeginCounting() begins the counting!
*/

int main()
{
	lcdinit();
	Task_UpdateMode(); //set the first mode
	timer_UpdateMode.start();
	
	while(true) {
		
		//Has the user hit the button? No?
		if(_button) {
			//Time for the timer?
			if(timer_UpdateMode.read() > 2) {
				Task_UpdateMode();
				timer_UpdateMode.reset();
				
			}
		}
		//If yes, begin counting
		else {
			//assure the user releases the button
			while(!_button); 
			BeginCounting();
		}
	}
}

	
	
void Task_UpdateMode(void) {
	
	//increment the mode
	NextMode();
	
	//display the current mode on the screen
	cls();
	switch(GetCurrentMode()) {
		case HEX: sendString((char*)"HEXADECIMAL"); break;
		case BINARY: sendString((char*)"BINARY"); break;
		case DECIMAL: sendString((char *)"DECIMAL"); break;
		
	}
}

//Counts up everytime the user button is pressed.
void BeginCounting() {
	
	int count = 0;
	
	while(count <= MAX_COUNT) {
		//Final count before exit
		if(count > MAX_COUNT) {
			wait(1);
			NextMode(); //move onto the next mode
			break;
		}
		
		//Clear screen & show in the right mode
		cls();
		switch(GetCurrentMode()) {
			case HEX: ShowHexFromDecimal(count); break;
			case BINARY: ShowBinaryFromDecimal(count); break;
			case DECIMAL: ShowDecimal(count); break;
		}
		
		//Wait for a button push: press & release
		while(_button.read());
		while(!_button.read());
		count++;
	}
}

//Moves to the next mode.
void NextMode() {
	g_currentMode++;
	if(g_currentMode > (int)DECIMAL) {
		g_currentMode = (int)HEX;
	}
}

//Returns the current mode
int GetCurrentMode() {
	return g_currentMode;
}



/*
  _____                              _                 
 / ____|                            (_)                
| |     ___  _ ____   _____ _ __ ___ _  ___  _ __  ___ 
| |    / _ \| '_ \ \ / / _ \ '__/ __| |/ _ \| '_ \/ __|
| |___| (_) | | | \ V /  __/ |  \__ \ | (_) | | | \__ \
 \_____\___/|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|___/

	* The number counting up, is converted into it's
		suitable form before being printed onto the LCD.
		
	* MODES: HEX, Binary, Decimal
                                                       
*/
void ShowHexFromDecimal(int num) {
	//int slots = num / MAX_COUNT + ( ((num + (num % MAX_COUNT)) / MAX_COUNT)); // - if I were to do numbers over 15
	//Throw the number as a hex, into a string, s
	char s[1];
	sprintf(s, "%1x", num);
	
	//since we're only dealing with numbers upto 15 = F
	sendChar(s[0]);
}

void ShowBinaryFromDecimal(int num) {
	
	for(int i = 0; i < MAX_COUNT_BITS; i++) {
		
		//shifting right MAX_COUNT_BITS-1 times to determine if bit = 1 || 0
		if(num & (1 << ((MAX_COUNT_BITS-1)-i))) { 
			sendChar('1');
		}
		else {
			sendChar('0');
		}
	}
}

void ShowDecimal(int num) {
	//Convert a number to a string
	char s[3]; 
	sprintf(s, "%d", num);
	sendString(s);
}




/*
 _      _____ _____    ______                    
| |    / ____|  __ \  |  ____|                   
| |   | |    | |  | | | |__ _   _ _ __   ___ ___ 
| |   | |    | |  | | |  __| | | | '_ \ / __/ __|
| |___| |____| |__| | | |  | |_| | | | | (__\__ \
|______\_____|_____/  |_|   \__,_|_| |_|\___|___/
                                                 

*/


//Clears the LCD screen, sets cursor to (0,0)
void cls() {
	sendCommand(0x01);
	wait_ms(2); //1.64ms execution
}

void sendString(char *s) {
	
	while(*s != '\0') {
		sendChar(*s);
		s++;
	}
}

void lcdinit() {
	_en.write(0); //-- GPIO_WriteBit(GPIOC, LCD_EN, Bit_RESET);
	wait_us(15000); //-- delay for >15msec second after power on
	lcdInit8Bit(0x30); //-- we are in "8bit" mode
	wait_us(4100); //-- 4.1msec delay
	lcdInit8Bit(0x30); //-- but the bottom 4 bits are ignored
	wait_us(100); //-- 100usec delay
	lcdInit8Bit(0x30);
	lcdInit8Bit(0x20);
	sendCommand(0x28); //-- we are now in 4bit mode, dual line
	sendCommand(0x08); //-- display off
	sendCommand(0x01); //-- display clear
	wait_us(2000); //-- needs a 2msec delay !!
	sendCommand(0x06); //-- cursor increments
	sendCommand(0x0f); //-- display on, cursor(blinks) on
}

static void lcdSetRS(int mode)
{
	_rs.write(mode);
}
static void lcdPulseEN(void)
{
	_en.write(1);
	wait_us(1); //-- enable pulse must be >450ns
	_en.write(0);
	wait_us(1);
}


static void lcdInit8Bit(unsigned char command)
{
	lcdSetRS(LCD_INSTRUCTION);
	lcdData.write(command>>4); //-- bottom 4 bits
	lcdPulseEN();
	wait_us(37); //-- let it work on the data
}
void sendCommand(unsigned char command)
{
	lcdSetRS(LCD_INSTRUCTION);
	lcdData.write(command>>4);
	lcdPulseEN(); //-- this can't be too slow or it will time out
	lcdData.write(command & 0x0f);
	lcdPulseEN();
	wait_us(37); //-- let it work on the data
}
void sendChar(unsigned char c)
{
	lcdSetRS(LCD_DATA);
	lcdData.write(c>>4);
	lcdPulseEN(); //-- this can't be too slow or it will time out
	lcdData.write(c & 0x0f);
	lcdPulseEN();
	wait_us(37); //-- let it work on the data
}
