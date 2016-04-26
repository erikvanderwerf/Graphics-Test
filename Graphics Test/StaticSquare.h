#pragma once

#include <SFML\Graphics.hpp>

#include "CommandDrawable.h"
#include "StaticObstacle.h"

class Viewport;

class StaticSquare :
	public StaticObstacle
{
public:
	StaticSquare(sf::Vector2f begin, sf::Vector2f end);
	~StaticSquare();

	virtual void bind(Game* game);
	virtual void tick(float dt) {};

private:
	class SQDisplay :
		public CommandDrawable {
	public:
		SQDisplay(StaticSquare& parent);
		virtual void draw(Viewport* window);
		virtual sf::FloatRect getBoundingBox();
	private:
		StaticSquare& parent;
	};

	SQDisplay display;
	sf::FloatRect square;
};

