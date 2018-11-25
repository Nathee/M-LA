#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#include <SoftwareSerial.h>
SoftwareSerial s(D6, D5);
int dataI, dataO;

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
    dataO = 11;
    s.write(dataO);
  } else {
    dataO = 21;
    s.write(dataO);
  }
  if (led2 == "ON") {
    dataO = 12;
    s.write(dataO);
  } else {
    dataO = 22;
    s.write(dataO);
  }
  if (led3 == "ON") {
    dataO = 13;
    s.write(dataO);
  } else {
    dataO = 23;
    s.write(dataO);
  }

}

void setup() {
  s.begin(9600);
  Serial.begin(9600);
  WiFiManager wifiManager;
  wifiManager.autoConnect("M'LA Robot");
  Serial.println("connected...yeey :)");

  setupFirebase();

  setupPinsMode();
}

void loop() {
//  s.write("A");
  getData();
  if (s.available() > 0)
  {
    dataI = s.read();
    if (dataI == 99) {
      Firebase.push("/Arduino/OUTPUT01", "OFF");
      Firebase.push("/Arduino/OUTPUT02", "OFF");
      Firebase.push("/Arduino/OUTPUT03", "OFF");
    }
    Serial.println(dataI);
  }
}
