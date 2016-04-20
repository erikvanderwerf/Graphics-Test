#pragma once
#include "GameEvent.h"

//class GameEvent;

class EventListener
{
public:
	//EventListener();
	//~EventListener();
	void virtual fire(GameEvent event) = 0;
};

