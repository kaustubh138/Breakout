#include "Game.hpp"
#include "Sprite/SpriteRenderer.hpp"
#include "ResourceManager/ResourceManager.hpp"

namespace GameData
{
	std::shared_ptr<SpriteRenderer> Renderer;
}

Game::Game(unsigned int width, unsigned int height)
	: State(GameState::ACTIVE), m_Keys(), m_Width(width), m_Height(height)
{}

Game::~Game()
{

}

void Game::init()
{
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->m_Width), static_cast<float>(this->m_Height), 0.0f, -1.0f, 1.0f);

	std::shared_ptr<Shader> SpriteShader = std::make_shared<Shader>("Resources/Sprite/Shaders/VertexShader.glsl",
		"Resources/Sprite/Shaders/FragmentShader.glsl",
		"SpriteShader");
	
	SpriteShader->Bind();
	SpriteShader->SetInteger("sprite", 0);
	SpriteShader->SetMatrix<glm::mat4>("projection", projection, MATRIX_4F);

	std::shared_ptr<Texture> SpriteTexture = std::make_shared<Texture>("Resources/Sprite/Textures/soccer_ball.jpg", "SpriteTexture");

	GameData::Renderer = std::make_shared<SpriteRenderer>(SpriteShader, SpriteTexture);
}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
}

void Game::Render()
{
	GameData::Renderer->DrawSprite(glm::vec2(200.0f, 200.0f),
		glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
