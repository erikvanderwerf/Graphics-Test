#pragma once

#include <string>

class JobSkeleton;

/**
 * A job is an asynchronous task that is dispatched to the proper job handler
 * when registered. The complete flag is set once the relevent computation
 * has been performed.
 */
class Job
{
public:
	Job(std::string const command);
	~Job();

	bool volatile complete;
	std::string destination;

	JobSkeleton *deliver, *responce;
};
