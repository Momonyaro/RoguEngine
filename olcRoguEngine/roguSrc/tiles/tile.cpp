#include "tile.h"

namespace rogu
{

	Tile::Tile(std::vector<rogu::Sprite*> tileSprites, int startSprIndex)
	{
		Tile::tileSprites = tileSprites;
		currentSprIndex = startSprIndex;
		canUpdate = (tileSprites.size() > 1);
	}

	void Tile::update()
	{
		if (updated || !canUpdate)
			return;

		currentSprIndex++;

		if (currentSprIndex >= tileSprites.size())
		{
			currentSprIndex = 0;
		}
		updated = true;
	}

}