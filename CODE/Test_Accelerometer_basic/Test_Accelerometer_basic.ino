int x, y, z = 0;
int mapX = 0;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(z, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  x = analogRead(A0);
  y = analogRead(A1);
  z = analogRead(A2);

  mapX = map(x, 270, 400, 0, 255);

 // Serial.println(mapX);
    Serial.print(x);
    Serial.print("/");
    Serial.print(y);
    Serial.print("/");
    Serial.println(z);

  delay(100);

}
