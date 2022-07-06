#include "Thread.h"

Thread::Thread(unsigned long interval, void (*function)())
{
	_hasTimeout = false;
	_active = true;
	_previous = millis();
	_interval = interval;
	_execute = function;
}

Thread::Thread(void (*function)())
{
	_hasTimeout = false;
	_active = false;
	_previous = millis();
	_interval = 0;
	_execute = function;
}

void Thread::stop()
{
	_previous = 0;
	_active = false;
}

void Thread::run()
{
	if (!_active && _interval > 0)
	{
		_previous = millis();
		_active = true;
	}
}

void Thread::loop()
{
	if (!_active)
		return;

	if (millis() - _previous >= _interval)
	{
		_previous = millis();
		_execute();

		if (_hasTimeout)
			stop();
	}
}

void Thread::setInterval(unsigned long interval)
{
	_interval = interval;
	_hasTimeout = false;
}

void Thread::setTimeout(unsigned long interval)
{
	_interval = interval;
	_hasTimeout = true;
}