#ifndef TIMEDACTION_H
#define TIMEDACTION_H

#include "arduino.h"

#define NO_PREDELAY 0

class Thread
{
public:
	Thread(unsigned long interval, void (*function)());
	Thread(void (*function)());

	void stop();
	void run();
	void loop();

	void setInterval(unsigned long interval);
	void setTimeout(unsigned long interval);

private:
	bool _hasTimeout;
	bool _active;
	unsigned long _previous;
	unsigned long _interval;
	void (*_execute)();
};

#endif
