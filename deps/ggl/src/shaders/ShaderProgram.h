#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <array>
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <string>
#include <unordered_map>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.h"

namespace ggl {

	class ShaderProgram
	{
	private:
		GLuint id;
		std::unordered_map<std::string, GLuint> uniforms;

		ShaderProgram(std::initializer_list<Shader::Pointer> shaders);

		GLuint createShaderProgram(
			std::initializer_list<Shader::Pointer> shaders) const;
		std::unordered_map<std::string, GLuint> consolidateUniforms(
			std::initializer_list<Shader::Pointer> shaders) const;

	public:
		typedef std::unique_ptr<ShaderProgram> Pointer;

		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram(const ShaderProgram&&) = delete;

		static Pointer fromFiles(const char* vertex, const char* fragment);
		static Pointer fromFiles(
			const char* vertex, const char* geometry, const char* fragment);
		static Pointer fromShaders(std::initializer_list<Shader::Pointer> shaders);

		~ShaderProgram();

		GLuint getId() const;
		const std::unordered_map<std::string, GLuint>& getUniforms() const;

		void use() const;

		// Uniform Setters //

		void setUniform(const char* name, int value) const;
		void setUniform(const char* name, unsigned int value) const;
		void setUniform(const char* name, float value) const;
		void setUniform(const char* name, double value) const;

		void setUniform(const char* name, const glm::ivec2& value) const;
		void setUniform(const char* name, const glm::uvec2& value) const;
		void setUniform(const char* name, const glm::fvec2& value) const;
		void setUniform(const char* name, const glm::dvec2& value) const;

		void setUniform(const char* name, const glm::ivec3& value) const;
		void setUniform(const char* name, const glm::uvec3& value) const;
		void setUniform(const char* name, const glm::fvec3& value) const;
		void setUniform(const char* name, const glm::dvec3& value) const;

		void setUniform(const char* name, const glm::ivec4& value) const;
		void setUniform(const char* name, const glm::uvec4& value) const;
		void setUniform(const char* name, const glm::fvec4& value) const;
		void setUniform(const char* name, const glm::dvec4& value) const;

		void setUniform(const char* name, const glm::fmat2x2& value) const;
		void setUniform(const char* name, const glm::dmat2x2& value) const;

		void setUniform(const char* name, const glm::fmat3x3& value) const;
		void setUniform(const char* name, const glm::dmat3x3& value) const;

		void setUniform(const char* name, const glm::fmat4x4& value) const;
		void setUniform(const char* name, const glm::dmat4x4& value) const;

		// Uniform Array Setters //
		
		template<std::size_t N>
		void setUniform(const char* name, const std::array<int, N>& value) const;
		template<std::size_t N>
		void setUniform(const char* name, const std::array<unsigned int, N>& value) const;
		template<std::size_t N>
		void setUniform(const char* name, const std::array<float, N>& value) const;
		template<std::size_t N>
		void setUniform(const char* name, const std::array<double, N>& value) const;

		// TODO: This is incomplete (if we do finish this good luck). 
	};

}

#endif