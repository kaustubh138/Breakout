#pragma once
#include "Buffer\VertexBuffer\VertexBuffer.hpp"
#include "Buffer\VertexBuffer\VertexBufferLayout.hpp"

class VertexArray
{
private:
	unsigned int m_VertexArrayID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	
	void Bind() const;
	void Unbind() const;

	// utility
	unsigned int GetID() { return m_VertexArrayID; };
};