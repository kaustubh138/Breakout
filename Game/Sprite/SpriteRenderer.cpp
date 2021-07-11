#include "SpriteRenderer.hpp"

void SpriteRenderer::init()
{
	m_VAO = std::make_shared<VertexArray>();
	m_VBO = std::make_shared<VertexBuffer>(m_Vertices, sizeof(m_Vertices));
	VertexBufferLayout Layout;
	Layout.Push<float>(4);
	m_VAO->AddBuffer(*m_VBO, Layout);
}

SpriteRenderer::SpriteRenderer(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
{
	m_Shader = shader;
	m_Texture = texture;
	init();
}

void SpriteRenderer::DrawSprite(glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
	/*
		Model Matrix:
			Step 1: Translate to the position
			Step 2: Rotate
				Step 2.1: Translate the point of rotation to center
				Step 2.2: Rotate around origin
				Step 2.3: Translate object back to normal
			Step 3: Scale to fit.
	*/

	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));  // translate origin to center
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate along z
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));  // reset origin translation
	
	model = glm::scale(model, glm::vec3(size, 1.0f));

	m_Texture->Bind();

	m_Shader->Bind();
	m_Shader->SetMatrix<glm::mat4>("model", model, MATRIX_4F);
	glUniform3f(glGetUniformLocation(m_Shader->GetProgramID(), "sprite_color"), color.x, color.y, color.z);

	m_VAO->Bind();
	m_VBO->Bind();

	glDrawArrays(GL_TRIANGLES, 0, 6);
}


