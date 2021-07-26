#pragma once
#ifndef PADDLE_H
#define PADDLE_H

#include "Renderer.hpp"
#include <memory>
#include "GameObject.hpp"

class Paddle
	: public GameObject
{
private:
	unsigned int ScreenWidth;
	unsigned int ScreenHeight;
public:
	Paddle(std::shared_ptr<Texture>& PaddleTexture, unsigned int& ScreenWidth, unsigned int& ScreenHeight, 
		glm::vec2 Size = glm::vec2(100.0f, 20.0f), glm::vec2 Velocity = glm::vec2(500.0f, 0.0f), glm::vec3 Color = glm::vec3(1.0f))
	{
		ScreenWidth = ScreenWidth;
		ScreenHeight = ScreenHeight;
		m_Texture = PaddleTexture;
		m_Size = Size;
		m_Position = glm::vec2(ScreenWidth / 2.0f - m_Size.x / 2.0f, ScreenHeight - m_Size.y);
		m_Color = Color;
		m_Velocity = Velocity;
	}
	
	void DrawObject(std::shared_ptr<SpriteRenderer> Renderer) override
	{
		Renderer->DrawSprite(m_Texture, m_Position, m_Size, m_Rotation, m_Color);
	}
};

#endif PADDLE_H