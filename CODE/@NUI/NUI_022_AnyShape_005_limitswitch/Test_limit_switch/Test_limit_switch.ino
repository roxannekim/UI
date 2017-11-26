
#define switchPin1 49
#define switchPin2 51
#define switchPin3 53

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;

void setup() {
  pinMode (switchPin1, INPUT);
  pinMode (switchPin2, INPUT);
  pinMode (switchPin3, INPUT);
  Serial.begin(9600);

}

void loop() {
  buttonState1 = digitalRead(switchPin1);
  buttonState2 = digitalRead(switchPin2);
  buttonState3 = digitalRead(switchPin3);
  Serial.print(buttonState1);
  Serial.print("  /  ");
  Serial.print(buttonState2);
  Serial.print("  /  ");
  Serial.println(buttonState3);
}
