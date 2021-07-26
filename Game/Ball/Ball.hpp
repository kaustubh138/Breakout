#pragma once

#ifndef BALL_H
#define BALL_H

#include "GameObject.hpp"
#include <memory>

struct OriginalData
{
	glm::vec2 OPosition;
	glm::vec2 OVelocity;
	float ORadius;
	glm::vec2 OSize;
};

class BallObject
	: public GameObject
{
private:
	OriginalData* OData;
	float m_Radius;
	bool IsStuck = true;

public:
	BallObject(std::shared_ptr<Texture> BallTexture, glm::vec2 Position, float Radius, glm::vec2 Velocity);
	~BallObject();

	glm::vec2 Move(GLFWwindow* window, float dt, unsigned int ScreenWidth, unsigned int ScreenHeight, glm::vec2 PaddlePosition, glm::vec2 PaddleSize);

	void Reset();
	
	void DrawObject(std::shared_ptr<SpriteRenderer> Renderer) override
	{
		Renderer->DrawSprite(m_Texture, m_Position, m_Size, m_Rotation, m_Color);
	}

	inline void Release() { IsStuck = false; };
	
	inline glm::vec2 ComputePosition(glm::vec2 PaddlePosition, glm::vec2 PaddleSize)
	{
		/*
			Ball Postion if IsStuck = True:
				Bottom left corner coords of Paddle + ([mid point of paddle - radius(to be truly in center)], [diameter of ball but from bottom to up]) 
														x-position											   y-position 	
		*/					
		return PaddlePosition + glm::vec2(PaddleSize.x / 2.0f - m_Radius, -m_Radius * 2.0f);
	}
};

#endif // !BALL_H