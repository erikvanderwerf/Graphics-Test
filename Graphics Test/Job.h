#pragma once

#include <string>

//#include "JobPayload.h"

class JobPayload;

class Job
{
public:
	Job(std::string const command);
	~Job();

	bool volatile complete;
	std::string command;

	JobPayload *deliver, *responce;
};
