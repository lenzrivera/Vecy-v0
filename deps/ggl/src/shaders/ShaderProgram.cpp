#include "ShaderProgram.h"

#include <cassert>

#include <glm/ext.hpp>

using namespace ggl;

ShaderProgram::ShaderProgram(std::initializer_list<Shader::Pointer> shaders)
	: id( createShaderProgram(shaders) ), uniforms(consolidateUniforms(shaders))
{
}

ShaderProgram::Pointer ShaderProgram::fromFiles(
	const char* vertex, const char* fragment)
{
	return fromShaders({ 
		Shader::fromFile(GL_VERTEX_SHADER, vertex), 
		Shader::fromFile(GL_FRAGMENT_SHADER, fragment) });
}

ShaderProgram::Pointer ShaderProgram::fromFiles(
	const char* vertex, const char* geometry, const char* fragment)
{
	return fromShaders({
		Shader::fromFile(GL_VERTEX_SHADER, vertex),
		Shader::fromFile(GL_GEOMETRY_SHADER, geometry),
		Shader::fromFile(GL_FRAGMENT_SHADER, fragment) });
}

ShaderProgram::Pointer ShaderProgram::fromShaders(
	std::initializer_list<Shader::Pointer> shaders)
{
	// Bypass std::make_unique() since it can't access the constructor.
	ShaderProgram* shaderProgram = new ShaderProgram(shaders);
	return ShaderProgram::Pointer(shaderProgram);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(id);
}


GLuint ShaderProgram::createShaderProgram(
	std::initializer_list<Shader::Pointer> shaders) const
{
	GLuint programId = glCreateProgram();

	for (auto const& shader : shaders)
		glAttachShader(programId, shader->getId());

	glLinkProgram(programId);

	// Shaders not detached will accordingly not be deleted until they are.
	for (auto const& shader : shaders)
		glDetachShader(programId, shader->getId());

	// Check for linking errors:
	GLint success;
	glGetProgramiv(programId, GL_LINK_STATUS, &success);

	if (!success)
	{
		char errorMsg[1024];
		glGetShaderInfoLog(programId, sizeof(errorMsg), nullptr, errorMsg);

		std::string msg = "Shader program linking error(s):\n";
		msg.append(errorMsg);

		// TODO: Handle this properly
		assert(false);
	}

	return programId;
}

std::unordered_map<std::string, GLuint> ShaderProgram::consolidateUniforms(
	std::initializer_list<Shader::Pointer> shaders) const
{
	std::unordered_map<std::string, GLuint> uniforms;

	for (auto const& shader : shaders)
		for (auto const& uniformName : shader->getUniformNames())
			uniforms[uniformName] = glGetUniformLocation(id, uniformName.c_str());

	return uniforms;
}


GLuint ShaderProgram::getId() const
{
	return id;
}

const std::unordered_map<std::string, GLuint>& ShaderProgram::getUniforms() const
{
	return uniforms;
}


void ShaderProgram::use() const
{
	glUseProgram(id);
}


// Uniform Setters //

void ShaderProgram::setUniform(const char* name, int value) const
{
	glUniform1i(uniforms.at(name), value);
}

void ShaderProgram::setUniform(const char* name, unsigned int value) const
{
	glUniform1ui(uniforms.at(name), value);
}

void ShaderProgram::setUniform(const char* name, float value) const
{
	glUniform1f(uniforms.at(name), value);
}

void ShaderProgram::setUniform(const char* name, double value) const
{
	glUniform1d(uniforms.at(name), value);
}


void ShaderProgram::setUniform(const char* name, const glm::ivec2& value) const
{
	glUniform2iv(uniforms.at(name), 1, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const char* name, const glm::uvec2& value) const
{
	glUniform2uiv(uniforms.at(name), 1, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const char* name, const glm::fvec2& value) const
{
	glUniform2fv(uniforms.at(name), 1, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const char* name, const glm::dvec2& value) const
{
	glUniform2dv(uniforms.at(name), 1, glm::value_ptr(value));
}


void ShaderProgram::setUniform(const char* name, const glm::ivec3& value) const
{
	glUniform3iv(uniforms.at(name), 1, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const char* name, const glm::uvec3& value) const
{
	glUniform3uiv(uniforms.at(name), 1, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const char* name, const glm::fvec3& value) const
{
	glUniform3fv(uniforms.at(name), 1, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const char* name, const glm::dvec3& value) const
{
	glUniform3dv(uniforms.at(name), 1, glm::value_ptr(value));
}


void ShaderProgram::setUniform(const char* name, const glm::ivec4& value) const
{
	glUniform4iv(uniforms.at(name), 1, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const char* name, const glm::uvec4& value) const
{
	glUniform4uiv(uniforms.at(name), 1, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const char* name, const glm::fvec4& value) const
{
	glUniform4fv(uniforms.at(name), 1, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const char* name, const glm::dvec4& value) const
{
	glUniform4dv(uniforms.at(name), 1, glm::value_ptr(value));
}


void ShaderProgram::setUniform(const char* name, const glm::fmat2x2& value) const
{
	glUniformMatrix2fv(uniforms.at(name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const char* name, const glm::dmat2x2& value) const
{
	glUniformMatrix2dv(uniforms.at(name), 1, GL_FALSE, glm::value_ptr(value));
}


void ShaderProgram::setUniform(const char* name, const glm::fmat3x3& value) const
{
	glUniformMatrix3fv(uniforms.at(name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const char* name, const glm::dmat3x3& value) const
{
	glUniformMatrix3dv(uniforms.at(name), 1, GL_FALSE, glm::value_ptr(value));
}


void ShaderProgram::setUniform(const char* name, const glm::fmat4x4& value) const
{
	glUniformMatrix4fv(uniforms.at(name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const char* name, const glm::dmat4x4& value) const
{
	glUniformMatrix4dv(uniforms.at(name), 1, GL_FALSE, glm::value_ptr(value));
}


// Uniform Array Setters //

template<std::size_t N>
void ShaderProgram::setUniform(const char* name, const std::array<int, N>& value) const
{
	glUniformiv(uniforms.at(name), N, glm::value_ptr(value));
}

template<std::size_t N>
void ShaderProgram::setUniform(const char* name, const std::array<unsigned int, N>& value) const
{
	glUniformuiv(uniforms.at(name), N, glm::value_ptr(value));
}

template<std::size_t N>
void ShaderProgram::setUniform(const char* name, const std::array<float, N>& value) const
{
	glUniformfv(uniforms.at(name), N, glm::value_ptr(value));
}

template<std::size_t N>
void ShaderProgram::setUniform(const char* name, const std::array<double, N>& value) const
{
	glUniformdv(uniforms.at(name), N, glm::value_ptr(value));
}