#pragma once
#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <unordered_map>
#include <string>
#include <memory>

#include "Shader/Shader.hpp"
#include "Texture/Texture.hpp"

struct ResourceManager
	: public Shader, public Texture
{
	static std::unordered_map<std::string, std::shared_ptr<Shader>> ShaderCache;
	static std::unordered_map<std::string, std::shared_ptr<Texture>> TextureCache;

	/*Shader*/
	static Shader LoadShaderFromFile(const std::string& VSPath, const std::string& FSPath, const std::string& name);
	static void CacheShader(Shader& shader, const std::string& name);
	static Shader& GetShader(const std::string& name);

	/*Texture*/
	static Texture LoadTextureFromFile(const std::string & path, const std::string & name);
	static void CacheTexture(Texture& texture, const std::string& name);
	static Texture& GetTexture(const std::string& name);
};


#endif