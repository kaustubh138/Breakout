#pragma once

class VertexBuffer
{
private:
	unsigned int m_VertexBufferID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	// move constructor
	VertexBuffer(VertexBuffer&& other);

	// copy constructor
	VertexBuffer(const VertexBuffer& other);

	void Bind() const;
	void Unbind() const;

	// utility
	unsigned int GetBufferID() { return m_VertexBufferID; };
};