#pragma once

class Viewport;

class CommandDrawable
{
public:
	virtual void draw(Viewport* window) = 0;
	virtual sf::FloatRect getBoundingBox() = 0;
};
