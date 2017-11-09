const byte LED = 6;
const byte Button = 2;
const byte interruptPin = 2;
volatile byte state = LOW;

void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(Button, INPUT_PULLUP);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
}

void loop()
{
  static byte last = LOW;
  static short count = 0;
  byte ButtonState = digitalRead(Button);
  digitalWrite(LED, state);

  if (ButtonState != last)
  {
    if (ButtonState == LOW)
    {
      analogWrite(LED, count += 5);
      Serial.println(count);
    }
    last = ButtonState;
  }

  if (count > 255)
  {
    digitalWrite(LED, LOW);
    count = 0;
  }
}


void blink() {
  state = !state;
}

