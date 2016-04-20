#pragma once

#include <thread>

/** Threadable
 * This is an interface for any objects that can (and should) be placed in
 * their own thread.
 */
class Threadable {
public:
	virtual bool isReady() = 0;
	virtual void start() = 0;
	virtual void stop() = 0;
	std::thread thread;
};