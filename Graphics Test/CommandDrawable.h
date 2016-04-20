#pragma once

class Viewport;

class CommandDrawable
{
public:
	//virtual ~CommandDrawable() = 0;
	virtual void draw(Viewport* window) = 0;
	virtual sf::FloatRect getBoundingBox() = 0;
};

