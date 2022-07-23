#include<Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>        //import ESP8266 WiFi library
#include <ESP8266HTTPClient.h>  //import ESP8266 HTTP Client library
#include <WiFiClient.h>
#include <SPI.h>   
#include "connections_server.h"

void connection_Server(){
   WiFiClient client;
  client.setTimeout(10000);
  if (!client.connect("aquamonia.com", 80)) {
    Serial.println(F("Connection failed"));
    return;
  }
  Serial.println(F("Connected!"));

  // Send HTTP request
  client.println(F("GET /os/ex HTTP/1.1"));
  client.println(F("Host: aquamonia.com"));
  client.println(F("Connection: close"));
  if (client.println() == 0) {
    Serial.println(F("Failed to send request"));
    client.stop();
    return;
  }
  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)) {
    Serial.println(F("Invalid response"));
    client.stop();
    return;
  }

  // Allocate the JSON document
  // Use arduinojson.org/v6/assistant to compute the capacity.
  const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(6) + 60;
  DynamicJsonDocument doc(1024);

  // Parse JSON object
  DeserializationError error = deserializeJson(doc, client);
  switch (error.code()) {
      case DeserializationError::Ok:
          Serial.println(F("Error : Deserialization succeeded"));
          break;
      case DeserializationError::InvalidInput:
          Serial.println(F("Error : Invalid input!"));
          break;
      case DeserializationError::NoMemory:
          Serial.println(F("Error : Not enough memory"));
          break;
      default:
          Serial.println(F("Error : Deserialization failed"));
          break;
  }
}
