#include "Level.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

/*
	Data format:
		unsigned long long => 8 bytes => 32 bits
		tile1 tile2 tile3 tile4 tile5 tile6 tile7 tile8
		 52		48	 40		32	  24	16	  8		0		  
	This imposes a limition of the number of tiles in a row
*/

void Level::LoadLevelFromFile(const char* FileName, unsigned int LevelWidth, unsigned int LevelHeight)
{
    m_LevelData.reserve(3);
   
    std::ifstream stream(FileName);

    char* c = nullptr;
    std::vector<unsigned __int64> AllRowsData;

    while (!stream.eof())
    {
        unsigned __int64 LineData = 0x00;
        std::vector<unsigned __int64> numbers;
        std::string line;
        std::getline(stream, line, '\n');

        for (auto& ptr : line)
        {
            if (ptr == ' ')
                ;
            else
            {
                unsigned __int64 num = boost::lexical_cast<unsigned __int64>(ptr);
                numbers.push_back(num);
            }
        }

        int arraySize = numbers.size();
        for (int i = arraySize; i != 0; i--)
        {
            LineData |= (numbers[i-1] << (i * 8));
        }

        m_LevelData.push_back(LineData);
        m_NumberofRows += 1;
    };
}

unsigned int Level::RetrieveTileData(unsigned int tile_number)
{
    unsigned __int64 shift = ((unsigned __int64)0xFF << (8 * (8 - tile_number))); 
    unsigned __int64 data = (m_LevelData[2] & shift) >> (8 * (8 - tile_number));
    return (unsigned int)data; // since the tile data won't excced 255 anyway. 
                               // so why squander 64 bits when we can get away with 32 bit
}
