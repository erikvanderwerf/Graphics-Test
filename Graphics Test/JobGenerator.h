#pragma once

class Job;

class JobGenerator {
public:
	/** int virtual jobCallback(Job* job)
	 * Returns 1 if the job has been handled.
	 */
	int virtual jobCallback(Job* job) = 0;
};