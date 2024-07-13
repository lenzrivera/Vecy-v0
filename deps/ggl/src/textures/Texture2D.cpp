#include "Texture2D.h"

#include <cassert>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace ggl;

Texture2D::Texture2D(
	const void* data,
	int width,
	int height,
	unsigned int slot,

	GLenum givenDataFormat,
	GLenum internalFormat,

	GLenum minScaleFilter,
	GLenum maxScaleFilter,

	GLenum horizontalWrappingMode,
	GLenum verticalWrappingMode,

	GLenum internalDataType
)
	: id(0), width(width), height(height)
{
	assert(slot < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);

	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minScaleFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxScaleFilter);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, horizontalWrappingMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, verticalWrappingMode);
		
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		internalFormat,
		width,
		height,
		0,
		givenDataFormat,
		internalDataType,
		data);
}

Texture2D::Pointer Texture2D::fromData(
	const void* data,
	int width,
	int height,
	unsigned int slot,

	GLenum givenDataFormat,
	GLenum internalFormat,

	GLenum minScaleFilter,
	GLenum maxScaleFilter,

	GLenum horizontalWrappingMode,
	GLenum verticalWrappingMode,

	GLenum internalDataType)
{
	 Texture2D* t = new Texture2D(
		data, 
		width, 
		height, 
		slot,
		
		givenDataFormat, 
		internalFormat, 
		
		minScaleFilter, 
		maxScaleFilter, 
		
		horizontalWrappingMode,
		verticalWrappingMode, 

		internalDataType);

	 return Texture2D::Pointer(t);
}

Texture2D::Pointer Texture2D::fromFile(
	const char* path,
	unsigned int slot,

	StbiFormat readFormat,

	GLenum givenDataFormat,
	GLenum internalFormat,

	GLenum minScaleFilter,
	GLenum maxScaleFilter,

	GLenum horizontalWrappingMode,
	GLenum verticalWrappingMode,

	GLenum internalDataType)
{
	int width, height, bitDepth;
	stbi_uc* imgData = stbi_load(
		path, &width, &height, &bitDepth, static_cast<int>(readFormat));

	// Unable to open file at given path.
	assert(imgData != nullptr);

	Texture2D::Pointer texture = fromData(
		imgData,
		width,
		height,
		slot,

		givenDataFormat,
		internalFormat,

		minScaleFilter,
		maxScaleFilter,

		horizontalWrappingMode,
		verticalWrappingMode,

		internalDataType);

	stbi_image_free(imgData);
	return texture;
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &id);
}


GLuint Texture2D::getId() const
{
	return id;
}

int Texture2D::getWidth() const
{
	return width;
}

int Texture2D::getHeight() const
{
	return height;
}


void Texture2D::setTextureSlot(unsigned int slot) const
{
	assert(slot < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);

	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}