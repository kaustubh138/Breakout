#pragma once
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Renderer.hpp"
#include "Sprite/SpriteRenderer.hpp"
#include <memory>

class GameObject
{
public:
	glm::vec2 m_Position, m_Size;
	float m_Velocity;
	glm::vec3 m_Color;
	float m_Rotation = 0.0f;
	bool IsDestroyed;
	std::shared_ptr<Texture> m_Texture;

	virtual void DrawObject(std::shared_ptr<SpriteRenderer> Renderer) = 0;
};

#endif //! GAME_OBJECT_H