#ifndef OTA_H
#define OTA_H

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <config.h>

void updateSW(DynamicJsonDocument doc)
{
  String url = doc["url"];
  WiFiClient client;

  Serial.print(F("[UPDATE] Starting update: "));
  Serial.println(url);

  ESPhttpUpdate.rebootOnUpdate(false);

  ESPhttpUpdate.onProgress([](size_t progress, size_t total)
                           {
                             Serial.print(progress * 100 / total);
                             Serial.println("%"); });

  t_httpUpdate_return returnType = ESPhttpUpdate.update(client, url);

  switch (returnType)
  {
  case HTTP_UPDATE_FAILED:
    Serial.println(F("[UPDATE] Update failed. reason: ") + ESPhttpUpdate.getLastErrorString());
    break;
  case HTTP_UPDATE_NO_UPDATES:
    Serial.println(F("[UPDATE] no updates available"));
    break;
  case HTTP_UPDATE_OK:
  {
    Serial.println(F("[UPDATED] restarting..."));
    ESP.restart();
  }
  break;
  default:
    break;
  }
}

#endif