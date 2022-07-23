#include <ArduinoJson.h>
#include "led_functions.h"
#include "wifi_setup.h"
#include "connections_server.h"
#include "wifi_managers.h"
#include <EEPROM.h>

#define LED_PIN 13
int addr = 0;
int address = 0;
byte value;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  EEPROM.begin(512);
  setupLED(LED_PIN);
  device_server_inst();
  wifi_Managers();
}

void loop() {
  // put your main code here, to run repeatedly:
  connection_Server();
  device_server_setup();
  powerOnLED(LED_PIN);
  delay(500);
  powerOffLED(LED_PIN);
  delay(500);

  Serial.println("");
  Serial.print(char(EEPROM.read(addr)));
  addr++;  //Increment address
  Serial.print(char(EEPROM.read(addr)));
  addr++;  //Increment address
  Serial.println(char(EEPROM.read(addr)));

  //Read string from eeprom (testing eeprom)
  String strText;
  for (int i = 0; i < 14; i++) {
    strText = strText + char(EEPROM.read(0x0F + i));
  }
  Serial.print(strText);
}