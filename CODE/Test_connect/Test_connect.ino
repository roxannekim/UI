/*

Magnet Connector [RECIEVER} side.

*/


unsigned long millisSerial;        // milliseconds when Serial was received
bool bSerialActive = false;        // Serial data detected
bool bConnected = false;           // Serial connection (true or false based on timeout)
int wheelVal = 0;                  // value received from the wheel


void setup()
{ 
    Serial.begin(9600);
}

void loop()
{
    if (Serial.available() > 0) 
    {
        wheelVal = Serial.parseInt();
    
        bSerialActive = true;
        millisSerial = millis();
    }

    if(!bConnected && bSerialActive)
    {
        bConnected = true;        // wheel connected..
        Serial.println("wheel connected!");
    }
    else if(bConnected && (millis() - millisSerial > 500))    
    {
        bSerialActive = false;    // wheel disconnected..
        bConnected = false;
        Serial.println("wheel disconnected!");
    }

    if(bConnected)
    {
      Serial.print("received: ");
      Serial.println(wheelVal);
    }
}


