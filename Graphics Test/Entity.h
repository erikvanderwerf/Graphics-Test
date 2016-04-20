#pragma once

class Game;

class Entity
{
public:
	virtual void bind(Game* game) = 0;
	virtual void tick(float dt) = 0;
protected:
	Game* game;
private:
};
