#include "Game.hpp"
#include "Paddle/Paddle.hpp"
#include "Ball/Ball.hpp"
#include "Collision/Collision.hpp"
#include "Sprite/SpriteRenderer.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Levels/Level.hpp"

namespace GameData
{
	std::shared_ptr<SpriteRenderer> Renderer;
	std::shared_ptr<Paddle> Player;
	std::shared_ptr<BallObject> Ball;

	namespace RenderData
	{
		std::shared_ptr<Texture> SpriteTexture;
		std::shared_ptr<Texture> Background;
	}

	namespace TileData
	{
		std::shared_ptr<Texture> SolidTileTexture;
		std::shared_ptr<Texture> NormalTileTexture;
	}

	namespace PaddleData
	{
		const glm::vec2 PlayerSize(100.0f, 20.0f);
		const glm::vec2 PlayerVelocity(500.0f, 0.0f);
		std::shared_ptr<Texture> PaddleTexture;
	}

	namespace BallData
	{
		const glm::vec2 InitBallVelocity(100.0f, -350.0f);
		const float BallRadius = 12.5f;
		std::shared_ptr<Texture> BallTexture;
	}
}

Game::Game(unsigned int width, unsigned int height)
	: State(GameState::ACTIVE), m_Keys(), m_Width(width), m_Height(height), m_CurrentLevel(0)
{}

Game::~Game()
{

}

void Game::init()
{
	using namespace GameData;
	// Sprite: Ball
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->m_Width), static_cast<float>(this->m_Height), 0.0f, -1.0f, 1.0f);

	std::shared_ptr<Shader> SpriteShader = std::make_shared<Shader>("Resources/Sprite/Shaders/VertexShader.glsl",
		"Resources/Sprite/Shaders/FragmentShader.glsl",
		"SpriteShader");
	
	SpriteShader->Bind();
	SpriteShader->SetInteger("sprite", 0);
	SpriteShader->SetMatrix<glm::mat4>("projection", projection, MATRIX_4F);

	Renderer = std::make_shared<SpriteRenderer>(SpriteShader);
	
	// Background
	RenderData::Background = std::make_shared<Texture>("Resources/background.jpg", "Background");

	// Level
	TileData::SolidTileTexture = std::make_shared<Texture>("Resources/Blocks/block.png", "Block");
	TileData::NormalTileTexture = std::make_shared<Texture>("Resources/Blocks/block_solid.png", "SolidBlock");
	m_Level.LoadLevelFromFile("Resources/Levels/1.lvl", m_Width, m_Height);
	m_CurrentLevel = 1;

	// Paddle
	PaddleData::PaddleTexture = std::make_shared<Texture>("Resources/Paddle/paddle.png", "Paddle");
	Player = std::make_shared<Paddle>(GameData::PaddleData::PaddleTexture, m_Width, m_Height, GameData::PaddleData::PlayerSize, GameData::PaddleData::PlayerVelocity);
	
	// Ball
	BallData::BallTexture = std::make_shared<Texture>("Resources/Ball/awesomeface.png", "Ball");
	glm::vec2 BallPosition = Player->m_Position + glm::vec2(PaddleData::PlayerSize.x / 2.0f - BallData::BallRadius, -BallData::BallRadius * 2.0f);
	Ball = std::make_shared<BallObject>(GameData::BallData::BallTexture, BallPosition, BallData::BallRadius, BallData::InitBallVelocity);
}

void Game::ProcessInput(GLFWwindow* window, float dt)
{
	using namespace GameData;
	if (State == GameState::ACTIVE)
	{
		float velocity = Player->m_Velocity.x * dt;
		
		// move playerboard
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			if (Player->m_Position.x >= 0.0f)
				Player->m_Position.x -= velocity;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			if (Player->m_Position.x <= m_Width - Player->m_Size.x)
				Player->m_Position.x += velocity;
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			Ball->Release();
		}
	}
}

void Game::PollCollisions()
{
	using namespace GameData;
	for (Tile& tile : m_Level)
	{
		if (!tile.GetDestroyed())
		{
			CollisionInfo Collision = CheckCollision<Tile>(tile, *GameData::Ball);
			if (std::get<0>(Collision))
			{
				if (!tile.GetSolidity())
					tile.Destroy();
				
				// collision resolution
				Direction CollisionDirection = std::get<1>(Collision);
				glm::vec2 DiffrenceVector = std::get<2>(Collision);

				if (CollisionDirection == Direction::LEFT || CollisionDirection == Direction::RIGHT)
				{
					Ball->m_Velocity.x = -Ball->m_Velocity.x; 
					
					// Reposition Ball outside the tile
					float Offset = Ball->m_Radius - std::abs(DiffrenceVector.x);
					
					if (CollisionDirection == Direction::LEFT)
						Ball->m_Position.x += Offset; 
					else
						Ball->m_Position.x -= Offset; 				
				}
				else
				{
					Ball->m_Velocity.y = -Ball->m_Velocity.y;
					
					// Reposition Ball outside the tile
					float Offset = Ball->m_Radius - std::abs(DiffrenceVector.y);
	
					if (CollisionDirection == Direction::UP)
						Ball->m_Position.y -= Offset;
					else
						Ball->m_Position.y += Offset;
				}
			}
		}
	}

	// Collision with Paddle
	CollisionInfo PaddleCollision = CheckCollision<Paddle>(*Player, *Ball);
	if (!Ball->GetStuck() && std::get<0>(PaddleCollision))
	{
		/*
			Further the ball hits the paddle stronger its velocity change,
			since Collision Angle is Larger, Impulse will be greater.
			Metric for increasing as Percentage Far Away is thus a suitable choice.
		*/

		float PaddleCenter = Player->GetCenter();
		float CollisionPosition = (Ball->m_Position.x + Ball->m_Radius) - PaddleCenter;
		
		float PercentageFar = CollisionPosition / (Player->m_Size.x / 2.0f);
	
		glm::vec2 VelocityCopy = Ball->m_Velocity;

		Ball->m_Velocity.x = BallData::InitBallVelocity.x * PercentageFar * 2.0f; // Increase the velocity by a factor of 2
		Ball->m_Velocity.y = -Ball->m_Velocity.y;
	
		// Adjusting y-coord according to changing x-coord
		Ball->m_Velocity = glm::normalize(Ball->m_Velocity) * glm::length(VelocityCopy);
	}
}

void Game::Update(GLFWwindow* window, float dt)
{
	GameData::Ball->Move(window, dt, m_Width, m_Height, GameData::Player->m_Position ,GameData::PaddleData::PlayerSize);
	PollCollisions();
}

void Game::Render()
{
	//GameData::Renderer->DrawSprite(ResourceManager::GetTexture("SpriteTexture"), glm::vec2(200.0f, 200.0f),
	//	glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	
	if (State == GameState::ACTIVE)
	{
		// background
		GameData::Renderer->DrawSprite(ResourceManager::GetTexture("Background"),
			glm::vec2(0.0f, 0.0f), glm::vec2(m_Width, m_Height), 0.0f);

		// paddle
		GameData::Player->DrawObject(GameData::Renderer);

		// bricks
		m_Level.Draw(GameData::Renderer);

		GameData::Ball->DrawObject(GameData::Renderer);
	}
}

