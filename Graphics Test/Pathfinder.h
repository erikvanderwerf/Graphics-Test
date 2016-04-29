#pragma once

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#include <queue>

#include "Entity.h"
#include "JobPayload.h"
#include "Threadable.h"

class Game;
class Job;

typedef JobPayload<sf::Vector2f> PathfindDeliverPayload;
typedef JobPayload<std::list<sf::Vector2f>>	PathfindResponcePayload;

class Pathfinder :
	public Entity,
	public Threadable
{
public:
	Pathfinder();
	~Pathfinder();

	void addJob(Job *job);

	// Entity
	virtual void bind(Game* game);
	virtual void tick(float dt) {};

	// Threadable
	virtual bool isReady();
	virtual void start();
	virtual void stop();

private:
	bool volatile running;
	std::queue<Job*> jobs;

	std::mutex m;
	std::condition_variable cv;
};
