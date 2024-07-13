#ifndef GLY_GLEXCEPTION_INCLUDED
#define GLY_GLEXCEPTION_INCLUDED

#include <stdexcept>
#include <string>

namespace gly {

	class GLException : public std::exception
	{
	private:
		const std::string message;

	public:
		explicit GLException(const std::string& msg) noexcept;
		const char* what() const noexcept;
	};

}

#endif