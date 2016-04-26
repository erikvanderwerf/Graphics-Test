#pragma once

#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Entity.h"

class CommandDrawable;
class Entity;
class Game;
class Viewport;

class Actor :
	public Entity
{
public:
	Actor();
	~Actor();

	// Entity
	void virtual bind(Game* game);
	void virtual tick(float dT);

	// JobGenerator
	int virtual jobCallback(Job* job);

	void setColor(sf::Color color);
	void setPath(std::list<sf::Vector2f> path);
	void setPosition(sf::Vector2f position);
	void setVelocity(sf::Vector2f vel);
private:
	class ActorDisplay : public CommandDrawable {
	public:
		ActorDisplay(Actor& parent);
		virtual ~ActorDisplay();
		virtual void draw(Viewport* view);
		virtual sf::FloatRect getBoundingBox();
		void setColor(sf::Color color);
	private:
		Actor& parent;
		sf::CircleShape circle;
		sf::Color color;
	};

	ActorDisplay display;
	bool waiting_path;
	float radius = 25.f;
	float speed = 50;
	sf::Vector2f coordinate;
	std::list<sf::Vector2f> path;
	sf::Vector2f velocity;
	std::vector<Job*> jobs;
};
