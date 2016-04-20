#include "EventHandler.h"


void EventHandler::bind(Game* game) {
	this->game = game;
}


void EventHandler::fire(GameEvent event)
{
	std::map<sf::Keyboard::Key, std::list<EventListener*>>::iterator find;

	if (event.type == sf::Event::Closed) {
		game->running = false;
		return;
	}
	else if (event.type == sf::Event::KeyPressed) {
		find = keyPressedListeners.find(event.key.code);
		if (find == keyPressedListeners.end()) { return; }
	}
	else if (event.type == sf::Event::KeyReleased) {
		find = keyReleasedListeners.find(event.key.code);
		if (find == keyReleasedListeners.end()) { return; }
	}
	else if (event.type == sf::Event::Resized) {
		game->viewport.window->setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
		return;
	}
	else {
		return;
	}

	// Fire all events
	for (EventListener* el : find->second) {
		el->fire(event);
	}
}

void EventHandler::registerKeyPressedListener(sf::Keyboard::Key key, EventListener * listener)
{
	std::list<EventListener*>* list = &keyPressedListeners[key];
	list->push_back(listener);
}

void EventHandler::registerKeyReleasedListener(sf::Keyboard::Key key, EventListener * listener)
{
	std::list<EventListener*>* list = &keyReleasedListeners[key];
	list->push_back(listener);
}