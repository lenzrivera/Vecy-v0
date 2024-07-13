#include "ShaderProgram.h"

#include <string>

#include "GLException.h"

using namespace gly;

ShaderProgram::ShaderProgram()
    : m_id( glCreateProgram() )
{
    if (!m_id)
		throw GLException("Failed to create shader program.");
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_id);
}


GLuint ShaderProgram::id() const
{
    return m_id;
}


void ShaderProgram::attach(const Shader& shader) const
{
    glAttachShader(id(), shader.id());
}

void ShaderProgram::attachFile(GLenum type, const char* path) const
{
    const Shader shader(type);
    shader.loadFile(path);

    attach(shader);
}

void ShaderProgram::attachSourceString(GLenum type, const char* sourceString) const
{
    const Shader shader(type);
    shader.loadSourceString(sourceString);

    attach(shader);
}

void ShaderProgram::link() const
{
    glLinkProgram(m_id);

	// Check for linking errors:
    GLint success;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);

    if (!success)
    {
		char errorMsg[1024];
		glGetShaderInfoLog(m_id, sizeof(errorMsg), nullptr, errorMsg);

		std::string msg = "Shader program linking error(s):\n";
		msg.append(errorMsg);

		throw GLException(msg);
    }
}


Uniform ShaderProgram::getUniform(const char* name) const
{
    return Uniform(m_id, name);
}


void ShaderProgram::use() const
{
    glUseProgram(m_id);
}