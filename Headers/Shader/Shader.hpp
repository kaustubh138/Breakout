#pragma once

#include <string>
#include <unordered_map>

#include "Renderer.hpp"

class ShaderBuilder
{
private:
	void ParseShader(const std::string& vsPath, const std::string& fsPath);
protected:
	unsigned int m_ShaderID = 0;
	std::string VertexShaderCode;
	std::string FragmentShaderCode;

	unsigned int CompileShader(std::string& source, unsigned int type);
	void CreateShader(const std::string& VertexShaderPath, const std::string& FragmentShaderPath);
};

class Shader
	: ShaderBuilder
{
private:
	std::string m_FilePathVS;
	std::string m_FilePathFS;
	std::string name;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& vsPath, const std::string& fsPath, const std::string& name);
	~Shader();

	template <typename t>
	void SetUniform(const std::string name, const unsigned int count, const t* value)
	{
		switch ((char)typeid(value[0]).name())
		{
			// integer
		case 'i':
			switch (count)
			{
			case 1:
				glUniform1iv(GetUniformLocation(name), count, (const GLint*)value);
				break;
			case 2:
				glUniform2iv(GetUniformLocation(name), count, (const GLint*)value);
				break;
			case 3:
				glUniform3iv(GetUniformLocation(name), count, (const GLint*)value);
				break;
			case 4:
				glUniform4iv(GetUniformLocation(name), count, (const GLint*)value);
				break;
			};

			// float
			// if not i and f, then assuming the type is "struct glm::vec<3,float,0>"
		case 'f':
		default:
			switch (count)
			{
			case 1:
				glUniform1fv(GetUniformLocation(name), count, (const GLfloat*)value);
				break;
			case 2:
				glUniform2fv(GetUniformLocation(name), count, (const GLfloat*)value);
				break;
			case 3:
				glUniform3fv(GetUniformLocation(name), count, (const GLfloat*)value);
				break;
			case 4:
				glUniform4fv(GetUniformLocation(name), count, (const GLfloat*)value);
				break;
			};
		}
	}

	template <typename t>
	void SetMatrix(const std::string&& name, t matrix, unsigned int MATRIX_TYPE, bool transpose = GL_FALSE, unsigned int count = 1)
	{
		switch (MATRIX_TYPE)
		{
		case 1:
			glUniformMatrix4fv(GetUniformLocation(name), count, transpose, glm::value_ptr(matrix));
			break;
		case 2:
			glUniformMatrix2x3fv(GetUniformLocation(name), count, transpose, glm::value_ptr(matrix));
			break;
		case 3:
			glUniformMatrix3x2fv(GetUniformLocation(name), count, transpose, glm::value_ptr(matrix));
			break;
		case 4:
			glUniformMatrix2x3fv(GetUniformLocation(name), count, transpose, glm::value_ptr(matrix));
			break;
		case 5:
			glUniformMatrix4x2fv(GetUniformLocation(name), count, transpose, glm::value_ptr(matrix));
			break;
		case 6:
			glUniformMatrix3x4fv(GetUniformLocation(name), count, transpose, glm::value_ptr(matrix));
			break;
		case 7:
			glUniformMatrix4x3fv(GetUniformLocation(name), count, transpose, glm::value_ptr(matrix));
			break;
		}
	}

	void SetInteger(const std::string&& name, unsigned int value);

	// utility functions
	unsigned int GetProgramID();
	
	void Bind() const;
	void Unbind() const;
	
	int GetUniformLocation(const std::string& name);
};