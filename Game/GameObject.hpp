#pragma once
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Renderer.hpp"
#include "Sprite/SpriteRenderer.hpp"

class GameObject
{
protected:
	glm::vec2 m_Position, m_Size, m_Velocity;
	glm::vec3 m_Color;
	float m_Rotation;
	bool IsDestroyed;
};

#endif //! GAME_OBJECT_H