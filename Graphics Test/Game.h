#pragma once

#include <list>
#include <SFML\Graphics.hpp>
#include <thread>
#include "Commands.h"
#include "Entity.h"
#include "EventHandler.h"
#include "EventListener.h"
#include "GameEvent.h"
#include "Job.h"
#include "Pathfinder.h"
#include "Viewport.h"

class EventHandler;
class Actor;

class Game
{
public:
	Game();
	~Game();
	int start();
	void registerEntity(Entity* entity);
	void registerJob(Job* job);
	void registerThread(Threadable* threadable);
	void fireEvent(GameEvent game_event);
	
	bool volatile running;
	EventHandler* eventhandler;
	std::list<Actor*> actors;
	Viewport viewport;
private:
	class EscapeListener : public EventListener {
	public:
		EscapeListener(Game& parent);
		void virtual fire(GameEvent event);
	private:
		Game& parent;
	};
	class RandomDestination : public EventListener {
	public:
		RandomDestination(Game& parent);
		void virtual fire(GameEvent event);
	private:
		Game& super;
	};

	EscapeListener escapelistener;
	RandomDestination rd;
	Pathfinder pathfinder;
	std::list<Entity*> gameEntities;
	std::vector<Threadable*> threads;
};

