#define dc 9
#define poten A0


void setup() {
  Serial.begin(9600);
  pinMode(dc, OUTPUT);
  pinMode(poten, INPUT);
}

void loop() {

  for (int i = 0; i < 360; i++) {
    //convert 0-360 angle to radian (needed for sin function)
    float rad = DEG_TO_RAD * i; //calculate sin of angle as number between 0 and 255
    int sinOut = constrain((sin(rad) * 128) + 128, 0, 255);
    Serial.println(sinOut);
    analogWrite(dc, sinOut);
    delay(15);
  }
}

