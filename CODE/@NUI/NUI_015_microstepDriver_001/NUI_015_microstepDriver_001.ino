#include <AccelStepper.h>

AccelStepper stepperA(1, 2, 3); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)

void setup()
{      
    stepperA.setAcceleration(1500); // acceleration in steps per second
    stepperA.setMaxSpeed(1100);    // maximum speed
}

void loop()
{
    
    stepperA.runToNewPosition(10000);
    stepperA.run();
    delay(2000);
    
    stepperA.runToNewPosition(-10000);
    stepperA.run();
    delay(2000);
}

