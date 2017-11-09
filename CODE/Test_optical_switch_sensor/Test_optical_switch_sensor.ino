
int sensor = HIGH;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sensor, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  sensor = digitalRead(6);
  Serial.println(sensor);
}
