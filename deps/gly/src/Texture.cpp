#include "Texture.h"

using namespace gly;

Texture::Texture()
	: m_id(0)
{
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}


GLuint Texture::id() const
{
	return m_id;
}

void Texture::generate()
{
	glGenTextures(1, &m_id);
}