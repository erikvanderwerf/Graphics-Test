#include "Viewport.h"

#include "Game.h"

#include <iostream>

Viewport::Viewport(): pan(*this)
{
}


Viewport::~Viewport()
{
	if (window != nullptr) {
		window->close();
	}
}


bool Viewport::isOpen()
{
	return window->isOpen();
}


bool Viewport::isReady()
{
	return ready;
}


void Viewport::bind(Game * game)
{
	this->game = game;
	game->registerThread(this);
	game->registerEntity(&pan);
}


void Viewport::stop()
{
	ready = false;
}


void Viewport::start()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 800), "Game");
	window->setFramerateLimit(60);
	window->setActive(false);

	ready = true;

	while (game->running) {
		// Events
		sf::Event event;
		while (window->pollEvent(event)) {
			game->fireEvent(event);
		}

		// Set View bounds
		sf::Vector2u pixels = window->getSize();
		display_ul = display_c - sf::Vector2f(pixels.x / zoom / 2, pixels.y / zoom / 2);
		viewbounds = sf::FloatRect(display_ul.x, display_ul.y, pixels.x / zoom, pixels.y / zoom);

		// Drawing
		window->clear();
		for (CommandDrawable* d : display) {
			if (viewbounds.intersects(d->getBoundingBox())) {
				d->draw(this);
			}
		}

		window->display();
	}
	window->close();
}


void Viewport::addCommandDrawable(CommandDrawable * command)
{
	display.push_back(command);
}

sf::Vector2f Viewport::transform(sf::Vector2f input)
{
	float x = zoom * (input.x - display_ul.x);
	float y = zoom * (input.y - display_ul.y);
	return sf::Vector2f(x, y);
}


Viewport::PanDisplay::PanDisplay(Viewport & super) : super(super) {
}


void Viewport::PanDisplay::bind(Game * game)
{
	game->eventhandler->registerKeyPressedListener(sf::Keyboard::W, this);
	game->eventhandler->registerKeyPressedListener(sf::Keyboard::S, this);
	game->eventhandler->registerKeyPressedListener(sf::Keyboard::A, this);
	game->eventhandler->registerKeyPressedListener(sf::Keyboard::D, this);
	game->eventhandler->registerKeyPressedListener(sf::Keyboard::Add, this);
	game->eventhandler->registerKeyPressedListener(sf::Keyboard::Subtract, this);

	game->eventhandler->registerKeyReleasedListener(sf::Keyboard::W, this);
	game->eventhandler->registerKeyReleasedListener(sf::Keyboard::S, this);
	game->eventhandler->registerKeyReleasedListener(sf::Keyboard::A, this);
	game->eventhandler->registerKeyReleasedListener(sf::Keyboard::D, this);
}


void Viewport::PanDisplay::fire(GameEvent event)
{
	float amount;
	switch (event.type) {
	case sf::Event::KeyPressed:
		amount = speed;
		break;
	case sf::Event::KeyReleased:
		amount = 0;
		break;
	default:
		return;
	}
	switch (event.key.code) {
	case sf::Keyboard::W:
		dy = -amount;
		break;
	case sf::Keyboard::A:
		dx = -amount;
		break;
	case sf::Keyboard::S:
		dy = amount;
		break;
	case sf::Keyboard::D:
		dx = amount;
		break;
	case sf::Keyboard::Add:
		super.zoom *= zoom_speed;
		break;
	case sf::Keyboard::Subtract:
		super.zoom /= zoom_speed;
		break;
	default:
		break;
	}
}


void Viewport::PanDisplay::tick(float dt)
{
	super.display_c += sf::Vector2f(dx / super.zoom * dt, dy / super.zoom * dt);
}
