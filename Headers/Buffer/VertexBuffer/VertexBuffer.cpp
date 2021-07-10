#include "VertexBuffer.hpp"
#include "Renderer.hpp"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	: m_VertexBufferID(0)
{
	glGenBuffers(1, &m_VertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_VertexBufferID);
}

// move constructor
VertexBuffer::VertexBuffer(VertexBuffer&& other)
{
	m_VertexBufferID = other.m_VertexBufferID;
	other.m_VertexBufferID = NULL;
}

// copy constructor
VertexBuffer::VertexBuffer(const VertexBuffer& other)
{
	memcpy(&m_VertexBufferID, &other.m_VertexBufferID, sizeof(m_VertexBufferID));
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
