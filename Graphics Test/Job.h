#pragma once

#include <string>

#include "Entity.h"
#include "JobPayload.h"

class Job
{
public:
	Job(std::string const command);
	~Job();

	bool volatile complete;
	std::string command;

	//JobGenerator* origin;
	JobPayload *deliver, *responce;
};

