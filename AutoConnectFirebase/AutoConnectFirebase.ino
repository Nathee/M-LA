#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

int leds[3] = {D0, D1, D2};
int states[3] = {LOW, LOW, LOW};
int totalDevices = 3;

#define firebaseURl "storagewebdev04.firebaseio.com"
#define authCode "vaPOOBasHTdyymw8vwSMhaWVPaCvEg5hhDlleUIU"


String chipId = "123";

void setupFirebase() {

  Firebase.begin(firebaseURl, authCode);
}

void setupPinsMode() {

  // setup Pin mode as output.


  for (int i; i < totalDevices; i++) {

    Serial.printf("Setup Output for pin %d", leds[i]);
    pinMode(leds[i], OUTPUT);
  }
}

void getData() {

  String path = "Arduino";
  //  String path = chipId + "/states";
  FirebaseObject object = Firebase.get(path);

  String led1 = object.getString("OUTPUT01");
  String led2 = object.getString("OUTPUT02");
  String led3 = object.getString("OUTPUT03");
  if (led1 == "ON") {
    digitalWrite(leds[0], HIGH);
    Serial.println("Led 1: ON");
  } else {
    digitalWrite(leds[0], LOW);
    Serial.println("Led 1: OFF");
  }
  if (led2 == "ON") {
    digitalWrite(leds[1], HIGH);
    Serial.println("Led 2: ON");
  } else {
    digitalWrite(leds[1], LOW);
    Serial.println("Led 2: OFF");
  }
  if (led3 == "ON") {
    digitalWrite(leds[2], HIGH);
    Serial.println("Led 3: ON");
  } else {
    digitalWrite(leds[2], LOW);
    Serial.println("Led 3: OFF");
  }
  //  Serial.println("Led 1: ");
  //  Serial.println(led1);
  //
  //  //
  //  Serial.println();
  //  Serial.println("Led 2: ");
  //  Serial.println(led2);
  //
  //  //
  //  Serial.println();
  //  Serial.println("Led 3: ");
  //  Serial.println(led3);


  // write output high or low to turn on or off led
  //  digitalWrite(leds[0], led1);

  //  digitalWrite(leds[1], led2);

  //  digitalWrite(leds[2], led3);

}

void setup() {
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect("M'LA Robot");
  Serial.println("connected...yeey :)");

  setupFirebase();

  setupPinsMode();
}

void loop() {
  getData();
}
