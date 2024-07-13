#ifndef SHADER_H
#define SHADER_H

#include <memory>
#include <string>
#include <vector>

#include <GL/glew.h>

namespace ggl {

	class Shader
	{
	protected:
		GLuint id;
		std::vector<std::string> uniformNames;

		Shader(GLenum type, const char* sourceString);

		std::vector<std::string> parseUniformNames(std::string sourceString) const;

	public:
		typedef std::unique_ptr<Shader> Pointer;

		Shader() = delete;
		Shader(const Shader&) = delete;
		Shader(const Shader&&) = delete;

		static Pointer fromFile(GLenum type, const char* filePath);
		static Pointer fromSourceString(GLenum type, const char* sourceString);

		~Shader();

		GLuint getId() const;
		const std::vector<std::string>& getUniformNames() const;
	};

}

#endif