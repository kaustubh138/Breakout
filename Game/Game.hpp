#pragma once

#include "Renderer.hpp"

enum class GameState
{
	ACTIVE,
	MENU,
	WIN
};

class Game
{
public:
	GameState State;
	bool m_Keys[1024];
	unsigned int m_Width, m_Height;

public:
	Game(unsigned int width, unsigned int height);
	~Game();

	void init();
	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
};