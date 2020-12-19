#include "SoftwareSerial.h"
#include <ESP8266HTTPClient.h>
#include <Adafruit_MLX90614.h>
#include "ESP8266WiFi.h"
#include <Wire.h>
#include<ArduinoJson.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
char* ssid = "namlam9x";
char* password = "m4tmangm4yhomroi";
const int buzzer = 2;
const int threshold = 37;

//Your Domain name with URL path or IP address with path
// String serverName = "http://jsonplaceholder.typicode.com/posts";
String serverName = "http://149.28.144.141:3003/metrics";
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

void setup() {

  pinMode (2, OUTPUT);

  //esp.begin(9600);

  Serial.begin(9600);



  connectWifi();
  mlx.begin();
}
void connectWifi() {

  WiFi.begin(ssid, password);
  //Serial.println(WL_CONNECTED);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println(WiFi.status());

  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connection Successful");
    Serial.print("The IP Address of ESP8266 Module is: ");
    Serial.println(WiFi.localIP());
  }




}
void loop() {

  //Send an HTTP POST request every 10 minutes
  //if ((millis() - lastTime) > timerDelay) {
  //Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Your Domain name with URL path or IP address with path
    http.begin(serverName);

    // Specify content-type header
    // http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    // Data to send with HTTP POST
    String httpRequestData =  String(mlx.readAmbientTempC()) + "|" + String(mlx.readObjectTempC());;
    DynamicJsonDocument doc(2048);
    doc["data"] = httpRequestData;
    String json;
    serializeJson(doc, json);
    // Send HTTP POST request


    http.addHeader("Content-Type", "application/json");
    //http.method("POST");
    int httpResponseCode = http.POST(json);
    // int httpResponseCode = http.GET();
    Serial.println(http.getString());
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  delay(1000);
  //  lastTime = millis();
  // }
}
