#include "StaticSquare.h"

#include "Game.h"

StaticSquare::StaticSquare(sf::Vector2f begin, sf::Vector2f end) :
	square(begin, end - begin),
	display(*this)
{
}


StaticSquare::~StaticSquare()
{
}

void StaticSquare::bind(Game * game)
{
	this->game = game;
	game->viewport.addCommandDrawable(&display);
}

StaticSquare::SQDisplay::SQDisplay(StaticSquare & p) :
	parent(p)
{
}

void StaticSquare::SQDisplay::draw(Viewport * window)
{
	sf::Vector2f position = window->transform(sf::Vector2f(parent.square.left, parent.square.top));
	sf::Vector2f wh = sf::Vector2f(parent.square.width, parent.square.height) * window->zoom;
	sf::RectangleShape rectangle(wh);
	rectangle.setPosition(position);
	window->window->draw(rectangle);
}

sf::FloatRect StaticSquare::SQDisplay::getBoundingBox()
{
	sf::FloatRect square = parent.square;
	return sf::FloatRect(square.left, square.top, square.width, square.height);
}
