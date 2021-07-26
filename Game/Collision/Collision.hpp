#pragma once
#include "Ball/Ball.hpp"
#include "Levels/Tile.hpp"

bool CheckCollision(Tile& tile, BallObject& ball)
{
	bool CollisionX = (tile.GetAABB('x') >= ball.GetPosition().x) &&
					  (ball.GetAABB('x') >= tile.GetPosition().x);

	bool CollisionY = (tile.GetAABB('y') >= ball.GetPosition().y) &&
					  (ball.GetAABB('y') >= tile.GetPosition().y);

	return CollisionX && CollisionY;
}