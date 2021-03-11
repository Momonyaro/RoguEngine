#pragma once
#include "entity.h"

class EntityManager
{
public:
	~EntityManager()
	{
		player->~Entity();
	}

	inline Entity* getPlayer() { return player; }
	void setPlayer(Entity* playerEntity) { player = playerEntity; }

private:
	Entity* player = new Entity("Player", { 1, 1 }, new rogu::Sprite({ 15, 0 }), 10, 10, 1);
};