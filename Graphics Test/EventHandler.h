#pragma once

#include<SFML\Graphics.hpp>

#include <list>
#include <map>
#include "GameEvent.h"
#include "Game.h"

class Game;
class EventListener;

class EventHandler
{
public:
	void bind(Game* game);
	void fire(GameEvent event);
	void registerKeyPressedListener(sf::Keyboard::Key key, EventListener* listener);
	void registerKeyReleasedListener(sf::Keyboard::Key key, EventListener* listener);
private:
	Game* game; // TODO Remove later when more comprehensive events are implemented.
	std::map<sf::Keyboard::Key, std::list<EventListener*>> keyPressedListeners;
	std::map<sf::Keyboard::Key, std::list<EventListener*>> keyReleasedListeners;
};

