#include "mbed.h"

#include <iostream>
using namespace std;

/*
 _____        __ _       _ _   _                 
|  __ \      / _(_)     (_) | (_)                
| |  | | ___| |_ _ _ __  _| |_ _  ___  _ __  ___ 
| |  | |/ _ \  _| | '_ \| | __| |/ _ \| '_ \/ __|
| |__| |  __/ | | | | | | | |_| | (_) | | | \__ \
|_____/ \___|_| |_|_| |_|_|\__|_|\___/|_| |_|___/
                                                 
	=> Pins
	=> Motor direction constants
	=> Stepper class header
                                                 
*/

DigitalIn button(PC_13);
Serial uart(PC_12, PD_2);

#define DIR_CLOCKWISE		1
#define DIR_ANTI_CLOCKWISE	3

class Stepper
{
private:
	
	//All pins for motor => bus
	BusOut bus;
	
	bool state = false;
	int direction;
	int cur_magnet;
	int delay;
	
	int tickcount = 0;
	Ticker ticker;
	
	//Only want the class accessing this
	void tick(void);

public:
	
	//Constructor/Destructor
	Stepper(PinName p1, PinName p2, PinName p3, PinName p4, int delay);
	~Stepper();
	
	//Getters
	bool GetStepperState();
	int GetTickCount();
	int GetStepperDirection();
	int GetStepperDelay();
	
	//Setters
	int SetStepperDelay(int delay);
	int SetStepperDirection(int dir);
	
	//Toggles
	bool ToggleStepperMotor();
	int ToggleStepperDirection();
	
};

/*
  _____ _                               ______                    
 / ____| |                             |  ____|                   
| (___ | |_ ___ _ __  _ __   ___ _ __  | |__ _   _ _ __   ___ ___ 
 \___ \| __/ _ \ '_ \| '_ \ / _ \ '__| |  __| | | | '_ \ / __/ __|
 ____) | ||  __/ |_) | |_) |  __/ |    | |  | |_| | | | | (__\__ \
|_____/ \__\___| .__/| .__/ \___|_|    |_|   \__,_|_| |_|\___|___/
               | |   | |                                          
               |_|   |_|                                          
               
	=> Constructor: Stepper(pin1, pin2, pin3, pin4, initial delay)
	=> Destructor: ~Stepper()

*/


/**	Initialize the bus, set the initial delay and direction. Turn it on.
 */
Stepper::Stepper(PinName p1, PinName p2, PinName p3, PinName p4, int delay)
	: bus(p1, p2, p3, p4)
{

	SetStepperDelay(delay);
	SetStepperDirection(DIR_ANTI_CLOCKWISE);
	ToggleStepperMotor();  //initially turn it on
	
}

/**	Stop the motor if it is going before destroying the object
 */
Stepper::~Stepper()
{
	//If it is on, turn it off.
	if(GetStepperState()) {
		ToggleStepperMotor();
	}
}

/*	Performed every this->delay milliseconds, makes the motor go in this->direction
 */
void Stepper::tick(void)
{
	int dir = GetStepperDirection();
	int delay = GetStepperDelay();
	
	//Output to the next magnet
	this->bus = (1 << this->cur_magnet);
	
	//Increase or decrease current magnet based on direction
	this->cur_magnet = (this->cur_magnet + dir) % 4;
	this->tickcount++;
	
}


//Getters
bool Stepper::GetStepperState()		{ return this->state; }
int Stepper::GetTickCount()			{ return this->tickcount; }
int Stepper::GetStepperDelay()		{ return this->delay; }
int Stepper::GetStepperDirection()	{ return this->direction; }

//Setters ...

/** Since the motor is already going, the Ticker has a defined delay,
 ** for which setting a new delay requires it to be restarted
*/
int Stepper::SetStepperDelay(int delay)
{
	this->delay = delay;
	if (GetStepperState()) //restart the motor if it's on
	{
		ToggleStepperMotor();
		ToggleStepperMotor();
	}
	return delay;
}



int Stepper::SetStepperDirection(int dir)
{
	this->direction = dir;
	return dir;
}

/**	Toggling the motor on/off
 */
bool Stepper::ToggleStepperMotor()
{
	cout << endl << !this->state << endl;
	
	//if on, turn off the motor
	if (this->state) {
		this->bus = 0; //turn off the magnets
		this->ticker.detach(); 
	}
	else
	{
		this->ticker.attach_us(callback(this, &Stepper::tick), this->delay * 1000);
	}
	
	this->state = !this->state;
	return this->state;
}

/** this->direction is fetched in the tick() function, updating
 ** the variable automatically changes the motor's direction
 */
int Stepper::ToggleStepperDirection()
{
	if (this->direction == DIR_CLOCKWISE)
	{
		this->direction = DIR_ANTI_CLOCKWISE;
	}
	else
	{
		this->direction = DIR_CLOCKWISE;
	}
	return this->direction;
}


/* 
  ____  _   _               
 / __ \| | | |              
| |  | | |_| |__   ___ _ __ 
| |  | | __| '_ \ / _ \ '__|
| |__| | |_| | | |  __/ |   
 \____/ \__|_| |_|\___|_|   
                           
      Functions          
*/
int main()
{
	uart.puts("I am starting the motor...\n");
	
	//Create an instance of Stepper
	Stepper sm(PC_0, PC_1, PC_2, PC_3, 5);
	
	uart.puts("\
I am now good to go!\n \
You may use the following commands to control the motor,\n \
'S' - toggle the motor on/off.\n \
'T' - toggle the motor's direction between clockwise & anticlockwise.\n \
'D n' - set the motor's delay. Replace n with some number.\n\n"
	);
	
	uart.puts("Type a command > ");
	while (true)
	{

		if (uart.readable())
		{
			char string[10];
			char cmd; int value = 0;
			
			//Get a string from the Serial & output arguments
			uart.gets(string, sizeof(string)/sizeof(*string));
			sscanf(string, "%c %d", &cmd, &value);
			
			
			//Match up the commands
			switch (cmd)
			{
				case 'S': {
					sm.ToggleStepperMotor();
					uart.printf("I have turned the motor %s.\n", (sm.GetStepperState() == true) ? "on" : "off");
					break;
				}
				case 'T': {
					sm.ToggleStepperDirection();
					uart.printf("I have set the motor to go in a %s direction.\n", (sm.GetStepperDirection() == DIR_CLOCKWISE) ? "clockwise" : "anti-clockwise");
					break;				
				}
				case 'D': {
					if (value > 0)
					{
						sm.SetStepperDelay(value);
						uart.printf("I have set the motor's delay to %d.\n", value);
					}
					break;
				}
			}
			uart.puts("Type a command > ");
		}
		
	}
}
