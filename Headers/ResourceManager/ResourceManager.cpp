#include "ResourceManager.hpp"
#include "Renderer.hpp"
#include <iostream>

/*Shader*/

std::unordered_map<std::string, std::shared_ptr<Shader>> ResourceManager::ShaderCache;
std::unordered_map<std::string, std::shared_ptr<Texture>> ResourceManager::TextureCache;

Shader ResourceManager::LoadShaderFromFile(const std::string& VSPath, const std::string& FSPath, const std::string& name)
{
	return {VSPath, FSPath, name};
}

void ResourceManager::CacheShader(Shader& shader,const std::string& name)
{
	ResourceManager::ShaderCache[name] = std::make_shared<Shader>(shader);
}

Shader& ResourceManager::GetShader(const std::string& name)
{
	return *ShaderCache[name];
}

Texture ResourceManager::LoadTextureFromFile(const std::string& path, const std::string& name)
{
	return {path, name};
}

/*Texture*/
void ResourceManager::CacheTexture(Texture& texture, const std::string& name)
{
	ResourceManager::TextureCache[name] = std::make_shared<Texture>(texture);
}

Texture& ResourceManager::GetTexture(const std::string& name)
{
	return *TextureCache[name];
}
