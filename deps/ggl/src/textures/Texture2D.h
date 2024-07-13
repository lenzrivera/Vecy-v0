#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

#include <memory>

#include <GL/glew.h>
#include <stb_image.h>

namespace ggl {

	class Texture2D
	{
	private:
		GLuint id;
		int width, height;

		Texture2D(
			const void* data,
			int width,
			int height,
			unsigned int slot,

			GLenum givenDataFormat = GL_RGBA,
			GLenum internalFormat = GL_RGBA,

			GLenum minScaleFilter = GL_LINEAR,
			GLenum maxScaleFilter = GL_LINEAR,

			GLenum horizontalWrappingMode = GL_CLAMP_TO_BORDER,
			GLenum verticalWrappingMode = GL_CLAMP_TO_BORDER,

			GLenum internalDataType = GL_UNSIGNED_BYTE);

	public:
		typedef std::unique_ptr<Texture2D> Pointer;

		enum class StbiFormat {
			DEFAULT = STBI_default,
			GREY = STBI_grey,
			GREY_ALPHA = STBI_grey_alpha,
			RGB = STBI_rgb,
			RGBA = STBI_rgb_alpha
		};

		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D(const Texture2D&&) = delete;

		static Pointer fromData(
			const void* data,
			int width,
			int height,
			unsigned int slot,

			GLenum givenDataFormat = GL_RGBA,
			GLenum internalFormat = GL_RGBA,

			GLenum minScaleFilter = GL_LINEAR,
			GLenum maxScaleFilter = GL_LINEAR,

			GLenum horizontalWrappingMode = GL_CLAMP_TO_BORDER,
			GLenum verticalWrappingMode = GL_CLAMP_TO_BORDER,

			GLenum internalDataType = GL_UNSIGNED_BYTE);

		static Pointer fromFile(
			const char* path,
			unsigned int slot,

			StbiFormat readFormat = StbiFormat::RGBA,

			GLenum givenDataFormat = GL_RGBA,
			GLenum internalFormat = GL_RGBA,

			GLenum minScaleFilter = GL_LINEAR,
			GLenum maxScaleFilter = GL_LINEAR,

			GLenum horizontalWrappingMode = GL_CLAMP_TO_BORDER,
			GLenum verticalWrappingMode = GL_CLAMP_TO_BORDER,

			GLenum internalDataType = GL_UNSIGNED_BYTE);

		~Texture2D();

		GLuint getId() const;
		int getWidth() const;
		int getHeight() const;

		void setTextureSlot(unsigned int slot) const;
	};

}

#endif