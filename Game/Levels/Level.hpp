#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

class Level
{
protected:
	unsigned int m_NumberofRows;
	std::vector<unsigned __int64> m_LevelData;
public:
	void LoadLevelFromFile(const char* file_name, unsigned int LevelWidth, unsigned int LevelHeight);
	unsigned int RetrieveTileData(unsigned int tile_number);
};

#endif //! LEVEL_H