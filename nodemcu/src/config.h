#ifndef CONFIG_H
#define CONFIG_H

// #define SW_VERSION (from build script)
#include <PortExpander_I2C.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <EventHandler.h>

#define WIFI_SSID "Vargaski"
#define WIFI_PASS "12345678"

#define TOPIC_ID "ngkKzLHfUh@"
#define TOPIC_ID_BROADCAST "ngkKzLHfUh@broadcast"

#define SERVER_URL "192.168.18.115"
#define SERVER_PORT 3333

// Pins Mapping
#define PORT_O_1 3
#define PORT_O_2 6
#define PORT_O_3 5
#define PORT_O_4 4
#define PORT_O_5 0
#define PORT_O_6 1
#define PORT_O_7 2
#define PORT_O_8 7

#define PORT_I_INTERRUPT 5
#define PORT_I_1 0
#define PORT_I_2 1
#define PORT_I_3 2
#define PORT_I_4 3
#define PORT_I_5 4
#define PORT_I_6 5
#define PORT_I_7 6
#define PORT_I_8 7

// Global class instances

PortExpander_I2C portO(0x27);
PortExpander_I2C portI(0x26);

WiFiClient espClient;
PubSubClient mqttClient(espClient);
EventHandler events;

#endif