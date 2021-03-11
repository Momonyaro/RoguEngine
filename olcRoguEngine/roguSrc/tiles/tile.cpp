#include "tile.h"

namespace rogu
{

	Tile::Tile(std::vector<rogu::Sprite*> tileSprites, int startSprIndex, bool collider)
	{
		Tile::tileSprites = tileSprites;
		Tile::currentSprIndex = startSprIndex;
		Tile::canUpdate = (tileSprites.size() > 1);
		Tile::collider = collider;
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