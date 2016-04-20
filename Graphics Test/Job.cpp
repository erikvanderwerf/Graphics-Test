#include "Job.h"

Job::Job(std::string const command)
{
	this->command = command;
	complete = false;
}


Job::~Job()
{
	delete deliver;
	delete responce;
}
