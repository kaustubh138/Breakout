#include "VertexArray.hpp"
#include "Renderer.hpp"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_VertexArrayID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_VertexArrayID);
}


void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	glBindVertexArray(m_VertexArrayID);
	
	unsigned int offset = 0;
	const auto& elements = layout.GetElements();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count,
			element.type,
			element.normalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(), (const void*)offset);

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
	
	glBindVertexArray(0);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_VertexArrayID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
