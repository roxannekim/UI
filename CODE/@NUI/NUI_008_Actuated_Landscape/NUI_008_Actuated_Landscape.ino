/***********************************************************************************
 *           RobotGeek Firgelli Linear Actuator Control Demo   
 *           Absolute Analog Control                
 * 
 *
 *  The following sketch will allow you to control a Firgelli Linear actuator using
 *  the RobotGeek Slider and RobotGeek Knob
 *
 *  Products
 *  
 *    http://www.robotgeek.com/robotgeek-geekduino-sensor-kit
 *    http://www.robotgeek.com/robotgeek-slider
 *    http://www.robotgeek.com/robotgeek-rotation-knob
 *    http://www.robotgeek.com/p/power-supply-6vdc-2a.aspx
 *    Firgelli Mini Linear Actuators http://www.robotgeek.com/store/Search.aspx?SearchTerms=firgelli
 *    http://www.robotgeek.com/robotgeek-small-workbench.aspx
 
 *  Wiring
 *    100mm Linear Actuator - Digital Pin 9 
 *    50mm Linear Actuator - Digital Pin 10 
 *
 *    Knob   - Analog Pin 0
 *    Slider - Analog Pin 1 
 *    Jumper for pins 9/10/11 should be set to 'VIN'
 *  
 *
 *  Control Behavior:
 *    Moving the analog controls will move the linear actuators keeping absolute position.
 *
 *  External Resources
 *
 ***********************************************************************************/


//Includes
#include <Servo.h> 

//Defines
#define LINEAR100PIN 9        //Linear Actuator Digital Pin
#define LINEAR210PIN 10        //Linear Actuator Digital Pin

//max/min pulse values in microseconds for the linear actuators
#define LINEAR100_MIN      10  //
#define LINEAR100_MAX      2000 //
#define LINEAR210_MIN  10     //
#define LINEAR210_MAX  2000    //


Servo LINEAR100, LINEAR210;  // create servo objects to control the linear actuators

int linear100Value = 1500;   //current positional value being sent to the linear actuator. 
int linear210Value = 1500;  //current positional value being sent to the linear actuator. 

int speed = 10;

void setup() 
{ 
  //initialize servos
  LINEAR100.attach(LINEAR100PIN, LINEAR100_MIN, LINEAR100_MAX);      // attaches/activates the linear actuator as a servo object 
  LINEAR210.attach(LINEAR210PIN, LINEAR210_MIN, LINEAR210_MAX);  // attaches/activates the linear actuator as a servo object 

  //Analog pins do not need to be initialized
  
  //use the writeMicroseconds to set the linear actuators to their default positions
  LINEAR100.writeMicroseconds(linear100Value); 
  LINEAR210.writeMicroseconds(linear210Value);
} 

void loop() 
{ 

  /**************linear actuator Positions *******************************/
  //read the values from the analog sensors
//  knobValue = analogRead(KNOB_PIN);
//  sliderValue = analogRead(SLIDER_PIN);

//  linear100Value = map(knobValue, 0, 1023, LINEAR100_MAX, LINEAR100_MIN); //Map analog value from the sensor to the linear actuator
//  linear210Value = map(sliderValue, 0, 1023, LINEAR50_MAX, LINEAR50_MIN); //Map analog value from the sensor to the linear actuator
 
  //use the writeMicroseconds to set the servos to their new positions
  LINEAR100.writeMicroseconds(linear100Value); 
  LINEAR210.writeMicroseconds(linear210Value);
} 
