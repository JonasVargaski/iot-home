#ifndef SETUP_H
#define SETUP_H

#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>
#include <config.h>

void setupIOs()
{
  Wire.begin(0, 2);
  portO.init();
  portI.init();

  for (int i = 0; i < 8; i++)
  {
    portO.pinMode(i, OUTPUT);
    portI.pinMode(i, INPUT);
  }

  pinMode(PORT_I_INTERRUPT, INPUT);
}

void setupWifi()
{
  delay(10);

  Serial.println();
  Serial.print(F("[SETUP] Connecting to \""));
  Serial.print(WIFI_SSID);
  Serial.print("@");
  Serial.print(WIFI_PASS);
  Serial.print("\"");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.printf("\n[SETUP] WiFi Connected. Ip: %s\n", WiFi.localIP().toString().c_str());
}

#endif