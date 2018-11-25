//Arduino code
#include <SoftwareSerial.h>
SoftwareSerial s(5, 6);
int dataI,dataO;
int INPUT_PIN = 9;
int leds[3] = {10, 11, 12};
int state;

void setup() {
  pinMode(INPUT_PIN, INPUT);
  pinMode(leds[0], OUTPUT);
  pinMode(leds[1], OUTPUT);
  pinMode(leds[2], OUTPUT);
  s.begin(9600);
  Serial.begin(9600);
}

void loop() {
  //  int data = 50;
  //  s.write("A");
  state = digitalRead(INPUT_PIN);
  if (s.available() > 0)
  {
    dataI = s.read();
    if (dataI == 11) {
      digitalWrite(leds[0], HIGH);
      Serial.println(dataI);
    } else if (dataI == 12) {
      digitalWrite(leds[1], HIGH);
      Serial.println(dataI);
    } else if (dataI == 13) {
      digitalWrite(leds[2], HIGH);
      Serial.println(dataI);
    } else if (dataI == 21) {
      digitalWrite(leds[0], LOW);
      Serial.println(dataI);
    } else if (dataI == 22) {
      digitalWrite(leds[1], LOW);
      Serial.println(dataI);
    } else if (dataI == 23) {
      digitalWrite(leds[2], LOW);
      Serial.println(dataI);
    }
  }

  if (state) {
    if (s.available() > 0)
    {
      dataO=99;
      s.write(dataO);
      Serial.println(dataO);
    }
  }
}
