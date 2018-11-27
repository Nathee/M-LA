#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
//54012009
#define FIREBASE_HOST "storagewebdev04.firebaseio.com"
#define FIREBASE_KEY "vaPOOBasHTdyymw8vwSMhaWVPaCvEg5hhDlleUIU"

const String deviceNumber = "001";
const String deviceName = "Mla " + deviceNumber;
const int input = D2, outputs[3] = {D5, D6, D7}, FLAG = 0, get01, get02, get03;

void setupFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);
  Firebase.setString(deviceNumber + "/name", deviceName);
}

void setupPinsMode() {
  for (int i = 0; i < 3; i++) {
    Serial.printf("Setup Output for pin %d", outputs[i]);
    pinMode(outputs[i], OUTPUT);
  }
  pinMode(input, INPUT);
}

void getDataFirebase() {
  get01 = Firebase.getInt(deviceNumber + "/value/OUTPUT01");
  get02 = Firebase.getInt(deviceNumber + "/value/OUTPUT02");
  get03 = Firebase.getInt(deviceNumber + "/value/OUTPUT03");
  digitalWrite(outputs[0], get01);
  digitalWrite(outputs[1], get02);
  digitalWrite(outputs[2], get03);

  FLAG = Firebase.getInt(deviceNumber + "/FLAG");
}

void setDataFirebase() {


  if (get01 || get02 || get03) {
    JsonObject& valueObject2 = jsonBuffer.createObject();
    valueObject2["FLAG"] = 0;
    Firebase.set(deviceNumber, valueObject2);
  }
  int value = digitalRead(input);
  delay(50);
  if (value == HIGH && ) {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& valueObject = jsonBuffer.createObject();
    valueObject["OUTPUT01"] = 0;
    valueObject["OUTPUT02"] = 0;
    valueObject["OUTPUT03"] = 0;
    Firebase.set(deviceNumber + "/value", valueObject);
    valueObject2["FLAG"] = 1;
    Firebase.set(deviceNumber, valueObject2);
  }
}

void setup() {
  Serial.begin(9600);
  WiFiManager wifiManager;
  wifiManager.autoConnect("M'LA Robot");
  Serial.println("connected...yeey :)");

  setupFirebase();
  setupPinsMode();

}

void loop() {
  getDataFirebase();
  setDataFirebase();
}
