#pragma once
#include "Tile.hpp"
#include "ResourceManager/ResourceManager.hpp"

Tile GenTile(unsigned int TileData, float TileWidth, float TileHeight, unsigned int i, unsigned int j)
{
    switch (TileData)
    {
        case 1:
        {
            // solid
            glm::vec2 pos(TileWidth * j, TileHeight * i);
            glm::vec2 size(TileWidth, TileHeight);
            SolidTile tile(pos, size, glm::vec3(1.0f));
            return tile;
        }
        case 2:
        {
            glm::vec2 pos(TileWidth * j, TileHeight * i);
            glm::vec2 size(TileWidth, TileHeight);
            NormalTile tile(pos, size, glm::vec3(0.2f, 0.6f, 1.0f));
            return tile;
        }
        case 3:
        {
            glm::vec2 pos(TileWidth * j, TileHeight * i);
            glm::vec2 size(TileWidth, TileHeight);
            NormalTile tile(pos, size, glm::vec3(0.0f, 0.7f, 0.0f));
            return tile;
        }
        case 4:
        {
            glm::vec2 pos(TileWidth * j, TileHeight * i);
            glm::vec2 size(TileWidth, TileHeight);
            NormalTile tile(pos, size,glm::vec3(0.8f, 0.8f, 0.4f));
            return tile;
        }
        case  5:
        {
            glm::vec2 pos(TileWidth * j, TileHeight * i);
            glm::vec2 size(TileWidth, TileHeight);
            NormalTile tile(pos, size, glm::vec3(1.0f, 0.5f, 0.0f));
            return tile;
        }
        default:
        {
            glm::vec2 pos(TileWidth * j, TileHeight * i);
            glm::vec2 size(TileWidth, TileHeight);
            NormalTile tile(pos, size, glm::vec3(1.0f));
            return tile;
        }
    }
}
