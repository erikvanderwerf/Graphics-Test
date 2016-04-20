#pragma once
#include <SFML\Graphics.hpp>

#include "JobPayload.h"

class PathfindPayload :
	public JobPayload
{
public:
	PathfindPayload();
	virtual ~PathfindPayload();

	sf::Vector2f payload;
};

