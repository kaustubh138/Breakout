#pragma once
// Header only

#ifndef TILE_H
#define TILE_H

#include "Texture/Texture.hpp"
#include "Renderer.hpp"
#include "Sprite/SpriteRenderer.hpp"
#include <memory>

class Tile
{
protected:
	glm::vec2 m_Position, m_Size, m_Velocity;
	glm::vec3 m_Color;
	float m_Rotation;
	bool IsDestroyed;
	std::shared_ptr<Texture> m_Texture;

public:
	void DrawTiles(std::shared_ptr<SpriteRenderer>& renderer)
	{
		renderer->DrawSprite(m_Texture, m_Position, m_Size, m_Rotation, m_Color);
	}
	
	inline bool GetDestroyed() { return IsDestroyed; };
};

class NormalTile
	:public Tile
{
public:
	NormalTile(glm::vec2 pos = glm::vec2(0.0f, 0.0f),
		glm::vec2 size = glm::vec2(1.0f, 1.0f),
		glm::vec3 color = glm::vec3(1.0f),
		glm::vec2 velocity = glm::vec2(0.0f, 0.0f),
		float rotation = 0.0f,
		bool destroyed = false
	)
	{
		m_Texture = std::make_shared<Texture>("Resources/Blocks/block.png", "Block");
		m_Position = pos,
		m_Size = size;
		m_Color = color;
		m_Velocity = velocity;
		m_Rotation = rotation;
		IsDestroyed = destroyed;
	}
};

class SolidTile
	: public Tile
{
public:
	SolidTile(glm::vec2 pos = glm::vec2(0.0f, 0.0f),
		glm::vec2 size = glm::vec2(1.0f, 1.0f),
		glm::vec3 color = glm::vec3(1.0f),
		glm::vec2 velocity = glm::vec2(0.0f, 0.0f),
		float rotation = 0.0f,
		bool destroyed = false
	)
	{
		m_Texture = std::make_shared<Texture>("Resources/Blocks/block_solid.png", "SolidBlock");
		m_Position = pos;
		m_Size = size;
		m_Color = color;
		m_Velocity = velocity;
		m_Rotation = rotation;
		IsDestroyed = destroyed;
	}
};

#endif // !TILE_H