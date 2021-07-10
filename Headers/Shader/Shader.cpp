#include "Shader.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Renderer.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

void ShaderBuilder::ParseShader(const std::string& vsPath, const std::string& fsPath)
{
	std::ifstream vsFile;
	std::ifstream fsFile;

	vsFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fsFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);

	try
	{
		//open file
		vsFile.open(vsPath.c_str());
		fsFile.open(fsPath.c_str());

		std::stringstream vsStream, fsStream;

		vsStream << vsFile.rdbuf();
		fsStream << fsFile.rdbuf();

		vsFile.close();
		fsFile.close();

		VertexShaderCode = vsStream.str();
		FragmentShaderCode = fsStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "[ERROR] an error occured while reading Shader file.." << std::endl;
	}
}

unsigned int ShaderBuilder::CompileShader(std::string& source, unsigned int type)
{
	const char* src = &source[0];

	unsigned int Shader = glCreateShader(type);
	glShaderSource(Shader, 1, &src, nullptr);
	glCompileShader(Shader);

	// error handling
	int success;
	char infoLog[512];
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(Shader, 512, NULL, infoLog);
		std::cerr << "[ERROR] Shader fragment compilation failed\n"
			<< infoLog << std::endl;
	}

	return Shader;
}

void ShaderBuilder::CreateShader(const std::string& vsPath, const std::string& fsPath)
{
	ParseShader(vsPath, fsPath);

	this->m_ShaderID = glCreateProgram();

	unsigned int vsID = CompileShader(VertexShaderCode, GL_VERTEX_SHADER);
	unsigned int fsID = CompileShader(FragmentShaderCode, GL_FRAGMENT_SHADER);

	glAttachShader(m_ShaderID, vsID);
	glAttachShader(m_ShaderID, fsID);

	glLinkProgram(m_ShaderID);

	glValidateProgram(m_ShaderID);

	glDeleteShader(vsID);
	glDeleteShader(fsID);
}

unsigned int Shader::GetProgramID()
{
	return m_ShaderID;
}


Shader::Shader(const std::string& vsPath, const std::string& fsPath, const std::string& name)
	:m_FilePathVS(vsPath), m_FilePathFS(fsPath), name(name)
{
	CreateShader(vsPath, fsPath);
	m_UniformLocationCache["init"] = 0;
	ResourceManager::CacheShader(*this, this->name);
}

Shader::~Shader()
{
	glDeleteShader(this->m_ShaderID);
}

void Shader::Bind() const
{
	int exist;
	glGetProgramiv(this->m_ShaderID, GL_VALIDATE_STATUS, &exist);
	if (exist)
	{
		glUseProgram(this->m_ShaderID);
	}
	else
		std::cerr << "[ERROR] Shader does not exist!" << std::endl;
}
void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetInteger(const std::string&& name, unsigned int value)
{
	glUniform1i(GetUniformLocation(name.c_str()), value);
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name.c_str()) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name.c_str()];

	int location = glGetUniformLocation(m_ShaderID, name.c_str());
	if (location == -1)
		std::cerr << "[WARNING] Uniform " << name << "might not exist!" << std::endl;
	
	m_UniformLocationCache[name] = location;
	return location;
}
