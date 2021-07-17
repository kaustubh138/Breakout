#include "Game.hpp"
#include "Sprite/SpriteRenderer.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Levels/Level.hpp"

namespace GameData
{
	std::shared_ptr<SpriteRenderer> Renderer;

	namespace RenderData
	{
		// Textures
		std::shared_ptr<Texture> SpriteTexture;
		std::shared_ptr<Texture> Background;
	}
}

Game::Game(unsigned int width, unsigned int height)
	: State(GameState::ACTIVE), m_Keys(), m_Width(width), m_Height(height)
{}

Game::~Game()
{

}

void Game::init()
{
	// Sprite: Ball
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->m_Width), static_cast<float>(this->m_Height), 0.0f, -1.0f, 1.0f);

	std::shared_ptr<Shader> SpriteShader = std::make_shared<Shader>("Resources/Sprite/Shaders/VertexShader.glsl",
		"Resources/Sprite/Shaders/FragmentShader.glsl",
		"SpriteShader");
	
	SpriteShader->Bind();
	SpriteShader->SetInteger("sprite", 0);
	SpriteShader->SetMatrix<glm::mat4>("projection", projection, MATRIX_4F);

	GameData::RenderData::SpriteTexture = std::make_shared<Texture>("Resources/Sprite/Textures/awesomeface.png", "SpriteTexture");

	GameData::Renderer = std::make_shared<SpriteRenderer>(SpriteShader);
	
	// Background
	GameData::RenderData::Background = std::make_shared<Texture>("Resources/background.jpg", "Background");

	// Level
	Level level1;
	level1.LoadLevelFromFile("Resources/Levels/1.lvl", m_Width, m_Height);

	m_Levels.push_back(level1);

	m_CurrentLevel = 0;
}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
}

void Game::Render()
{
	//GameData::Renderer->DrawSprite(ResourceManager::GetTexture("SpriteTexture"), glm::vec2(200.0f, 200.0f),
	//	glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	
	if (State == GameState::ACTIVE)
	{
		GameData::Renderer->DrawSprite(ResourceManager::GetTexture("Background"),
			glm::vec2(0.0f, 0.0f), glm::vec2(m_Width, m_Height), 0.0f);

		m_Levels[m_CurrentLevel].Draw(GameData::Renderer);
	}
}
