#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Tile.hpp"
#include "Sprite/SpriteRenderer.hpp"

class Level
{
private:
	unsigned int m_TilesPerLine;
	std::vector<unsigned __int64> m_LevelData;
	std::vector<Tile> m_Tiles;
public:
	void LoadLevelFromFile(const char* file_name, unsigned int ScreenWidth, unsigned int ScreenHeight);
	unsigned int RetrieveTileData(unsigned int tile_number, unsigned int row_number);

	void init(unsigned int ScreenWidth, unsigned int ScreenHeight);

	void Draw(std::shared_ptr<SpriteRenderer>& renderer);
	
	// vector iterator wrapper
	using IteratorType = std::vector<Tile>;
	IteratorType::iterator begin() { return m_Tiles.begin(); };
	IteratorType::iterator end() { return m_Tiles.end(); };
};

#endif //! LEVEL_H