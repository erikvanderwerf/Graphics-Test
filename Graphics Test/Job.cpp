#include "Job.h"



Job::Job(std::string const command) : 
	deliver(0, nullptr),
	responce(0, nullptr)
{
	this->command = command;
	complete = false;
}


Job::~Job()
{
}
