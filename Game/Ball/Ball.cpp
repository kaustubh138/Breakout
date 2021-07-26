#include "Ball.hpp"

BallObject::BallObject(std::shared_ptr<Texture> BallTexture, glm::vec2 Position, float Radius, glm::vec2 Velocity)
{
	m_Texture = BallTexture;
	m_Position = Position;
	m_Radius = Radius;
	m_Velocity = Velocity;
	m_Size = glm::vec2(m_Radius * 2.0f, m_Radius * 2.0f); // Ball Block Size = (Diameter, Diameter) <=> (x, y)
    m_Color = glm::vec3(1.0f);
    IsDestroyed = false;
    m_Rotation = 180.0f;

    // Copy of Original Ball Data
    OData = new OriginalData{m_Position, m_Velocity, m_Radius, m_Size};
}

BallObject::~BallObject()
{
    delete OData;
}

glm::vec2 BallObject::Move(GLFWwindow* window,float dt, unsigned int ScreenWidth, unsigned int ScreenHeight, glm::vec2 PaddlePosition, glm::vec2 PaddleSize)
{
    if (IsStuck)
    {
        m_Position = ComputePosition(PaddlePosition, PaddleSize);
    }

    else
    {
        m_Position += m_Velocity * dt;
    
        // Handle x-positions
        if (m_Position.x <= 0.0f)
        {
            // Not collided with any edge (right or left)
            m_Velocity.x = -m_Velocity.x;
            m_Position.x = 0.0f;
        }
        else if (m_Position.x + m_Size.x >= ScreenWidth)
        {
            // Collided with edge (right or left)
            m_Velocity.x = -m_Velocity.x;
            m_Position.x = ScreenWidth - m_Size.x;
        }
        
        if (m_Position.y <= 0.0f)
        {
            // If collided with (edge top or bottom)
            m_Velocity.y = -m_Velocity.y;
            m_Position.y = 0.0f;
        }
    }
    return m_Position;
}

void BallObject::Reset()
{
    m_Position = OData->OPosition;
    m_Radius = OData->ORadius;
    m_Velocity = OData->OVelocity;
    m_Size = OData->OSize;
}

