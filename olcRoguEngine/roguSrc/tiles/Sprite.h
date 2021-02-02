#pragma once
#include "../olcPixelGameEngine.h"

namespace rogu
{
	class Sprite
	{
	public:
		Sprite(olc::vi2d spriteCutoutPos)
		{
			spriteDimensions = spriteCutoutPos;
		}

		inline olc::vi2d getSpriteDimensions()
		{
			return spriteDimensions;
		}

	private:
		olc::vi2d spriteDimensions;
	};
}