#pragma once
#include "Ball/Ball.hpp"
#include "Levels/Tile.hpp"
#include <tuple>

enum class Direction{
	UP = 0,
	RIGHT,
	DOWN,
	LEFT
};

Direction VectorDirection(glm::vec2 target)
{
	glm::vec2 Compass[] = {
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};

	/*
		Algorithm:
			Compute Angle along all the direction vectors
			Maximum Angle => Ball Aligned to that Direction
				Reason: Angle with far away axis will be negative, and we take two closest that would be positive, maximum is to taken.
	*/

	float Max = 0.0f;
	unsigned int BestMatch = -1;
	for (unsigned int i = 0; i < 4; i++)
	{
		float Angle = glm::dot(glm::normalize(target), Compass[i]);
		if (Angle > Max)
		{
			Max = Angle;
			BestMatch = i;
		}
	}

	return (Direction)BestMatch;
}

typedef std::tuple<bool, Direction, glm::vec2> CollisionInfo;

template<typename T>
CollisionInfo CheckCollision(T& AABB, BallObject& ball)
{
	glm::vec2 Ball_Center = ball.GetCenter();
	glm::vec2 Tile_HalfExtents = AABB.GetHalfExtents();
	glm::vec2 Tile_Center = AABB.GetCenter(Tile_HalfExtents);

	// Distance between Ball Center and Tile Center
	glm::vec2 Distance = Ball_Center - Tile_Center;

	glm::vec2 Clamped = glm::clamp(Distance, -Tile_HalfExtents, Tile_HalfExtents);
	glm::vec2 VectorOnTile = Tile_Center + Clamped;

	/*
		Computing Distance from Tile Center to Ball Center.
		if Distance > Radius:
			Ball is Outside the Tile
			=> No Collision
		if Distance <= Radius:
			Ball is inside the Tile
			=> Collision
	*/

	Distance = VectorOnTile - Ball_Center;

	if (glm::length(Distance) <= ball.m_Radius)
		return std::make_tuple(true, VectorDirection(Distance), Distance);
	else
		return std::make_tuple(false, Direction::UP, glm::vec2(0.0f, 0.0f));
}