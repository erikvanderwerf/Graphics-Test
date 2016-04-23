#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>

#include "Actor.h"
#include "PathfindPayload.h"

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
	if ("pathfind" == job->command) {
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
	jobs.erase(std::remove_if(jobs.begin(), jobs.end(),
		[&](Job* job) { return jobCallback(job); })
	, jobs.end());

	sf::Vector2f destination = (path.size() != 0)? path.front(): sf::Vector2f(0,1);

	if (path.size() != 0 && sqrt(pow(destination.x - coordinate.x, 2) + pow(destination.y - coordinate.y, 2)) < 5) {
		path.pop_front();
	}

	if (!waiting_path && path.size() == 0) {
		Job* pathjob = new Job("pathfind");
		
		sf::Vector2f ndest = sf::Vector2f();
		ndest.x = (float)(std::rand() % 10000);
		ndest.y = (float)(std::rand() % 10000);
		pathjob->deliver = new PayloadDeliverPayload(ndest);

		jobs.push_back(pathjob);
		game->registerJob(pathjob);
		waiting_path = true;
	}

	//velocity.x = (float)(-(coordinate.x - destination.x) / 0.5);
	//velocity.y = (float)(-(coordinate.y - destination.y) / 0.5);

	sf::Vector2f d = destination - coordinate;
	velocity = d / (float)(1.0/100.0 * sqrt(pow(d.x, 2) + pow(d.y, 2)));

	coordinate.x += velocity.x * dt;
	coordinate.y += velocity.y * dt;
}

Actor::ActorDisplay::ActorDisplay(Actor& parent) : parent(parent), rect(sf::Vector2f(25, 5)) {}

Actor::ActorDisplay::~ActorDisplay() {}

void Actor::ActorDisplay::draw(Viewport* view)
{
	float x = view->zoom * (parent.coordinate.x - view->display_ul.x);
	float y = view->zoom * (parent.coordinate.y - view->display_ul.y);
	float radius = parent.radius * view->zoom;

	circle.setRadius(radius);
	circle.setFillColor(color);
	circle.setPosition(x, y);

	rect.setScale(view->zoom, view->zoom);
	rect.setPosition(x + radius , y + radius);
	rect.setRotation((float)(atan2f(parent.velocity.y, parent.velocity.x) * 180 / M_PI));

	view->window->draw(circle);
	view->window->draw(rect);
}

sf::FloatRect Actor::ActorDisplay::getBoundingBox()
{
	return sf::FloatRect(parent.coordinate.x, parent.coordinate.y, parent.radius * 2, parent.radius * 2);
}

void Actor::ActorDisplay::setColor(sf::Color color) {
	this->color = color;
}