#ifndef _STEPPER_H
#define _STEPPER_H
#include "mbed.h"

//Preprocessor definitions
#define DIR_CLOCKWISE       1
#define DIR_ANTI_CLOCKWISE  3


class Stepper
{
private:
    
	//All pins for motor => bus
	BusOut bus;
    
	bool state;
	int direction;
	int cur_magnet;
	int delay;
    
	int tickcount;
	Ticker ticker;
    
	//Only want the class accessing this
	void tick(void);

public:
    
	//Constructor/Destructor
	Stepper(PinName p1, PinName p2, PinName p3, PinName p4, int delay);
	~Stepper();
    
	//Getters
	bool GetStepperState()     { return this->state; }
	int GetTickCount()         { return this->tickcount; }
	int GetStepperDelay()      { return this->delay; }
	int GetStepperDirection()  { return this->direction; }
    
	//Setters
	int SetStepperDelay(int delay);
	int SetStepperDirection(int dir);
    
	//Toggles
	bool ToggleStepperMotor();
	int ToggleStepperDirection();
    
};

#endif
