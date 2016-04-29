#pragma once

#include <SFML\Graphics.hpp>
#include <list>

class JobSkeleton {};

template<typename T>
class JobPayload : public JobSkeleton {
public:
	JobPayload(T p) { payload = p; };

	T payload;
};