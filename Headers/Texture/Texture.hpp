#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <memory>
#include <string>

class Texture
{
private:
	unsigned int m_TextureID;
	std::string m_FilePath, name;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& path, const std::string& name);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	// utilty 
	inline int GetWidth() const { return m_Width; };
	inline int GetHeight() const { return m_Width; };
};

#endif