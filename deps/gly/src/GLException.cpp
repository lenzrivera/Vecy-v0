#include "GLException.h"

using namespace gly;

GLException::GLException(const std::string& msg) noexcept
	: message(msg) // Use its copy constructor.
{
}

const char* GLException::what() const noexcept
{
	return message.c_str();
}