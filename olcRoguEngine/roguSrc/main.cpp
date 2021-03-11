#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "rendering/boardRenderer.h"
#include "res_handling/resourceManager.h"
#include "res_handling/ResourceBlock.h"
#include "tiles/tile.h"
#include "entities/entityManager.h"
#include "entities/entity.h"

namespace rogu
{
	#define TILE_SIZE 12
	#define RES_MULTIPLIER 1
	#define SCREEN_PIXEL_SIZE 2
	#define SCREEN_WIDTH (72 * TILE_SIZE * RES_MULTIPLIER)
	#define SCREEN_HEIGHT (41 * TILE_SIZE * RES_MULTIPLIER)
	#define CENTER_POS_X ((SCREEN_WIDTH / 2) - SCREEN_WIDTH % TILE_SIZE) / TILE_SIZE
	#define CENTER_POS_Y ((SCREEN_HEIGHT / 2) - SCREEN_HEIGHT % TILE_SIZE) / TILE_SIZE

	//Why wouldn't you use these?
	#define USING_DECALS true 

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

			Entity* player = entityManager.getPlayer();
			player->setPosition((SCREEN_WIDTH / TILE_SIZE) * 0.5f, (SCREEN_HEIGHT / TILE_SIZE) * 0.5f);
			entityManager.setPlayer(player);

