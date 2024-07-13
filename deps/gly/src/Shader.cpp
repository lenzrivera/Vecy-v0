#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

#include "GLException.h"

using namespace gly;

Shader::Shader(GLenum type)
    : m_id( glCreateShader(type) )
{
	if (!m_id)
		throw GLException("Failed to create shader");
}

Shader::~Shader()
{
	glDeleteShader(m_id);
}


GLuint Shader::id() const
{
    return m_id;
}


void Shader::loadFile(const char* path) const
{
	std::ifstream shaderFile(path);

	if (!shaderFile.is_open())
	{
		std::string msg = "Failed to open shader file at \"";
		msg.append(path);
		msg.append("\".");

		throw GLException(msg);
	}

	std::stringstream shaderFileBuffer;
	shaderFileBuffer << shaderFile.rdbuf();

	std::string shaderFileContents = std::move( shaderFileBuffer.str() );

	// Note that we can't just pass `shaderFileBuffer.str().data()` into `src`
	// because `shaderFileBuffer.str()` would delete the string pointer after
	// the whole expression had been evaluated, leaving a dangling pointer.
	loadSourceString(shaderFileContents.data());
}

void Shader::loadSourceString(const char* source) const
{
    glShaderSource(m_id, 1, &source, nullptr);
	glCompileShader(m_id);

	// Check for compilation errors:
	GLint success;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
	
	if (!success)
	{
		char errorMsg[1024];
		glGetShaderInfoLog(m_id, sizeof(errorMsg), nullptr, errorMsg);

		std::string msg = "Shader compilation error(s):\n";
		msg.append(errorMsg);

		std::cerr << msg;

		throw GLException(msg);
	}
}