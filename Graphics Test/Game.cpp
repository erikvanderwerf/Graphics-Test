#include "Game.h"
#include <ctime>
#include <chrono>
#include <iostream>
#include <random>

#include "Actor.h"
#include "Pathfinder.h"

Game::Game() : escapelistener(*this), rd(*this)
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
	Actor* a;
	const int spd_rng = 200;
	const int dest_rng = 10000;

	Actor * actors = new Actor[100000];

	for (int i = 0; i < 100000; i++) {
		if (!(i % 100))
			std::cout << i << std::endl;
		int x, y, vx, vy, r, g, b;
		x = 0;// std::rand() % dest_rng;
		y = 0;// std::rand() % dest_rng;
		vx = 0;//std::rand() % dest_rng;
		vy = 0;// std::rand() % dest_rng;

		r = (1*i) % 255;
		g = (3*i) % 255;
		b = (5*i) % 255;

		a = &actors[i];
		a->setColor(sf::Color(r,g,b));
		a->setPosition(sf::Vector2f((float)x, (float)y));
		a->setDestination(sf::Vector2f((float)vx, (float)vy));

		registerEntity(a);
	}
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
			e->tick((float)(1.0 / 60));
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

Game::RandomDestination::RandomDestination(Game & parent) : super(parent) {}

void Game::RandomDestination::fire(GameEvent event)
{
	int vx, vy, dest_rng = 800;
	for (Actor* a: super.actors) {
		vx = std::rand() % dest_rng;
		vy = std::rand() % dest_rng;
		a->setDestination(sf::Vector2f((float)vx, (float)vy));
	}
}
