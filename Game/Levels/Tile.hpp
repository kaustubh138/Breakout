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
	bool IsSolid;
	std::shared_ptr<Texture> m_Texture;

public:
	void DrawTiles(std::shared_ptr<SpriteRenderer>& renderer)
	{
		renderer->DrawSprite(m_Texture, m_Position, m_Size, m_Rotation, m_Color);
	}

	/* Utilities */
	inline bool GetDestroyed() { return IsDestroyed; };
	inline void Destroy() { IsDestroyed = true; };
	inline glm::vec2 GetPosition() { return m_Position; };
	inline bool GetSolidity() { return IsSolid; };

	// AABB Data
	inline glm::vec2 GetHalfExtents()
	{
		return glm::vec2(
			m_Size.x / 2.0f,
			m_Size.y / 2.0f);
	};

	inline glm::vec2 GetCenter(glm::vec2 HalfExtents)
	{
		return glm::vec2(
			m_Position.x + HalfExtents.x,
			m_Position.y + HalfExtents.y
		);
	};
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
		IsSolid = false;
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
		IsSolid = true;
	}
};

#endif // !TILE_H