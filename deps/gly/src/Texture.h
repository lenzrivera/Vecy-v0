#ifndef GLY_TEXTURE_INCLUDED
#define GLY_TEXTURE_INCLUDED

#include "GL/glew.h"

namespace gly {
	
	/**
	 * @brief Pretty much just a barebones smart pointer wrapper thing for an
	 * OpenGL texture.
	 */
	class Texture
	{
	private:
		GLuint m_id;

	public:
		Texture();
		~Texture();

		GLuint id() const;

		void generate();
	};

}

#endif