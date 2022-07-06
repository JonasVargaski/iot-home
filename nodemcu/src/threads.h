#ifndef THREDS_APP_H
#define THREDS_APP_H

#include <config.h>
#include <Thread.h>

void blinkConnectionLed()
{
  portO.digitalToggle(PORT_I_8);
}

void connectMqtt()
{
  if (!mqttClient.connected())
  {
    Serial.println(F("[MQTT] Attempting connection..."));

    String clientId = F("client:") + WiFi.macAddress();

    if (mqttClient.connect(clientId.c_str()))
    {
      Serial.println(F("[MQTT] connected."));
      
      DynamicJsonDocument doc(0);
      events.dispatch("connected", doc);
    }
    else
    {
      Serial.print(F("[MQTT] Connection failed, rc="));
      Serial.println(mqttClient.state());

      DynamicJsonDocument doc(0);
      events.dispatch("disconnected", doc);
    }
  }
}

Thread statusLedThread = Thread(800, blinkConnectionLed);
Thread connectMqttThread = Thread(6000, connectMqtt);

#endif