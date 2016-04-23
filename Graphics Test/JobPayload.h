#pragma once

#include <SFML\Graphics.hpp>

class JobPayload
{
public:
	virtual ~JobPayload() {};
};

class PayloadDeliverPayload :
	public JobPayload
{
public:
	PayloadDeliverPayload(sf::Vector2f payload) { this->payload = payload; };
	//virtual ~PathfindPayload();

	sf::Vector2f payload;
};