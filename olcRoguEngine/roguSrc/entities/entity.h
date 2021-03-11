#pragma once
#include "../olcPixelGameEngine.h"
#include "../tiles/Sprite.h"

class Entity
{
public:
	Entity()
	{
		sName = "Entity";
		vPos = {0, 0};
		sprite = new rogu::Sprite({0, 8});
		nHealth = 10;
		nMaxHealth = 10;
		nLevel = 1;
		nXp = 0;
	}

	Entity(std::string name, olc::vi2d pos, rogu::Sprite* spr, int health, int maxHealth, int level)
	{
		sName = name;
		vPos = pos;
		sprite = spr;
		nHealth = health;
		nMaxHealth = maxHealth;
		nLevel = level;
		nXp = 0;
	}

	~Entity()
	{
		//I am really unfamiliar with using destructors but I think this ought to work?
		delete[] & vPos;
		delete[] sprite;
		//delete[] & nHealth;
		//delete[] & nMaxHealth;
		//delete[] & nLevel;
		//delete[] & nXp;
	}

	void move(int x, int y)
	{
		vPos += { x, y };
	}

	void setPosition(int x, int y)
	{
		vPos = { x, y };
	}

	inline olc::vi2d getPosition() { return vPos; }
	inline rogu::Sprite* getSprite() { return sprite; }
	inline int getCurrentHealth() { return nHealth; }
	inline int getMaxHealth() { return nMaxHealth; }

private:
	olc::vi2d vPos;
	rogu::Sprite* sprite;
	std::string sName;
	int nHealth;
	int nMaxHealth;
	int nLevel;
	int nXp;
};