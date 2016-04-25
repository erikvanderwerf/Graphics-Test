#include <iostream>

#include "Pathfinder.h"
#include "JobPayload.h"
#include "Game.h"

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
		PathfindDeliverPayload& deliver = *((PathfindDeliverPayload*)job->deliver);

		std::list<sf::Vector2f> path;
		//path.push_back(sf::Vector2f(500,500));
		path.push_back(deliver.payload);

		job->responce = new PathfindResponcePayload(path);
		PathfindResponcePayload* responce = (PathfindResponcePayload*)job->responce;

		job->complete = true;
	}
}

void Pathfinder::stop()
{
	running = false;
	cv.notify_one();
}