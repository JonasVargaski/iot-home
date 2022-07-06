#include <EventHandler.h>

void EventHandler::dispatch(const char *event, DynamicJsonDocument doc)
{
	auto e = _events.find(event);
	if (e != _events.end())
	{
		EventHandlerDEBUG("[EVENTS] dispatch event %s\n", event);
		e->second(doc);
	}
	else
	{
		EventHandlerDEBUG("[EVENTS] event [%s] not found. %d events available\n", event, _events.size());
	}
}

void EventHandler::on(const char *event, std::function<void( DynamicJsonDocument doc)> func)
{
	_events[event] = func;
	EventHandlerDEBUG("[EVENTS] listening event %s\n", event);
}
