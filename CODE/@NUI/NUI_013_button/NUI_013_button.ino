int sensor = 0;
int location = 0;

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(13, OUTPUT);

}

void loop() {
  sensor = analogRead(A0);
  Serial.println(sensor);

  if (sensor == 1023) {
    location = 0;
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

}
