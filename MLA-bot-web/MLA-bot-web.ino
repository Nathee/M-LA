#include <ESP8266WiFi.h>
//needed for library
#include <ESP8266WebServer.h>
#include <WiFiManager.h>


boolean ledStatus01 = false;
boolean ledStatus02 = false;
boolean ledStatus03 = false;
boolean ledStatus04 = false;
String strLedStatus01;
String strLedStatus02;
String strLedStatus03;
String strLedStatus04;
String strButtonLabel01;
String strButtonLabel02;
String strButtonLabel03;
String strButtonLabel04;

const int input = D2, outputs[4] = {D4, D5, D6, D7};
bool getI = false;
ESP8266WebServer server(80);


void handleRoot() {
  server.send(200, "text/html", getHtmlPage() );
}

String getHtmlPage() {
  if (ledStatus01) {
    strLedStatus01 = "ขณะนี้กำลังเสริฟโต๊ะที่ 01";
    strButtonLabel01 = "หยุด";
    Serial.println("led on now");
  } else {
    strLedStatus01 = "โต๊ะที่ 01 พร้อมเสริฟ";
    strButtonLabel01 = "เสริฟโต๊ะที่ 01";
  }
  if (ledStatus02) {
    strLedStatus02 = "ขณะนี้กำลังเสริฟโต๊ะที่ 02";
    strButtonLabel02 = "หยุด";
    Serial.println("led on now");
  } else {
    strLedStatus02 = "โต๊ะที่ 02 พร้อมเสริฟ";
    strButtonLabel02 = "เสริฟโต๊ะที่ 02";
  }
  if (ledStatus03) {
    strLedStatus03 = "ขณะนี้กำลังเสริฟโต๊ะที่ 03";
    strButtonLabel03 = "หยุด";
    Serial.println("led on now");
  } else {
    strLedStatus03 = "โต๊ะที่ 03 พร้อมเสริฟ";
    strButtonLabel03 = "เสริฟโต๊ะที่ 03";
  }
  if (ledStatus04) {
    strLedStatus04 = "ขณะนี้กำลังเสริฟโต๊ะที่ 04";
    strButtonLabel04 = "หยุด";
    Serial.println("led on now");
  } else {
    strLedStatus04 = "โต๊ะที่ 04 พร้อมเสริฟ";
    strButtonLabel04 = "เสริฟโต๊ะที่ 04";
  }

  String css = "<style>.button {background-color: #990033;border: none;border-radius: 4px;color: white;padding: 7px 15px;text-align: center;text-decoration: none;text-decoration: none;}</style>";

  String strHtml = "<!DOCTYPE html><html><head>";
  strHtml += css;
  strHtml += "<meta http-equiv='Content-Type' content='text/html; charset=UTF-8'>";
  strHtml += "<meta name=\"viewport\" content=\"initial-scale=1, maximum-scale=1, ";
  strHtml += "minimum-scale=1, width=device-width, height=device-height\">";
  strHtml += "<title>Controller</title>";
  strHtml += "</head><body><h1>Controller/ควบคุม</h1>";

  strHtml += "<h1>สถานะการทำงานโต๊ะที่ 01 : ";
  strHtml += strLedStatus01;//****
  strHtml += "</h1>";
  strHtml += "<br>";
  strHtml += "<a href='./toggle01' class='button'>";
  strHtml += strButtonLabel01;
  strHtml += "</a> ";

  strHtml += "<h1>สถานะการทำงานโต๊ะที่ 02 : ";
  strHtml += strLedStatus02;//****
  strHtml += "</h1>";
  strHtml += "<br>";
  strHtml += "<a href='./toggle02' class='button'>";
  strHtml += strButtonLabel02;
  strHtml += "</a> ";

  strHtml += "<h1>สถานะการทำงานโต๊ะที่ 03 : ";
  strHtml += strLedStatus03;//****
  strHtml += "</h1>";
  strHtml += "<br>";
  strHtml += "<a href='./toggle03' class='button'>";
  strHtml += strButtonLabel03;
  strHtml += "</a> ";

  strHtml += "<h1>สถานะการทำงานโต๊ะที่ 04 : ";
  strHtml += strLedStatus04;//****
  strHtml += "</h1>";
  strHtml += "<br>";
  strHtml += "<a href='./toggle04' class='button'>";
  strHtml += strButtonLabel04;
  strHtml += "</a> ";

  strHtml += "<br>";
  strHtml += "<br>";
  strHtml += "<br>";
  strHtml += "<hr>";
  strHtml += "<a href='./' class='button'>";
  strHtml += "กลับหน้าหลัก";
  strHtml += "</a> ";
  strHtml += "<a href='./reset' class='button'>";
  strHtml += "RESET";
  strHtml += "</a> ";
  strHtml += "</body></html>";
  return strHtml;
}

void setup() {
  pinMode(input, INPUT);
  pinMode(outputs[0], OUTPUT);
  pinMode(outputs[1], OUTPUT);
  pinMode(outputs[2], OUTPUT);
  pinMode(outputs[3], OUTPUT);
  digitalWrite(outputs[0], LOW);
  digitalWrite(outputs[1], LOW);
  digitalWrite(outputs[2], LOW);
  digitalWrite(outputs[3], LOW);
  delay(2000);

  Serial.begin(9600);
  WiFiManager wifiManager;
  wifiManager.autoConnect("M'LA Robot");
  Serial.println("connected...yeey :)");

  server.on("/", handleRoot);
  server.on("/toggle01", toggleLed01);
  server.on("/toggle02", toggleLed02);
  server.on("/toggle03", toggleLed03);
  server.on("/toggle04", toggleLed04);
  server.on("/reset", reSet);

  server.begin();
  Serial.println("HTTP server started");
}
void reSet() {
  ledStatus01 = false;
  ledStatus02 = false;
  ledStatus03 = false;
  digitalWrite(outputs[0], LOW);
  digitalWrite(outputs[1], LOW);
  digitalWrite(outputs[2], LOW);  
  digitalWrite(outputs[3], LOW);  
  server.send(200, "text/html", getHtmlPage() );
}

void toggleLed01() {
  if (ledStatus01) {
    digitalWrite(outputs[0], LOW);
    ledStatus01 = true ;
    Serial.println("01 now Off");
  } else {
    digitalWrite(outputs[0], HIGH);
    ledStatus01 = false;
    Serial.println("01 now On");
  }
  server.send(200, "text/html", getHtmlPage() );
}

void toggleLed02() {
  if (ledStatus02) {
    digitalWrite(outputs[1], LOW);
    ledStatus02 = true ;
    Serial.println("02 now Off");
  } else {
    digitalWrite(outputs[1], HIGH);
    ledStatus02 = false;
    Serial.println("02 now On");
  }
  server.send(200, "text/html", getHtmlPage() );
}

void toggleLed03() {
  if (ledStatus03) {
    digitalWrite(outputs[2], LOW);
    ledStatus03 = true;
    Serial.println("03 now Off");
  } else {
    digitalWrite(outputs[2], HIGH);
    ledStatus03 = false;
    Serial.println("03 now On");
  }
  server.send(200, "text/html", getHtmlPage() );
}

void toggleLed04() {
  if (ledStatus04) {
    digitalWrite(outputs[3], LOW);
    ledStatus04 = true;
    Serial.println("04 now Off");
  } else {
    digitalWrite(outputs[3], HIGH);
    ledStatus04 = false;
    Serial.println("04 now On");
  }
  server.send(200, "text/html", getHtmlPage() );
}

void loop() {
  getI = digitalRead(input);
  if (getI) {
    reSet();
  }
  server.handleClient();
}
