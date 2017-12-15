//1: button detection HIGH or LOW (start  or stop)
//2: Read pot value and store it as motorSpeed
//3 Read Direction switch and store value FWD or REV
//4: Display values on 7 segment LED display
//5: Run the motor with the values from above

int ledPin = 13;      // select the pin for the LED

// stepper pins
#define DIR_PIN 2
#define STEP_PIN 3
#define switchPin 4

//motorSpeed from POT
int sensorPin = A0;    // select the input pin for the potentiometer

// Start Stop Push Button
int button = 5;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status

// Limit switches
int limitLeft = 11;
int limitRight = 12;
// display pot
int displayPin = A1;    // select the input pin for the potentiometer

void setup(){
 Serial.begin(9600);
 pinMode(DIR_PIN, OUTPUT);
 pinMode(STEP_PIN, OUTPUT);
 pinMode (switchPin, INPUT);
 pinMode(button, INPUT);
 // Show me power on LED
 pinMode(ledPin, OUTPUT); 
}

void loop(){
// stop stepper and wait for button push to start routine
// gather speed and dir values
// what function do I call here to gather info?
}


void startStopButton(){
// detact if button is pushed
// Button pushed case one = run stepper based on motorSpeed and Direction
// if pushed while stepper is running - stop the motor and the elapsed time
// if pushed again, start stepper and elapsed time

}
void duration (){
// display elapsed time on LED display that only starts when motor is stepping
// pause when push button is pressed
}

void displayInfo(){
// pot value to display speed and direction and elapsed time on LED display
// map this in thirds - for now 
// 0-335 = show direction
// 336-695 = show motorSpeed
// 696-1023 = show elasped time
}

void motorSpeed(){
// get POT value and make it the stepper speed
}

void getDirection(){
// get the direction from the switch pin
// HIGH = FWD
// LOW = REV
}

void limitLeft(){
// if limit switch is hit - stop stepper and elapsed time
// set direction to FWD?
// restart elapsed time?
}

void limitRight(){
// if limit switch is hit - stop stepper and elapsed time
// set direction to REV?
// restart elapsed time?
}
