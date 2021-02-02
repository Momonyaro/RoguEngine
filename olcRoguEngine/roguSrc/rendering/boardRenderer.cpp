#include "boardRenderer.h"

namespace rogu
{

	BoardRenderer::BoardRenderer(int width, int height, rogu::Tile* initTile, int size)
	{
		boardTiles = std::vector<rogu::Tile*>(width * height);

		boardWidth = width;
		boardHeight = height;
		tileSize = size;

		for (int i = 0; i < boardTiles.size(); i++)
		{
			boardTiles[i] = initTile;
		}
	}

	void BoardRenderer::updateBoard()
	{
		for (int i = 0; i < boardTiles.size(); i++)
		{
			if (boardTiles[i] == nullptr || !boardTiles[i]->canUpdate) continue;
			boardTiles[i]->update();
		}
	}

	void BoardRenderer::writeToAllEmpty(rogu::Tile* tile)
	{
		for (int i = 0; i < boardTiles.size(); i++)
		{
			if (boardTiles[i] == nullptr)
				boardTiles[i] = tile;
		}
	}

	void BoardRenderer::writeToAll(rogu::Tile* tile)
	{
		for (int i = 0; i < boardTiles.size(); i++)
		{
			boardTiles[i] = tile;
		}
	}

	void BoardRenderer::writeToArea(int x, int y, int w, int h, rogu::Tile* tile)
	{
		for (int q = y; q < y + h; q++)
			for (int p = x; p < x + w; p++)
			{
				boardTiles[q * boardWidth + p] = tile;
			}
	}

	void BoardRenderer::writeTextToArea(int x, int y, int overflowWidth, std::vector<rogu::Tile*> tiles)
	{
		int xPos = x;
		int yPos = y;
		for (int i = 0; i < tiles.size(); i++)
		{
			if (xPos >= x + overflowWidth)
			{
				yPos++;
				xPos = x;
			}
			writeToBufferTilePos(tiles[i], xPos, yPos);
			xPos++;
		}
	}

	void BoardRenderer::drawPanel(int x, int y, int w, int h, int thickness, rogu::Tile* background, rogu::Tile* border, rogu::BorderType type = BorderType::BORDER_NONE)
	{
		for (int q = y; q < y + h; q++)
			for (int p = x; p < x + w; p++)
			{
				writeToBufferScreenPos(background, p * tileSize, q * tileSize);
			}

		if (type == BorderType::BORDER_NONE) return;

		bool draw = false;
		for (int q = y; q < y + h; q++)
			for (int p = x; p < x + w; p++)
			{
				draw = false;
				if ((p <   x      + thickness) && (type == BorderType::BORDER_FULL || type == BorderType::BORDER_LEFT 
												|| type == BorderType::BORDER_BOTTOM_LEFT || type == BorderType::BORDER_LEFT_TOP))   draw = true;
				if ((q <   y      + thickness) && (type == BorderType::BORDER_FULL || type == BorderType::BORDER_TOP 
												|| type == BorderType::BORDER_TOP_RIGHT || type == BorderType::BORDER_LEFT_TOP))    draw = true;
				if ((p >= (x + w) - thickness) && (type == BorderType::BORDER_FULL || type == BorderType::BORDER_RIGHT 
												|| type == BorderType::BORDER_RIGHT_BOTTOM || type == BorderType::BORDER_TOP_RIGHT))  draw = true;
				if ((q >= (y + h) - thickness) && (type == BorderType::BORDER_FULL || type == BorderType::BORDER_BOTTOM 
												|| type == BorderType::BORDER_BOTTOM_LEFT || type == BorderType::BORDER_RIGHT_BOTTOM)) draw = true;

				if (draw)
					writeToBufferScreenPos(border, p * tileSize, q * tileSize);
			}
	}

	void BoardRenderer::writeToBufferScreenPos(rogu::Tile* tile, int x, int y)
	{
		int posX = x / tileSize;
		int posY = y / tileSize;

		boardTiles[posY * boardWidth + posX] = tile;
	}
	
	void BoardRenderer::writeToBufferTilePos(rogu::Tile* tile, int x, int y)
	{
		if (y >= boardHeight || x >= boardWidth ) 
			boardTiles[0] = tile;
		else
			boardTiles[y * boardWidth + x] = tile;
	}

}