#define dc 9

void setup() {
  Serial.begin(9600);
  pinMode(dc, OUTPUT);
}

void loop() {
  int poten = analogRead(A0);
  int mapVal = map(poten, 0, 1024, 0, 255);
  Serial.print(poten);
  Serial.print(" / ");
  Serial.println(mapVal);
  analogWrite(dc, mapVal);
  delay(15);
}

