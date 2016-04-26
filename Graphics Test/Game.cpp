#include "Game.h"
#include <ctime>
#include <chrono>
#include <iostream>
#include <random>

#include "Actor.h"
#include "StaticSquare.h"
#include "Pathfinder.h"

Game::Game() : 
	escapelistener(*this)
{
	// Event Handler
	eventhandler = new EventHandler();
	eventhandler->bind(this);
	// Pathfinder
	registerEntity(&pathfinder);
	// Viewport
	registerEntity(&viewport);

	// Default Actors, remove later
	std::cerr << "Generating" << std::endl;
	const int num_actors = 50;

	Actor * a;
	Actor * actors = new Actor[num_actors];

	for (int i = 0; i < num_actors; i++) {
		if (!(i % 100)) std::cout << i << std::endl;
		int r, g, b;

		r = (67 * i) % 255;
		g = (73 * i) % 255;
		b = (83 * i) % 255;

		a = &actors[i];
		//a->setPosition(sf::Vector2f(r, g));
		a->setColor(sf::Color(r, g, b));

		registerEntity(a);
	}

	// Default Obstacle, remove later
	StaticSquare* sq2 = new StaticSquare(sf::Vector2f(400, 400), sf::Vector2f(600, 600));
	registerEntity(sq2);
}

Game::~Game()
{
	for (Entity* e : gameEntities) {
		//e->~Entity();
	}
}

int Game::start()
{
	running = true;

	eventhandler->registerKeyPressedListener(sf::Keyboard::Escape, &escapelistener);

	// Set up threads.
	for (Threadable * t : threads)
		t->thread = std::thread(&Threadable::start, t);
	for (Threadable * t : threads) { // Wait for each thread to be ready
		while (!t->isReady()) {}
	}

	while (running)
	{
		auto start = std::chrono::system_clock::now();

		for (Entity* e : gameEntities) {
			e->tick((float)(1.0 / 60.0));
		}

		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
		//std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
	}

	// Shutdown and join threads.
	for (Threadable * t : threads)
		t->stop();
	for (Threadable * t : threads)
		t->thread.join();

	return 0;
}

void Game::registerEntity(Entity * entity)
{
	gameEntities.push_back(entity);
	entity->bind(this);
}

void Game::registerJob(Job *job)
{
	pathfinder.addJob(job);
}

void Game::registerThread(Threadable * threadable)
{
	threads.push_back(threadable);
}

void Game::fireEvent(GameEvent game_event)
{
	eventhandler->fire(game_event);
}

Game::EscapeListener::EscapeListener(Game & parent) : parent(parent) {}

void Game::EscapeListener::fire(GameEvent event)
{
	parent.running = false;
}