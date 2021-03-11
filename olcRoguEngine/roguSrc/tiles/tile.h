#pragma once
#include "../olcPixelGameEngine.h"
#include "Sprite.h"

namespace rogu
{

	class Tile
	{
	public:
		Tile(std::vector<rogu::Sprite*> tileSprites, int startSprIndex, bool collider = false);

		void update();

		olc::vi2d getSpriteDimensions()
		{
			if (tileSprites.size() <= currentSprIndex) return tileSprites[0]->getSpriteDimensions();
			return tileSprites[currentSprIndex]->getSpriteDimensions();
		}

		inline bool getCollider() { return collider; }

	public:
		bool updated = false;
		bool canUpdate = true;

	private:
		std::vector<rogu::Sprite*> tileSprites;
		float flipFrequency;
		float flip;
		int currentSprIndex = 0;
		bool collider = false;
	};
}