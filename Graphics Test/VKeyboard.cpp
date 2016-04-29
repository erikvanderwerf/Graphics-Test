#include "VKeyboard.h"

#include <iostream>
#include "Job.h"

VKeyboard::VKeyboard()
{
}


VKeyboard::~VKeyboard()
{
}

void VKeyboard::addJob(Job * job)
{
	if (job == nullptr) {
		std::cerr << "NULL Job" << std::endl;
	}

	VKeyboardJobPayload& vkjob = *(VKeyboardJobPayload*)job->deliver;
	keyboard[vkjob.payload.first] = vkjob.payload.second;
	job->complete = true;
}
