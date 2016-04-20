#pragma once

#include <SFML\Graphics.hpp>
#include <list>

#include "Entity.h"
#include "EventListener.h"
#include "Threadable.h"

class CommandDrawable;
class Game;

class Viewport: public Entity, public Threadable
{
public:
	Viewport();
	~Viewport();

	bool isOpen();
	void addCommandDrawable(CommandDrawable* command);

	// Entity
	virtual void bind(Game* game);
	virtual void tick(float dt) {};

	// Threadable
	virtual bool isReady();
	virtual void start();
	virtual void stop();
	
	sf::RenderWindow* window;
	sf::Vector2f display_ul; // Upper-left
	sf::Vector2f display_c; // Center
	float zoom = 1;
private:
	class PanDisplay : public EventListener, public Entity {
	public:
		PanDisplay(Viewport& parent);
		void virtual bind(Game* game);
		void virtual fire(GameEvent event);
		void virtual tick(float dt);
	private:
		const float speed = 200;
		const float zoom_speed = 1.125;
		Viewport& super;
		float dx, dy;
	};

	bool volatile ready = false;
	Game* game;
	sf::FloatRect viewbounds;
	std::list<CommandDrawable*> display;
	PanDisplay pan;
};

