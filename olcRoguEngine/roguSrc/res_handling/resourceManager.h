#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include "ResourceBlock.h"
#include "../tiles/tile.h"

namespace rogu
{
	class ResourceManager
	{
		/*  ::Description:: -Sebastian
			Here we will load in the spritesheet and actors and the renderer can request 
			rogu::Sprite(s) for the tiles that will end up on the screen.

			while the actor & landscapeManager will request sprites from here, they themselves
			will write to the boardRenderer's buffer. 
		*/


	public:

		ResourceManager()
		{
		}

		~ResourceManager()
		{
			//delete &resources;
		}

		std::vector<rogu::Tile*> requestSpriteString(std::string keyToFind)
		{
			std::vector<rogu::Tile*> toReturn = std::vector<rogu::Tile*>();
			std::vector<char> stringVector = std::vector<char>(keyToFind.begin(), keyToFind.end());
			while (!stringVector.empty())
			{
				std::vector<char> toCompare;
				toCompare.push_back(stringVector[0]);
				stringVector.erase(stringVector.begin());

				if (toCompare[0] == '<')
				{
					while (true)
					{
						toCompare.push_back(stringVector[0]);
						stringVector.erase(stringVector.begin());
						if (toCompare[toCompare.size() - 1] == '>')
						{
							break;
						}
					}
				}

				toReturn.push_back(getTileFromBlock(std::string(toCompare.begin(), toCompare.end())));
			}
			return toReturn;
		}

		rogu::Tile* getTileFromBlock(std::string keyToFind)
		{
			for (int i = 0; i < resources.size(); i++)
			{
				if (resources[i]->tryKey(keyToFind))
				{
					return resources[i]->getTile();
				}
			}
			return nullptr;
		}

