#pragma once
#include <SFML\Graphics.hpp>

#include <list>

#include "JobPayload.h"

class PathfindPayload :
	public JobPayload
{
public:
	virtual ~PathfindPayload();

	std::list<sf::Vector2f> payload;
};

