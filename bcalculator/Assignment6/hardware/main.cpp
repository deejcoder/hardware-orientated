#include "mbed.h"
#include "uart.h"
//#include "stepper.h"
#include <string>


//LCD marcos
#define LCD_DATA 1
#define LCD_INSTRUCTION 0

//What number to count upto?
#define MAX_COUNT       15
#define MAX_COUNT_BITS  4   //max# of bits


/*
    PIN DEFINITIONS
*/
//UART
DigitalIn button(PC_13);
Uart uart(USBTX, USBRX);

//LEDs
DigitalOut greenLED(PA_5);
DigitalOut blueLED(PA_7);

//Servo
PwmOut servo(PB_0);

//Ultrasonic Sensor
PwmOut usTrig(PB_3);
InterruptIn usEcho(PB_5);

//LCD
BusOut lcdData(PA_9, PA_8, PB_10, PB_4);
DigitalOut _en(PC_7), _rs(PB_6);

/*
    VARIABLES
*/
//Ultrasonic sensor variables
Timer usTimer;
bool usState = false;
volatile int usTime = 0;

//========[ Stepper from Assignment 5 ]==========

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


//#include "stepper.h"

Stepper::Stepper(PinName p1, PinName p2, PinName p3, PinName p4, int delay)
    : bus(p1, p2, p3, p4)
{

    //initial values
    this->state = false;
    this->tickcount = 0;
    SetStepperDelay(delay);
    SetStepperDirection(DIR_CLOCKWISE);
    //ToggleStepperMotor();      //initially turn it on
    
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




//========[ Servo Motor ]========

void moveServo(int degree) {
    servo.period_us(20000);
    
    if(degree > 90) return;
    
    //how much microsec per degree 0-90 degrees?
    const int pw = 1000/90;
    servo.pulsewidth_us(1000 + (degree*pw));
    wait_us(40000);
}

//===========[ Ultrasonic Sensor functions ]===========

void toggleUltraSensor() {
    if(usState) {
        usTrig = 0; //set it to LOW
    }
    else {
        usTrig = 1; //set it to HIGH
        usTrig.period_us(100000);
        usTrig.pulsewidth_us(10);
    }
    usState = !usState;
}

void usEchoStart(void) {
    if(usState) {
        usTimer.reset();
        usTimer.start();
    }
}

void usEchoEnd(void) {
    if(usState) {
        usTimer.stop();
        usTime = usTimer.read_us();
    }
}


//=============[ LCD functions ]===============
//Setup
void lcdinit();
static void lcdInit8Bit(unsigned char command); 

//Controlling data
void sendCommand(unsigned char command);
void sendChar(unsigned char c);
void sendString(char *s);
void cls();
static void lcdSetRS(int mode);
static void lcdPulseEN(void);

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

//===========[ Input & Entry point ]===========
        
int main()
{
    //Set up the stepper motor
    Stepper sm(PC_0, PC_1, PC_2, PC_3, 5);
    
    //Set up the ultrasonic sensor
    usEcho.rise(&usEchoStart);
    usEcho.fall(&usEchoEnd);
    
    //Set up the LCD
    lcdinit();
    
    
    while (1) {
        
        //Update US distance
        if(usTime && usState) {
            //int distance = (int)rint(0.017*usTime);
            uart.printf("U %d\n", usTime);
            usTime = 0;
        }
        
        char str[10];
        if (uart.canReadLine()) {
            uart.readLine(str);
            str[strlen(str)-1] = '\0';
            //Get a string from the Serial & output arguments
            
            char cmd; int value; char msg[50];
                
            if(sscanf(str, "%c", &cmd)) {
            
            
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
                        sscanf(str, "%c %d", &cmd, &value);
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
                        break;
                    }
                    case 'a':
                    case 'A': {
                        sscanf(str, "%c %d", &cmd, &value);
                        if(value > 0) {
                            moveServo(value);
                        }
                        break;
                    }
                    case 'u':
                    case 'U': {
                        toggleUltraSensor();
                        break;
                    }
                    case 'm':
                    case 'M': {
                        sscanf(str, "%c %[^\n]", &cmd, msg); //allow spaces :)
                        if(strlen(msg) > 0 && strlen(msg) < 50) {
                            cls();
                            sendString(msg);
                        }
                        break;
                    }
                        
                }
                
            }
        }
    }
}
