#pragma once
#include <SFML\Graphics.hpp>

#include <list>

#include "JobPayload.h"

class PathfindResponcePayload :
	public JobPayload
{
public:
	virtual ~PathfindResponcePayload();

	std::list<sf::Vector2f> payload;
};

PathfindResponcePayload::~PathfindResponcePayload()
{
}
