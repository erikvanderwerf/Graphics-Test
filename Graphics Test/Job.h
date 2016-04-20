#pragma once

#include <string>

#include "Entity.h"
#include "JobGenerator.h"

//class JobGenerator;

class Job
{
public:
	Job(std::string const command);
	~Job();

	bool volatile complete;
	std::string command;

	//JobGenerator* origin;
	std::pair<long, void*> deliver, responce;
};