	private:
		std::vector<rogu::ResourceBlock*> resources = 
		{
				new ResourceBlock("A", new rogu::Tile({new rogu::Sprite({1, 8})}, 0)),
				new ResourceBlock("B", new rogu::Tile({new rogu::Sprite({2, 8})}, 0)),
				new ResourceBlock("C", new rogu::Tile({new rogu::Sprite({3, 8})}, 0)),
				new ResourceBlock("D", new rogu::Tile({new rogu::Sprite({4, 8})}, 0)),
				new ResourceBlock("E", new rogu::Tile({new rogu::Sprite({5, 8})}, 0)),
				new ResourceBlock("F", new rogu::Tile({new rogu::Sprite({6, 8})}, 0)),
				new ResourceBlock("G", new rogu::Tile({new rogu::Sprite({7, 8})}, 0)),
				new ResourceBlock("H", new rogu::Tile({new rogu::Sprite({8, 8})}, 0)),
				new ResourceBlock("I", new rogu::Tile({new rogu::Sprite({9, 8})}, 0)),
				new ResourceBlock("J", new rogu::Tile({new rogu::Sprite({10, 8})}, 0)),
				new ResourceBlock("K", new rogu::Tile({new rogu::Sprite({11, 8})}, 0)),
				new ResourceBlock("L", new rogu::Tile({new rogu::Sprite({12, 8})}, 0)),
				new ResourceBlock("M", new rogu::Tile({new rogu::Sprite({13, 8})}, 0)),
				new ResourceBlock("N", new rogu::Tile({new rogu::Sprite({14, 8})}, 0)),
				new ResourceBlock("O", new rogu::Tile({new rogu::Sprite({15, 8})}, 0)),
				new ResourceBlock("P", new rogu::Tile({new rogu::Sprite({0, 9})}, 0)),
				new ResourceBlock("Q", new rogu::Tile({new rogu::Sprite({1, 9})}, 0)),
				new ResourceBlock("R", new rogu::Tile({new rogu::Sprite({2, 9})}, 0)),
				new ResourceBlock("S", new rogu::Tile({new rogu::Sprite({3, 9})}, 0)),
				new ResourceBlock("T", new rogu::Tile({new rogu::Sprite({4, 9})}, 0)),
				new ResourceBlock("U", new rogu::Tile({new rogu::Sprite({5, 9})}, 0)),
				new ResourceBlock("V", new rogu::Tile({new rogu::Sprite({6, 9})}, 0)),
				new ResourceBlock("W", new rogu::Tile({new rogu::Sprite({7, 9})}, 0)),
				new ResourceBlock("X", new rogu::Tile({new rogu::Sprite({8, 9})}, 0)),
				new ResourceBlock("Y", new rogu::Tile({new rogu::Sprite({9, 9})}, 0)),
				new ResourceBlock("Z", new rogu::Tile({new rogu::Sprite({10, 9})}, 0)),
				new ResourceBlock("Å", new rogu::Tile({new rogu::Sprite({15, 13})}, 0)),
				new ResourceBlock("Ä", new rogu::Tile({new rogu::Sprite({14, 13})}, 0)),
				new ResourceBlock("Ö", new rogu::Tile({new rogu::Sprite({9, 14})}, 0)),

				new ResourceBlock("a", new rogu::Tile({new rogu::Sprite({1, 10})}, 0)),
				new ResourceBlock("b", new rogu::Tile({new rogu::Sprite({2, 10})}, 0)),
				new ResourceBlock("c", new rogu::Tile({new rogu::Sprite({3, 10})}, 0)),
				new ResourceBlock("d", new rogu::Tile({new rogu::Sprite({4, 10})}, 0)),
				new ResourceBlock("e", new rogu::Tile({new rogu::Sprite({5, 10})}, 0)),
				new ResourceBlock("f", new rogu::Tile({new rogu::Sprite({6, 10})}, 0)),
				new ResourceBlock("g", new rogu::Tile({new rogu::Sprite({7, 10})}, 0)),
				new ResourceBlock("h", new rogu::Tile({new rogu::Sprite({8, 10})}, 0)),
				new ResourceBlock("i", new rogu::Tile({new rogu::Sprite({9, 10})}, 0)),
				new ResourceBlock("j", new rogu::Tile({new rogu::Sprite({10, 10})}, 0)),
				new ResourceBlock("k", new rogu::Tile({new rogu::Sprite({11, 10})}, 0)),
				new ResourceBlock("l", new rogu::Tile({new rogu::Sprite({12, 10})}, 0)),
				new ResourceBlock("m", new rogu::Tile({new rogu::Sprite({13, 10})}, 0)),
				new ResourceBlock("n", new rogu::Tile({new rogu::Sprite({14, 10})}, 0)),
				new ResourceBlock("o", new rogu::Tile({new rogu::Sprite({15, 10})}, 0)),
				new ResourceBlock("p", new rogu::Tile({new rogu::Sprite({0, 11})}, 0)),
				new ResourceBlock("q", new rogu::Tile({new rogu::Sprite({1, 11})}, 0)),
				new ResourceBlock("r", new rogu::Tile({new rogu::Sprite({2, 11})}, 0)),
				new ResourceBlock("s", new rogu::Tile({new rogu::Sprite({3, 11})}, 0)),
				new ResourceBlock("t", new rogu::Tile({new rogu::Sprite({4, 11})}, 0)),
				new ResourceBlock("u", new rogu::Tile({new rogu::Sprite({5, 11})}, 0)),
				new ResourceBlock("v", new rogu::Tile({new rogu::Sprite({6, 11})}, 0)),
				new ResourceBlock("w", new rogu::Tile({new rogu::Sprite({7, 11})}, 0)),
				new ResourceBlock("x", new rogu::Tile({new rogu::Sprite({8, 11})}, 0)),
				new ResourceBlock("y", new rogu::Tile({new rogu::Sprite({9, 11})}, 0)),
				new ResourceBlock("z", new rogu::Tile({new rogu::Sprite({10, 11})}, 0)),
				new ResourceBlock("å", new rogu::Tile({new rogu::Sprite({4, 13})}, 0)),
				new ResourceBlock("ä", new rogu::Tile({new rogu::Sprite({6, 13})}, 0)),
				new ResourceBlock("ö", new rogu::Tile({new rogu::Sprite({4, 14})}, 0)),

				new ResourceBlock(",", new rogu::Tile({new rogu::Sprite({12, 6})}, 0)),
				new ResourceBlock(".", new rogu::Tile({new rogu::Sprite({14, 6})}, 0)),
				new ResourceBlock("!", new rogu::Tile({new rogu::Sprite({1 , 6})}, 0)),
				new ResourceBlock("?", new rogu::Tile({new rogu::Sprite({15, 7})}, 0)),
				new ResourceBlock(":", new rogu::Tile({new rogu::Sprite({10, 7})}, 0)),
				new ResourceBlock("-", new rogu::Tile({new rogu::Sprite({13, 6})}, 0)),
				new ResourceBlock("_", new rogu::Tile({new rogu::Sprite({15, 9})}, 0)),
				new ResourceBlock("'", new rogu::Tile({new rogu::Sprite({7 , 6})}, 0)),

				new ResourceBlock("@", new rogu::Tile({new rogu::Sprite({0, 8})}, 0)),
				new ResourceBlock("$", new rogu::Tile({new rogu::Sprite({4, 6})}, 0)),
				new ResourceBlock("£", new rogu::Tile({new rogu::Sprite({12, 13})}, 0)),
				new ResourceBlock("µ", new rogu::Tile({new rogu::Sprite({6, 18})}, 0)),

				new ResourceBlock("<up>", new rogu::Tile({new rogu::Sprite({8, 5})}, 0)),
				new ResourceBlock("<down>", new rogu::Tile({new rogu::Sprite({9, 5})}, 0)),
				new ResourceBlock("<right>", new rogu::Tile({new rogu::Sprite({10, 5})}, 0)),
				new ResourceBlock("<left>", new rogu::Tile({new rogu::Sprite({11, 5})}, 0)),

				new ResourceBlock("<dither_soft>", new rogu::Tile({new rogu::Sprite({0, 15})}, 0)),
				new ResourceBlock("<dither_medium>", new rogu::Tile({new rogu::Sprite({1, 15})}, 0)),
				new ResourceBlock("<dither_hard>", new rogu::Tile({new rogu::Sprite({2, 15})}, 0)),
				new ResourceBlock("<dither_flip>", new rogu::Tile({new rogu::Sprite({0, 15}), new rogu::Sprite({1, 15}), new rogu::Sprite({2, 15}), new rogu::Sprite({1, 15})}, 0)),
				new ResourceBlock("<stone_wall>", new rogu::Tile({new rogu::Sprite({0, 0})}, 0, true)),
				new ResourceBlock("<wisp>", new rogu::Tile({new rogu::Sprite({13, 3}), new rogu::Sprite({14, 3}), new rogu::Sprite({15, 3}), new rogu::Sprite({14, 3})}, 0)),
				new ResourceBlock("<wisp1>", new rogu::Tile({new rogu::Sprite({14, 3}), new rogu::Sprite({15, 3}), new rogu::Sprite({14, 3}), new rogu::Sprite({13, 3})}, 0)),
				new ResourceBlock("<wisp2>", new rogu::Tile({new rogu::Sprite({15, 3}), new rogu::Sprite({14, 3}), new rogu::Sprite({13, 3}), new rogu::Sprite({14, 3})}, 0)),
				new ResourceBlock("<fountain>", new rogu::Tile({new rogu::Sprite({12, 0}), new rogu::Sprite({13, 0})}, 0)),
				new ResourceBlock("<wooden_door>", new rogu::Tile({new rogu::Sprite({1, 0})}, 0)),
		};
	};
}

