#include "mbed.h"

#include <iostream>
using namespace std;

DigitalIn button(PC_13);
RawSerial pc(PA_2, PA_3);

#define DIR_CLOCKWISE		0
#define DIR_ANTI_CLOCKWISE	1

class Stepper
{
private:
	BusOut bus;
	bool state;
	int direction;
	int cur_magnet;
	int delay;
	Ticker ticker;
	
	int tick();

public:
	Stepper(PinName p1, PinName p2, PinName p3, PinName p4, int delay);
	~Stepper();
	bool ToggleStepperMotor();
	int ToggleStepperDirection();
	int SetStepperDelay(int delay);
	int GetStepperDirection();
	int GetStepperDelay();
};


Stepper::Stepper(PinName p1, PinName p2, PinName p3, PinName p4, int delay): 
	bus(p1,p2,p3,p4)
{
	
	
	SetStepperDelay(delay);
	ToggleStepperMotor(); //initially turn it on
	ticker.attach_us(this, &Stepper::tick, 1000);
}

int Stepper::SetStepperDelay(int delay)
{
	this->delay = delay;
	return delay;
}

int Stepper::GetStepperDelay()
{
	return this->delay;
}
bool Stepper::ToggleStepperMotor()
{
	this->state = !this->state;
}

int Stepper::GetStepperDirection()
{
	this->cur_magnet = 0;
	return this->direction;
}
int Stepper::tick()
{
	int dir = GetStepperDirection();
	int delay = GetStepperDelay();
	
	this->bus = (1 << this->cur_magnet);
	this->cur_magnet = (this->cur_magnet + dir) % 4;
	
}
Stepper::~Stepper()
{
	
}

int main()
{
	printf("starting stepper motor with a delay of 5");
	Stepper sm(PC_0, PC_1, PC_2, PC_3, 5);
	

}