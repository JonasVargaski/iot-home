#ifndef MQTT_H
#define MQTT_H

#include <ArduinoJson.h>
#include <config.h>

void mqttCallback(char *topic, byte *payload, unsigned int length)
{
  String data;

  for (unsigned int i = 0; i < length; i++)
    data += (char)payload[i];

  Serial.print(F("[MQTT] Message arrived "));
  Serial.println(data);

  DynamicJsonDocument doc(2048);
  deserializeJson(doc, data);

  events.dispatch(doc["action"].as<const char*>(), doc["payload"]);
}

#endif