#ifndef __EVENT_HUB_H__
#define __EVENT_HUB_H__

#include <Arduino.h>
#include <ArduinoJson.h>
#include <map>
#include <vector>

#define EventHandlerDEBUG(...) Serial.printf(__VA_ARGS__);

class EventHandler
{
private:
	std::map<String, std::function<void(DynamicJsonDocument doc)>> _events;

public:
	void dispatch(const char *event, DynamicJsonDocument doc);
	void on(const char *event, std::function<void(DynamicJsonDocument doc)> func);
};

#endif
