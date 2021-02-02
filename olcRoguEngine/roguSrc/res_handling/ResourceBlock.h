#pragma once
#include <iostream>
#include "../tiles/tile.h"

namespace rogu
{
	class ResourceBlock
	{
	public:
		ResourceBlock(std::string key, rogu::Tile* tile)
		{
			this->key = key;
			this->tile = tile;
		}

		bool tryKey(std::string key)
		{
			return (this->key == key);
		}

		rogu::Tile* getTile()
		{
			return tile;
		}

	private:
		rogu::Tile* tile;
		std::string key;
	};
}