			timer = 0;
			introDraw();
			return true;
		}

		bool OnUserUpdate(float fElapsedTime) override
		{

			//std::cout << "deltaTime: " << fElapsedTime << "\n";
			introTimer -= fElapsedTime;
			if (introTimer > -100)
			{
				introTimer -= fElapsedTime;
				float diff = introTimer - std::floorf(introTimer);
				if ((diff >= 0.0f && diff < 0.06f) || (diff >= 0.5f && diff < 0.56f))
				{
					renderer.writeToAll(nullptr);
					introDraw();
				}
				if (introTimer <= 0)
				{
					introTimer = -250;
					mainMenuDraw();
				}
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
#else
					DrawPartialSprite(position, spriteSheet.get(), { dimensions.x * TILE_SIZE, dimensions.y * TILE_SIZE }, { TILE_SIZE, TILE_SIZE });
#endif
					boardTiles[y * boardDimensions.x + x]->updated = false;
				}

			if (introTimer < -100)
			{
				Entity* player = entityManager.getPlayer();
				olc::vi2d vPos = player->getPosition();

				if (GetKey(olc::RIGHT).bPressed && !renderer.getIfTileIsCollider(vPos.x + 1, vPos.y)) { player->move(1, 0); }
				else if (GetKey(olc::LEFT).bPressed && !renderer.getIfTileIsCollider(vPos.x - 1, vPos.y)) { player->move(-1, 0); }
				else if (GetKey(olc::UP).bPressed && !renderer.getIfTileIsCollider(vPos.x, vPos.y - 1)) { player->move(0, -1); }
				else if (GetKey(olc::DOWN).bPressed && !renderer.getIfTileIsCollider(vPos.x, vPos.y + 1)) { player->move(0, 1); }

				DrawPartialDecal(player->getPosition() * TILE_SIZE, decalSheet.get(), 
					{ player->getSprite()->getSpriteDimensions().x * (float)TILE_SIZE, player->getSprite()->getSpriteDimensions().y * (float)TILE_SIZE }, 
					{ TILE_SIZE, TILE_SIZE }, { 1.0f, 1.0f });
			}
		}

		void introDraw()
		{
			rogu::Tile* ditherFlip = resourceManager.getTileFromBlock("<dither_flip>");
			rogu::Tile* ditherSoft = resourceManager.getTileFromBlock("<dither_soft>");
			rogu::Tile* wisp = resourceManager.getTileFromBlock("<wisp>");
			rogu::Tile* wisp1 = resourceManager.getTileFromBlock("<wisp1>");
			rogu::Tile* wisp2 = resourceManager.getTileFromBlock("<wisp2>");

			//Draw Fire?
			if (introTimer < 10.f)
			{
				for (int i = 0; i < (SCREEN_WIDTH / TILE_SIZE) * 2; i++)
				{
					renderer.writeToBufferTilePos(wisp, rand() % (SCREEN_WIDTH / TILE_SIZE), (rand() % 4) + ((SCREEN_HEIGHT / TILE_SIZE) - 4));
					renderer.writeToBufferTilePos(wisp, rand() % (SCREEN_WIDTH / TILE_SIZE), (rand() % 4));
				}

				if (introTimer < 9.f)
				{
					for (int i = 0; i < (SCREEN_WIDTH / TILE_SIZE) * 1; i++)
					{
						renderer.writeToBufferTilePos(wisp1, rand() % (SCREEN_WIDTH / TILE_SIZE), (rand() % 3) + ((SCREEN_HEIGHT / TILE_SIZE) - 7));
						renderer.writeToBufferTilePos(wisp1, rand() % (SCREEN_WIDTH / TILE_SIZE), (rand() % 3) + 4);
					}

					if (introTimer < 8.2f)
					{
						for (int i = 0; i < (SCREEN_WIDTH / TILE_SIZE) * 0.5f; i++)
						{
							renderer.writeToBufferTilePos(wisp2, rand() % (SCREEN_WIDTH / TILE_SIZE), (rand() % 4) + ((SCREEN_HEIGHT / TILE_SIZE) - 11));
							renderer.writeToBufferTilePos(wisp2, rand() % (SCREEN_WIDTH / TILE_SIZE), (rand() % 4) + 7);
						}
					}
				}
			}
			

			//Draw ROGU logo
			int centerX = (SCREEN_WIDTH / TILE_SIZE) * 0.5f;
			int centerY = (SCREEN_HEIGHT / TILE_SIZE) * 0.5f;
			renderer.drawPanel(centerX - 7, centerY - 8, 15, 15, 1, nullptr, ditherFlip, BorderType::BORDER_FULL);

			//R
			renderer.drawPanel(centerX - 5, centerY - 6, 5, 5, 1, nullptr, ditherSoft, BorderType::BORDER_FULL);
			renderer.drawPanel(centerX - 4, centerY - 4, 4, 3, 1, nullptr, nullptr, BorderType::BORDER_NONE);

			//O
			renderer.drawPanel(centerX + 1, centerY - 6, 5, 5, 1, nullptr, ditherSoft, BorderType::BORDER_FULL);

			//G
			renderer.drawPanel(centerX - 5, centerY, 5, 5, 1, nullptr, ditherSoft, BorderType::BORDER_FULL);
			renderer.writeToBufferTilePos(nullptr, centerX - 1, centerY + 1);
			renderer.writeToBufferTilePos(ditherSoft, centerX - 2, centerY + 2);
			renderer.writeToBufferTilePos(ditherSoft, centerX - 3, centerY + 2);

			//U
			renderer.drawPanel(centerX + 1, centerY, 5, 5, 1, nullptr, ditherSoft, BorderType::BORDER_FULL);
			renderer.drawPanel(centerX + 2, centerY, 3, 2, 1, nullptr, nullptr, BorderType::BORDER_NONE);

			renderer.writeTextToArea(centerX - 5, centerY + 8, 15, resourceManager.requestSpriteString("ROGU Engine"));
		}

		void mainMenuDraw()
		{
			rogu::Tile* stoneWall = resourceManager.getTileFromBlock("<stone_wall>");
			rogu::Tile* wisp = resourceManager.getTileFromBlock("<wisp>");
			rogu::Tile* ditherFlip = resourceManager.getTileFromBlock("<dither_flip>");
			rogu::Tile* ditherSoft = resourceManager.getTileFromBlock("<dither_soft>");

			// LOG_SCREEN
			renderer.drawPanel(0, fLogYStart, (SCREEN_WIDTH / TILE_SIZE), (SCREEN_HEIGHT / TILE_SIZE) - fLogYStart, 1, nullptr, stoneWall, rogu::BorderType::BORDER_FULL);
			// GAME_SCREEN
			renderer.drawPanel(0, 0, (SCREEN_WIDTH / TILE_SIZE), fLogYStart + 1, 1, nullptr, stoneWall, rogu::BorderType::BORDER_FULL);

			//TEST TEXT
			renderer.writeTextToArea(2, fLogYStart + 2, (SCREEN_WIDTH / TILE_SIZE) - 4, resourceManager.requestSpriteString(
				"Welcome to ROGU! A game where you find yourself captured by a people known as the Synod, thrown in a cell on-board their ship. Escape by any means neccessary or be inducted into their order whether you want to or not..."));
			
			int centerX = (SCREEN_WIDTH / TILE_SIZE) * 0.5f;
			int centerY = (SCREEN_HEIGHT / TILE_SIZE) * 0.5f;
			//renderer.writeTextToArea(centerX - 10, centerY - 13, 22, resourceManager.requestSpriteString("Sebastian Alkstrand's"));
			renderer.writeTextToArea(centerX - 11, centerY + 2, 22, resourceManager.requestSpriteString("You can move with <up><down><left><right>"));
			renderer.writeTextToArea(centerX - 17, centerY + 6, 22, resourceManager.requestSpriteString("New Character"));
			renderer.writeTextToArea(centerX - 11, centerY + 8, 22, resourceManager.requestSpriteString("<wooden_door>"));

			//Check if there is a save before creating this later!
			renderer.writeTextToArea(centerX + 3, centerY + 6, 22, resourceManager.requestSpriteString("Load  Character"));
			renderer.writeTextToArea(centerX + 10, centerY + 8, 22, resourceManager.requestSpriteString("<wooden_door>"));

			for (int q = 2; q < fLogYStart - 1; q++)
			{
				renderer.writeTextToArea(2, q, (SCREEN_WIDTH / TILE_SIZE) - 4, resourceManager.requestSpriteString("<dither_flip> <dither_soft><dither_medium><dither_hard> @ <dither_hard><dither_medium><dither_soft> <dither_flip>"));
				renderer.writeTextToArea((SCREEN_WIDTH / TILE_SIZE) - 15, q, (SCREEN_WIDTH / TILE_SIZE) - 4, resourceManager.requestSpriteString("<dither_flip> <dither_soft><dither_medium><dither_hard> @ <dither_hard><dither_medium><dither_soft> <dither_flip>"));
			}

			//R
			renderer.drawPanel(centerX - 15, centerY - 11, 7, 7, 1, nullptr, ditherSoft, BorderType::BORDER_FULL);
			renderer.drawPanel(centerX - 14, centerY - 9, 6, 5, 1, nullptr, nullptr, BorderType::BORDER_NONE);
			//O
			renderer.drawPanel(centerX - 7, centerY - 11, 7, 7, 1, nullptr, ditherSoft, BorderType::BORDER_FULL);
			//G
			renderer.drawPanel(centerX + 1, centerY - 11, 7, 7, 1, nullptr, ditherSoft, BorderType::BORDER_FULL);
			renderer.drawPanel(centerX + 2, centerY - 10, 6, 6, 1, nullptr, nullptr, BorderType::BORDER_NONE);
			renderer.drawPanel(centerX + 1, centerY - 8, 7, 4, 1, nullptr, ditherSoft, BorderType::BORDER_FULL);
			renderer.writeToBufferTilePos(nullptr, centerX + 2, centerY - 8);
			renderer.writeToBufferTilePos(nullptr, centerX + 3, centerY - 8);
			//U
			renderer.drawPanel(centerX + 9, centerY - 11, 7, 7, 1, nullptr, ditherSoft, BorderType::BORDER_FULL);
			renderer.drawPanel(centerX + 10, centerY - 11, 5, 5, 1, nullptr, nullptr, BorderType::BORDER_NONE);
		}

	private:
		rogu::BoardRenderer renderer = rogu::BoardRenderer(SCREEN_WIDTH / TILE_SIZE, SCREEN_HEIGHT / TILE_SIZE, nullptr, TILE_SIZE);
		EntityManager entityManager = EntityManager();
		rogu::ResourceManager resourceManager;
		olc::vi2d gameWindowPos = olc::vi2d(1, 1);
		int fLogYStart = (int)(SCREEN_HEIGHT * 0.8f) / TILE_SIZE;
		int fInvXStart = (int)(SCREEN_WIDTH * 0.84f) / TILE_SIZE;
		olc::vi2d gameWindowSize = olc::vi2d(fInvXStart - gameWindowPos.x, fLogYStart);
		std::unique_ptr<olc::Sprite> spriteSheet;
		std::unique_ptr<olc::Decal> decalSheet;
		float timeBetweenFrames = 0.22f;
		float introTimer = 12.f;
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