#include "Shader.h"

#include <cassert>
#include <fstream>
#include <sstream>

using namespace ggl;

Shader::Shader(GLenum type, const char* sourceString)
	: id(0), uniformNames(parseUniformNames(sourceString))
{
	id = glCreateShader(type);
	glShaderSource(id, 1, &sourceString, nullptr);
	glCompileShader(id);

	// Check for compilation errors:
	GLint success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char errorMsg[1024];
		glGetShaderInfoLog(id, sizeof(errorMsg), nullptr, errorMsg);

		std::string msg = "Shader compilation error(s):\n";
		msg.append(errorMsg);

		// TODO: Handle this properly
		assert(false);
	}
}

Shader::Pointer Shader::fromFile(GLenum type, const char* filePath)
{
	std::ifstream shaderFile(filePath);

	if (!shaderFile.is_open())
	{
		std::string msg = "Failed to open shader file at \"";
		msg.append(filePath);
		msg.append("\".");

		// TODO: Handle this properly.
		assert(false);
	}

	std::stringstream shaderFileBuffer;
	shaderFileBuffer << shaderFile.rdbuf();

	std::string shaderFileContents = std::move(shaderFileBuffer.str());

	// Note that we can't just pass `shaderFileBuffer.str().data()` into `src`
	// because `shaderFileBuffer.str()` would delete the string pointer after
	// the whole expression had been evaluated, leaving a dangling pointer.
	return fromSourceString(type, shaderFileContents.data());
}

Shader::Pointer Shader::fromSourceString(GLenum type, const char* sourceString)
{
	// Bypass std::make_unique() since it can't access the constructor.
	Shader* shader = new Shader(type, sourceString);
	return Shader::Pointer(shader);
}

Shader::~Shader()
{
	glDeleteShader(id);
}


std::vector<std::string> Shader::parseUniformNames(std::string sourceString) const
{
	std::vector<std::string> uniformNames;

	// TODO: Make the parser more robust, because:
	// 1.) Will fail if the shader code is only in one line (no newlines, only 
	//	   separated by semicolons)
	// 2.) Will fail if the uniform declarations have more than one space in between
	//	   (e.g. "uniform    vec4   u_vector;" - yes it's exaggerated, I know.)
	
	std::string line;
	std::stringstream sourceStream(sourceString);
	while (std::getline(sourceStream, line))
	{
		auto indexAfterUniformKeyWord = line.find(" ");
		if (line.substr(0, indexAfterUniformKeyWord) == "uniform")
		{
			auto typePos = line.find(" ", indexAfterUniformKeyWord + 1) + 1;
			auto uniformName = line.substr(typePos, line.length() - typePos - 1);

			uniformNames.push_back(uniformName);
		}
	}

	return uniformNames;
}


GLuint Shader::getId() const
{
	return id;
}

const std::vector<std::string>& Shader::getUniformNames() const
{
	return uniformNames;
}