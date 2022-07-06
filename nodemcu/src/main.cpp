#include <ArduinoJson.h>
#include <config.h>
#include <setup.h>
#include <ota.h>
#include <mqtt.h>
#include <threads.h>

void onConnect(DynamicJsonDocument doc)
{
  statusLedThread.setInterval(250);

  Serial.print(F("[MQTT] Subscribed on topic "));
  Serial.print(TOPIC_ID + WiFi.macAddress() + " | ");
  Serial.println(TOPIC_ID_BROADCAST);

  mqttClient.subscribe((TOPIC_ID + WiFi.macAddress()).c_str());
  mqttClient.subscribe(TOPIC_ID_BROADCAST);
}

void onDisconnect(DynamicJsonDocument doc)
{
  statusLedThread.setInterval(1500);
}

void syncPinState(DynamicJsonDocument doc)
{
  portO.digitalWrite(PORT_O_1, (int)doc[F("pO1")]);
  portO.digitalWrite(PORT_O_2, (int)doc[F("pO2")]);
  portO.digitalWrite(PORT_O_3, (int)doc[F("pO3")]);
  portO.digitalWrite(PORT_O_4, (int)doc[F("pO4")]);
  portO.digitalWrite(PORT_O_5, (int)doc[F("pO5")]);
  portO.digitalWrite(PORT_O_6, (int)doc[F("pO6")]);
  portO.digitalWrite(PORT_O_7, (int)doc[F("pO7")]);
}

void setup(void)
{
  Serial.begin(115200);
  Serial.println("\r\n\r\nBooting...");

  setupIOs();
  setupWifi();

  events.on("connected", onConnect);
  events.on("disconnected", onDisconnect);
  events.on("updateSw", updateSW);
  events.on("syncPinState", syncPinState);

  mqttClient.setCallback(mqttCallback);
  mqttClient.setServer("broker.mqtt-dashboard.com", 1883);

  statusLedThread.run();
  connectMqttThread.run();
}

void loop(void)
{
  mqttClient.loop();
  statusLedThread.loop();
  connectMqttThread.loop();
}
