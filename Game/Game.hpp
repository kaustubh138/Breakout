#pragma once

#include "Renderer.hpp"
#include "Levels/Level.hpp"

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
	
	//std::vector<Level> m_Levels;
	Level m_Level;
	unsigned int m_CurrentLevel;
public:
	Game(unsigned int width, unsigned int height);
	~Game();

	void init();
	
	void ProcessInput(GLFWwindow* window, float dt);
	void PollCollisions();
	
	void Update(GLFWwindow* window, float dt);
	void Render();
};