#pragma once
#include "../olcPixelGameEngine.h"
#include "Sprite.h"

namespace rogu
{

	class Tile
	{
	public:
		Tile(std::vector<rogu::Sprite*> tileSprites, int startSprIndex);

		void update();

		olc::vi2d getSpriteDimensions()
		{
			if (tileSprites.size() <= currentSprIndex) return tileSprites[0]->getSpriteDimensions();
			return tileSprites[currentSprIndex]->getSpriteDimensions();
		}

	public:
		bool updated = false;
		bool canUpdate = true;

	private:
		std::vector<rogu::Sprite*> tileSprites;
		float flipFrequency;
		float flip;
		int currentSprIndex = 0;
	};
}