#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "rendering/boardRenderer.h"
#include "res_handling/resourceManager.h"
#include "res_handling/ResourceBlock.h"
#include "tiles/tile.h"

namespace rogu
{
	#define TILE_SIZE 12
	#define RES_MULTIPLIER 1 
	#define SCREEN_PIXEL_SIZE 2
	#define SCREEN_WIDTH (70 * TILE_SIZE * RES_MULTIPLIER)
	#define SCREEN_HEIGHT (41 * TILE_SIZE * RES_MULTIPLIER)
	#define CENTER_POS_X ((SCREEN_WIDTH / 2) - SCREEN_WIDTH % TILE_SIZE) / TILE_SIZE
	#define CENTER_POS_Y ((SCREEN_HEIGHT / 2) - SCREEN_HEIGHT % TILE_SIZE) / TILE_SIZE

	#define USING_DECALS true;

	class RoguCore : public olc::PixelGameEngine
	{
	public:
		RoguCore()
		{
			// Name you application
			sAppName = "spriteSheet";
		}

		bool OnUserCreate() override
		{
			srand(200);


			spriteSheet = std::make_unique<olc::Sprite>("./resources/tileset12x12.png");

			decalSheet = std::make_unique<olc::Decal>(spriteSheet.get());

			timer = 0;
			spriteSheetDraw();
			return true;
		}

		bool OnUserUpdate(float fElapsedTime) override
		{

			//std::cout << "deltaTime: " << fElapsedTime << "\n";

			if (GetKey(olc::F).bHeld)
			{
				renderer.writeToAllEmpty(resourceManager.getTileFromBlock("<stone_wall>"));
			}
			if (GetKey(olc::R).bHeld)
			{
				olc::vi2d pos = olc::vi2d((rand() % (gameWindowSize.x - 1)) + gameWindowPos.x, (rand() % (gameWindowSize.y - 1)) + gameWindowPos.y);
				rogu::Tile* randTile = resourceManager.getTileFromBlock("<wisp>");
				olc::vi2d dimensions = randTile->getSpriteDimensions();
				renderer.writeToBufferTilePos(randTile, pos.x, pos.y);
#if USING_DECALS
				DrawPartialDecal(pos * TILE_SIZE, decalSheet.get(), dimensions, { TILE_SIZE, TILE_SIZE });
#elif
				//DrawPartialSprite(pos.x * TILE_SIZE, pos.y * TILE_SIZE, spriteSheet, dimensions.x, dimensions.y, TILE_SIZE, TILE_SIZE);
#endif
			}
			if (GetKey(olc::C).bHeld)
			{
				renderer.writeToArea(0, 0, SCREEN_WIDTH / TILE_SIZE, SCREEN_HEIGHT / TILE_SIZE, nullptr);
			}
			if (GetKey(olc::T).bPressed)
			{
				spriteSheetDraw();
			}

			if (GetMouse(0).bHeld)
			{
				renderer.writeToBufferScreenPos(resourceManager.getTileFromBlock("<stone_wall>"), GetMousePos().x, GetMousePos().y);
				olc::vi2d dimensions = resourceManager.getTileFromBlock("<stone_wall>")->getSpriteDimensions();
#if USING_DECALS
				DrawPartialDecal({ (float)GetMousePos().x - (GetMousePos().x % TILE_SIZE), (float)GetMousePos().y - (GetMousePos().y % TILE_SIZE) }, decalSheet.get(), dimensions, { TILE_SIZE, TILE_SIZE });
#elif
				DrawPartialSprite(GetMousePos().x - (GetMousePos().x % TILE_SIZE), GetMousePos().y - (GetMousePos().y % TILE_SIZE), spriteSheet, dimensions.x, dimensions.y, TILE_SIZE, TILE_SIZE);
#endif
			}
			if (GetMouse(1).bHeld)
			{
				renderer.writeToBufferScreenPos(nullptr, GetMousePos().x, GetMousePos().y);
				render();
			}

			timer += fElapsedTime;
			if (timer >= timeBetweenFrames)
			{
				timer = 0;
				renderer.updateBoard();
			}
			render();

			return true;
		}

		void render()
		{
			Clear(olc::BLACK);
			//SetPixelMode(olc::Pixel::MASK);
			// Called once at the start, so create things here
			std::vector<rogu::Tile*> boardTiles = renderer.getAllTilesInBuffer();
			olc::vi2d boardDimensions = renderer.getBoardDimensions();

			for (int x = 0; x < boardDimensions.x; x++)
				for (int y = 0; y < boardDimensions.y; y++)
				{
					if (boardTiles[y * boardDimensions.x + x] == nullptr) continue;
					olc::vi2d dimensions = boardTiles[y * boardDimensions.x + x]->getSpriteDimensions();
					olc::vi2d position = olc::vi2d(x * TILE_SIZE, y * TILE_SIZE);
#if USING_DECALS
					DrawPartialDecal(position, decalSheet.get(), {dimensions.x * (float)TILE_SIZE, dimensions.y * (float)TILE_SIZE}, { TILE_SIZE, TILE_SIZE }, { 1.0f, 1.0f });
#elif
					//DrawPartialSprite(x * TILE_SIZE, y * TILE_SIZE, spriteSheet, dimensions.x, dimensions.y, TILE_SIZE, TILE_SIZE);
#endif
					boardTiles[y * boardDimensions.x + x]->updated = false;
				}
			//SetPixelMode(olc::Pixel::NORMAL);
		}

