#include "Uniform.h"

#include <string>

#include "glm/gtc/type_ptr.hpp"

#include "GLException.h"

using namespace gly;

Uniform::Uniform()
	: m_location(0) 
{
}

Uniform::Uniform(GLuint programId, const char* name)
    : m_location( glGetUniformLocation(programId, name) )
{
	if (m_location == -1)
	{
		std::string msg = "Invalid uniform name: \"";
		msg.append(name);
		msg.append("\'.");

		throw GLException(msg);
	}
}


GLint Uniform::location() const 
{
    return m_location;
}


// Individual Value Setters //
// ---------------------------

void Uniform::setUniform(GLint value) const
{
	glUniform1i(m_location, value);
}

void Uniform::setUniform(GLuint value) const
{
	glUniform1ui(m_location, value);
}

void Uniform::setUniform(GLfloat value) const
{
	glUniform1f(m_location, value);
}


void Uniform::setUniform(glm::vec<2, GLint> value) const
{
	glUniform2iv(m_location, 1, glm::value_ptr(value));
}

void Uniform::setUniform(glm::vec<3, GLint> value) const
{
	glUniform3iv(m_location, 1, glm::value_ptr(value));
}

void Uniform::setUniform(glm::vec<4, GLint> value) const
{
	glUniform4iv(m_location, 1, glm::value_ptr(value));
}


void Uniform::setUniform(glm::vec<2, GLuint> value) const
{
	glUniform2uiv(m_location, 1, glm::value_ptr(value));
}

void Uniform::setUniform(glm::vec<3, GLuint> value) const
{
	glUniform3uiv(m_location, 1, glm::value_ptr(value));
}

void Uniform::setUniform(glm::vec<4, GLuint> value) const
{
	glUniform4uiv(m_location, 1, glm::value_ptr(value));
}


void Uniform::setUniform(glm::vec<2, GLfloat> value) const
{
	glUniform2fv(m_location, 1, glm::value_ptr(value));
}

void Uniform::setUniform(glm::vec<3, GLfloat> value) const
{
	glUniform3fv(m_location, 1, glm::value_ptr(value));
}

void Uniform::setUniform(glm::vec<4, GLfloat> value) const
{
	glUniform4fv(m_location, 1, glm::value_ptr(value));
}


void Uniform::setUniform(glm::mat<2, 2, GLfloat> value) const
{
	glUniformMatrix2fv(m_location, 1, GL_FALSE, glm::value_ptr(value));
}

void Uniform::setUniform(glm::mat<3, 3, GLfloat> value) const
{
	glUniformMatrix3fv(m_location, 1, GL_FALSE, glm::value_ptr(value));
}

void Uniform::setUniform(glm::mat<4, 4, GLfloat> value) const
{
	glUniformMatrix4fv(m_location, 1, GL_FALSE, glm::value_ptr(value));
}


// Array Value Setters //
// ---------------------

void Uniform::setUniform(GLint* value, GLsizei count) const
{
	glUniform1iv(m_location, count, value);
}

void Uniform::setUniform(GLuint* value, GLsizei count) const
{
	glUniform1uiv(m_location, count, value);
}

void Uniform::setUniform(GLfloat* value, GLsizei count) const
{
	glUniform1fv(m_location, count, value);
}