#pragma once
#include "Ball/Ball.hpp"
#include "Levels/Tile.hpp"

bool CheckCollision(Tile& tile, BallObject& ball)
{
	glm::vec2 Ball_Center = ball.GetCenter();
	glm::vec2 Tile_HalfExtents = tile.GetHalfExtents();
	glm::vec2 Tile_Center = tile.GetCenter(Tile_HalfExtents);

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

	return glm::length(Distance) < ball.m_Radius;
}