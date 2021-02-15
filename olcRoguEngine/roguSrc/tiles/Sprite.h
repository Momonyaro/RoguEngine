#pragma once
#include "../olcPixelGameEngine.h"

namespace rogu
{
	class Sprite
	{
	public:
		Sprite(olc::vi2d spriteCutoutPos, olc::Pixel tint = olc::WHITE)
		{
			spriteDimensions = spriteCutoutPos;
			spriteTint = tint;
		}

		inline olc::vi2d getSpriteDimensions()
		{
			return spriteDimensions;
		}

		inline olc::Pixel getSpriteTint()
		{
			return spriteTint;
		}

	private:
		olc::vi2d spriteDimensions;
		olc::Pixel spriteTint;
	};
}