#include "Image.h"

#include <string>
#include <type_traits>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "GLException.h"

using namespace gly;

Image::Image(Format format, const char* path, bool flip)
    : m_data(nullptr), m_width(0), m_height(0)
{
	stbi_set_flip_vertically_on_load(flip);
	m_data = stbi_load(path, &m_width, &m_height, nullptr, 
        static_cast<std::underlying_type<Image::Format>::type>(format));

	if (m_data == nullptr)
	{
		std::string msg = "Unable to open file in \"";
		msg.append(path);
		msg.append("\".");

		throw GLException(msg);
	}
}

Image::~Image()
{
    stbi_image_free(m_data);
}


unsigned char* Image::data() const
{
    return m_data;
}

int Image::height() const
{
    return m_height;
}

int Image::width() const
{
    return m_width;
}