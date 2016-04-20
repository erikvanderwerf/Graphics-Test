#include <iostream>

#include "Game.h"
#include "Pathfinder.h"

Pathfinder::Pathfinder()
{
}


Pathfinder::~Pathfinder()
{
}

void Pathfinder::addJob(Job * job)
{
	std::lock_guard<std::mutex> lock(m);

	if (job == nullptr) {
		std::cerr << "NULL Job" << std::endl;
	}

	jobs.push(job);

	cv.notify_one();
}

void Pathfinder::bind(Game * game)
{
	game->registerThread(this);
}

bool Pathfinder::isReady()
{
	return true;
}

void Pathfinder::start()
{
	running = true;
	Job* job;
	while (running) {
		std::unique_lock<std::mutex> lock(m);
		cv.wait(lock, [this]() {return !(jobs.empty() && running); });

		if (jobs.empty())
			continue;

		job = jobs.front();
		jobs.pop();
		lock.unlock();

		// Complete Job
		sf::Vector2f* ndest = new sf::Vector2f();
		ndest->x = (float)(std::rand() % 10000);
		ndest->y = (float)(std::rand() % 10000);
		
		job->responce.first = sizeof(sf::Vector2f);
		job->responce.second = ndest;
		job->complete = true;

	}
}

void Pathfinder::stop()
{
	running = false;
	cv.notify_one();
}
