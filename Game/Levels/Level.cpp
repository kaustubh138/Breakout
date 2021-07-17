#include "Level.hpp"
#include "GenTile.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <boost/lexical_cast.hpp>

/*
	Data format:
		unsigned long long => 8 bytes => 32 bits
		tile1 tile2 tile3 tile4 tile5 tile6 tile7 tile8
		 52		48	 40		32	  24	16	  8		0		  
	This imposes a limition of the number of tiles in a row
*/

void Level::LoadLevelFromFile(const char* FileName, unsigned int ScreenWidth, unsigned int ScreenHeight)
{
    m_LevelData.reserve(3);
   
    std::ifstream stream(FileName);

    char* c = nullptr;

    while (!stream.eof())
    {
        unsigned __int64 LineData = 0x00;
        std::vector<unsigned __int64> numbers;
        std::string line;
        std::getline(stream, line, '\n');

        for (auto ptr : line)
        {
            if (ptr == ' ')
                ;
            else
            {
                try
                {
                    unsigned __int64 num = boost::lexical_cast<unsigned __int64>(ptr);
                    numbers.push_back(num);
                }
                catch (boost::bad_lexical_cast& e) {
                    std::cout << "Exception caught :" << e.what() << std::endl;
                }
            }
        }

        int arraySize = numbers.size();
        m_TilesPerLine = arraySize;
        for (int i = arraySize; i != 0; i--)
        {
            LineData |= (numbers[i-1] << (i * 8));
        }

        m_LevelData.push_back(LineData);
    };

    if (m_LevelData.size() > 0)
        init(ScreenWidth, ScreenHeight / 2);
    else
        std::cerr << "[ERROR] Level Data is empty!" << std::endl;
}

unsigned int Level::RetrieveTileData(unsigned int tile_number, unsigned int row_number)
{
    unsigned __int64 shift = ((unsigned __int64)0xFF << (8 * (tile_number + 1))); 
    unsigned __int64 data = (m_LevelData[row_number] & shift) >> (8 * (tile_number + 1));
    return (unsigned int)data; // since the tile data won't excced 255 anyway. 
                               // so why squander 64 bits when we can get away with 32 bit
}

void Level::init(unsigned int ScreenWidth, unsigned int ScreenHeight)
{
    unsigned int LevelHeight = m_LevelData.size();
    unsigned int LevelWidth = m_TilesPerLine;

    float TileWidth = ScreenWidth / static_cast<float>(LevelWidth);
    float TileHeight = ScreenHeight / static_cast<float>(LevelHeight);

    for (unsigned int i = 0; i < LevelHeight; i++)
    {
        for (unsigned int j = 0; j < LevelWidth; j++)
        {
            unsigned int TileData = RetrieveTileData(j, i);
            if (TileData)
            {
                Tile tempTile = GenTile(TileData, TileWidth, TileHeight, i, j);
                m_Tiles.push_back(tempTile);
            }
        }
    }
}

void Level::Draw(std::shared_ptr<SpriteRenderer>& renderer)
{
    for (Tile& t : m_Tiles)
    {
        if (!t.GetDestroyed())
        {
            t.DrawTiles(renderer);
        }
    }
}