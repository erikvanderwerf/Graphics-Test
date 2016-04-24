#pragma once

#include <SFML\Graphics.hpp>
#include <list>


class JobPayload {};

template<typename T>
class JPT : public JobPayload {
public:
	JPT(T p) { payload = p; };

	T payload;
};

typedef JPT<sf::Vector2f>				PathfindDeliverPayload;
typedef JPT<std::list<sf::Vector2f>>	PathfindResponcePayload;