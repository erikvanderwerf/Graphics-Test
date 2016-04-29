#include "Job.h"

#include <iostream>

Job::Job(std::string const command) :
	deliver(nullptr),
	responce(nullptr)
{
	this->destination = command;
	complete = false;
}

Job::~Job()
{
	delete deliver;
	delete responce;
}