		void spriteSheetDraw()
		{
			rogu::Tile* stoneWall = resourceManager.getTileFromBlock("<stone_wall>");
			rogu::Tile* wisp = resourceManager.getTileFromBlock("<wisp>");
			rogu::Tile* ditherFlip = resourceManager.getTileFromBlock("<dither_flip>");
			rogu::Tile* ditherSoft = resourceManager.getTileFromBlock("<dither_soft>");

			renderer.drawPanel(0, (SCREEN_HEIGHT / TILE_SIZE) - 11, (SCREEN_WIDTH / TILE_SIZE) - 10, 11, 1, nullptr, stoneWall, rogu::BorderType::BORDER_FULL);
			renderer.drawPanel((SCREEN_WIDTH / TILE_SIZE) - 10, 10, 10, (SCREEN_HEIGHT / TILE_SIZE) - 10, 1, nullptr, stoneWall, rogu::BorderType::BORDER_RIGHT_BOTTOM);
			renderer.drawPanel((SCREEN_WIDTH / TILE_SIZE) - 11, 0, 11, 10, 1, nullptr, stoneWall, rogu::BorderType::BORDER_FULL);

			renderer.drawPanel(gameWindowPos.x - 1, gameWindowPos.y - 1, gameWindowSize.x + 1, gameWindowSize.y + 1, 1, nullptr, stoneWall, rogu::BorderType::BORDER_FULL);


			//Draw ROGU logo
			

			int centerX = gameWindowPos.x + (gameWindowSize.x / 2);
			int centerY = gameWindowPos.y + (gameWindowSize.y / 2) - 2;
			renderer.drawPanel(centerX - 7, centerY - 7, 15, 15, 1, nullptr, ditherFlip, BorderType::BORDER_FULL);

			//R
			renderer.drawPanel(centerX - 5, centerY - 5, 5, 5, 1, nullptr, ditherSoft, BorderType::BORDER_FULL);
			renderer.drawPanel(centerX - 4, centerY - 3, 4, 3, 1, nullptr, nullptr, BorderType::BORDER_NONE);

			//O
			renderer.drawPanel(centerX + 1, centerY - 5, 5, 5, 1, nullptr, ditherSoft, BorderType::BORDER_FULL);

			//G
			renderer.drawPanel(centerX - 5, centerY + 1, 5, 5, 1, nullptr, ditherSoft, BorderType::BORDER_FULL);
			renderer.writeToBufferTilePos(nullptr, centerX - 1, centerY + 2);
			renderer.writeToBufferTilePos(ditherSoft, centerX - 2, centerY + 3);
			renderer.writeToBufferTilePos(ditherSoft, centerX - 3, centerY + 3);

			//U
			renderer.drawPanel(centerX + 1, centerY + 1, 5, 5, 1, nullptr, ditherSoft, BorderType::BORDER_FULL);
			renderer.drawPanel(centerX + 2, centerY + 1, 3, 2, 1, nullptr, nullptr, BorderType::BORDER_NONE);

			//TEST TEXT
			renderer.writeTextToArea(2, 32, 56, resourceManager.requestSpriteString("This is a project to see if a smaller single-buffer engine is a viable concept, This is a project by Sebastian for Blind Hate Machine."));
			renderer.writeTextToArea(2, 37, 56, resourceManager.requestSpriteString("You can even write tiles! Like: <fountain> and <wisp>!"));
			renderer.writeTextToArea(centerX - 5, centerY + 9, 65, resourceManager.requestSpriteString("ROGU Engine"));
		}

	private:
		rogu::BoardRenderer renderer = rogu::BoardRenderer(SCREEN_WIDTH / TILE_SIZE, SCREEN_HEIGHT / TILE_SIZE, nullptr, TILE_SIZE);
		rogu::ResourceManager resourceManager;
		olc::vi2d gameWindowPos = olc::vi2d(1, 1);
		olc::vi2d gameWindowSize = olc::vi2d((SCREEN_WIDTH / TILE_SIZE) - 11, (SCREEN_HEIGHT / TILE_SIZE) - 11);
		std::unique_ptr<olc::Sprite> spriteSheet;
		std::unique_ptr<olc::Decal> decalSheet;
		float timeBetweenFrames = 0.22f;
		float timer;
	};
}

int main()
{
	rogu::RoguCore core;
	if (core.Construct(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_PIXEL_SIZE, SCREEN_PIXEL_SIZE, false, true))
		core.Start();
	return 0;
}