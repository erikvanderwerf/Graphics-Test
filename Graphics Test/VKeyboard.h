#pragma once

#include <cstdint>
#include "JobPayload.h"

class Job;

typedef JobPayload<std::pair<int, uint8_t>> VKeyboardJobPayload;

/**
 * A virtual keyboard, with bytes for the value of each key/axis. Up to 1024
 * bindings can be defined.
 *
 * Potentially change to vector for variable amount of bindings.
*/
class VKeyboard
{
public:
	VKeyboard();
	~VKeyboard();

	// Constants
	static const int MAX_VALUE = UINT8_MAX;
	static const int MIN_VALUE = 0;

	// Functions
	void addJob(Job* job);
	uint8_t getKey(int index) { return keyboard[index]; };

private:
	uint8_t keyboard[1024] = { 0 };
};

