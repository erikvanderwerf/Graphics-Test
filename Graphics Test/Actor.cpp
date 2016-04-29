#define _USE_MATH_DEFINES

#include <iomanip>
#include <iostream>
#include <math.h>

#include "Actor.h"
#include "Pathfinder.h"
#include "VectorUtil.h"

Actor::Actor() :
	display(*this),
	jobs()
{}

Actor::~Actor() {}

void Actor::setPosition(sf::Vector2f position)
{
	coordinate = position;
}

void Actor::setVelocity(sf::Vector2f vel)
{
	velocity = vel;
}

void Actor::bind(Game * game)
{
	this->game = game;
	game->actors.push_back(this);
	game->viewport.addCommandDrawable(&display);
}

int Actor::jobCallback(Job * job)
{
	// If job is complete, handle it.
	if (!job->complete)
		return 0;

	// Determine command within job.
	if ("pathfind" == job->destination) {
		PathfindResponcePayload* resp = (PathfindResponcePayload*)job->responce;
		setPath(resp->payload);
		waiting_path = false;
	}

	// Once job is handled, delete.
	delete job;
	return 1;
}

void Actor::setColor(sf::Color color)
{
	display.setColor(color);
}

void Actor::setPath(std::list<sf::Vector2f> path)
{
	//delete this->path;
	this->path = path;
}

void Actor::tick(float dt)
{
	// Find and process completed jobs
	jobs.erase(std::remove_if(jobs.begin(), jobs.end(),
		[this](Job* job) { return jobCallback(job); })
		, jobs.end());

	sf::Vector2f destination = (path.size() != 0) ? path.front() : sf::Vector2f(0, 1);

	if (path.size() != 0 && sqrt(pow(destination.x - coordinate.x, 2) + pow(destination.y - coordinate.y, 2)) < radius) {
		path.pop_front();
	}

	// Request a new path
	if (!waiting_path && path.size() == 0) {
		Job* pathjob = new Job("pathfind");

		sf::Vector2f ndest = sf::Vector2f();
		ndest.x = (float)(std::rand() % 1000);
		ndest.y = (float)(std::rand() % 1000);
		pathjob->deliver = new PathfindDeliverPayload(ndest);

		jobs.push_back(pathjob);
		game->registerJob(pathjob);
		waiting_path = true;
	}

	// Forces
	// Direction
	sf::Vector2f direction = normalize(destination - coordinate, speed);

	// Avoidance
	std::list<Actor*> close = game->actors;
	sf::Vector2f repulse(0.0f, 0.0f);
	for (Actor* a : close) {
		sf::Vector2f diff = a->coordinate - coordinate;
		if (0.0 != diff.x && 0.0 != diff.y) {
			sf::Vector2f mag = sf::Vector2f(1.0f / diff.x, 1.0f / diff.y);
			repulse -= mag;
		}
	}

	sf::Vector2f force = direction + repulse;
	velocity += force * dt;

	// Limit Velocity
	velocity = maximize(direction, 100);
	coordinate += velocity * dt;
}

Actor::ActorDisplay::ActorDisplay(Actor& parent) : parent(parent) {}

Actor::ActorDisplay::~ActorDisplay() {}

void Actor::ActorDisplay::draw(Viewport* view)
{
	// Position on screen
	float radius = parent.radius * view->zoom;
	sf::Vector2f center = view->transform(parent.coordinate);
	sf::Vector2f pos(center.x - radius, center.y - radius);

	// Actor Circle
	circle.setRadius(radius);
	circle.setFillColor(color);
	circle.setPosition(pos);

	// Velocity Rectangle
	sf::VertexArray vel(sf::LinesStrip, 2);
	vel[0] = center;
	vel[1] = center + normalize(parent.velocity, radius);

	// Destination
	sf::VertexArray dest(sf::LinesStrip);
	dest.append(center);
	for (sf::Vector2f waypoint : parent.path) {
		dest.append(view->transform(waypoint));
	}

	view->window->draw(circle);
	view->window->draw(vel);
	view->window->draw(dest);
}

sf::FloatRect Actor::ActorDisplay::getBoundingBox()
{
	float x = parent.coordinate.x, y = parent.coordinate.y, r = parent.radius;
	return sf::FloatRect(x - r, y - r, r * 2, r * 2);
}

void Actor::ActorDisplay::setColor(sf::Color color) {
	this->color = color;
	circle.setFillColor(color);
}