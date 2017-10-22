#include "stepper.h"

Stepper::Stepper(PinName p1, PinName p2, PinName p3, PinName p4, int delay)
	: bus(p1, p2, p3, p4)
{

	//initial values
	this->state = false;
	this->tickcount = 0;
	SetStepperDelay(delay);
	SetStepperDirection(DIR_CLOCKWISE);
	ToggleStepperMotor();      //initially turn it on
    
}

/** Stop the motor if it is going before destroying the object
 */
Stepper::~Stepper()
{
	//If it is on, turn it off.
	if(GetStepperState()) {
		ToggleStepperMotor();
	}
}

/*  Performed every this->delay milliseconds, makes the motor go in this->direction
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

/** Toggling the motor on/off
 */
bool Stepper::ToggleStepperMotor()
{
    
	//if on, turn off the motor
	if(this->state) {
		this->bus = 0;     //turn off the magnets
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
