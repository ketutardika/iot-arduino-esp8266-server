#include<Arduino.h>
#include <ESP8266WiFi.h>        //import ESP8266 WiFi library
#include <ESP8266HTTPClient.h>  //import ESP8266 HTTP Client library
#include <WiFiClient.h>
#include <SPI.h>  
#include "wifi_setup.h"


const char* ssid = "Creative Alokaa";  // Enter your local network SSID
const char* password = "Indrakila6";   // Enter your local network Password
void wifi_Setup(){
  WiFi.begin(ssid, password);  // Pass the credential for local wifi network to connect ESP8266 board
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP Address");
  Serial.println(WiFi.localIP());
}