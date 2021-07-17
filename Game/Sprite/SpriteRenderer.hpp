#pragma once

#ifndef  SPRITE_RENDERER_H
#define  SPRITE_RENDERER_H

#include "Shader/Shader.hpp"
#include "Texture/Texture.hpp"
#include "Containers/VertexArray.hpp"
#include <memory>

class SpriteRenderer
{
private:
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<Texture> m_Texture;
	std::shared_ptr<VertexArray> m_VAO;
	std::shared_ptr<VertexBuffer> m_VBO;
private:
	float m_Vertices[6 * 4] = 
	{
		// pos      // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

private:
	void init();
public:
	SpriteRenderer(std::shared_ptr<Shader> shader);

	void DrawSprite(std::shared_ptr<Texture> texture,
		glm::vec2 position,
		glm::vec2 size = glm::vec2(10.0f, 10.0f),
		float rotate = 0.0f, glm::vec3 color = glm::vec3(0.2f, 0.2f, 0.5f));
};

#endif // ! SPRITE_RENDERER_H
