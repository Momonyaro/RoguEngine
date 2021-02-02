#pragma once
#include <vector>
#include "../olcPixelGameEngine.h"
#include "../tiles/tile.h"

namespace rogu
{
	enum class BorderType
	{
		BORDER_NONE = 0,
		BORDER_FULL = 1,
		BORDER_TOP = 2,
		BORDER_RIGHT = 3,
		BORDER_BOTTOM = 4,
		BORDER_LEFT = 5,
		BORDER_TOP_RIGHT = 6,
		BORDER_RIGHT_BOTTOM = 7,
		BORDER_BOTTOM_LEFT = 8,
		BORDER_LEFT_TOP = 9
	};

	class BoardRenderer
	{
	public:
		BoardRenderer(int width, int height, rogu::Tile* initTile, int size);

		void init();

		void updateBoard();

		void writeToBufferScreenPos(rogu::Tile* tile, int x, int y);
		void writeToBufferTilePos(rogu::Tile* tile, int x, int y);
		void writeToAllEmpty(rogu::Tile* tile);
		void writeToAll(rogu::Tile* tile);
		void writeToArea(int x, int y, int w, int h, rogu::Tile* tile);
		void writeTextToArea(int x, int y, int overflowWidth, std::vector<rogu::Tile*> tiles);

		void drawPanel(int x, int y, int w, int h, int thickness, rogu::Tile* background, rogu::Tile* border, rogu::BorderType type);

		rogu::Tile* getTileInBuffer(int x, int y)
		{
			return boardTiles[y * boardWidth + x];
		}

		std::vector<rogu::Tile*> getAllTilesInBuffer() { return boardTiles; }

		olc::vi2d getBoardDimensions() { return olc::vi2d(boardWidth, boardHeight); }
		olc::vi2d getScreenOffset() { return olc::vi2d(screenXOffset, screenYOffset); }

	private:
		std::vector<rogu::Tile*> boardTiles;
		int boardWidth;
		int boardHeight;
		int screenXOffset;
		int screenYOffset;
		int tileSize;
	};
}