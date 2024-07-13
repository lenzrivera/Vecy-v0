#ifndef GLY_TEXT_INCLUDED
#define GLY_TEXT_INCLUDED

#include <unordered_map>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "ft2build.h"
#include FT_FREETYPE_H

#include "Shader.h"
#include "ShaderProgram.h"

namespace gly {

	/**
	 * @brief Contains the relevant data of a character based on a loaded font
	 * file.
	 */
	struct CharData
	{
		GLuint textureId;
		glm::ivec2 size;
		glm::ivec2 bearing;
		FT_Pos advance;
	};

	/**
	 * @brief Represents a loaded font file. Note that only the first 128 ASCII
	 * characters of a font are loaded.
	 */
	class FontFace
	{
	private:
		std::unordered_map<unsigned char, CharData> textureMap;

	public:
		FontFace();

		FontFace(
			const FT_Library& ftLib,
			const char* fontPath,
			unsigned int pixelWidth,
			unsigned int pixelHeight);

		~FontFace();

		/**
		 * @brief Returns the character data of a given character based on the
		 * loaded font.
		 */
		const CharData getCharData(unsigned char c);
	};

	/**
	 * @brief Loads in all the necessary components to render text onto an OpenGL
	 * viewport.
	 * 
	 * TAKE NOTE: When in use, texture slot 0 is reserved for font glyph texture
	 * operations; be very careful!.
	 * 
	 * TAKE NOTE 2: Don't forget to turn on blending and set the blend mode; that
	 * is needed for text rendering but isn't handled by this class!
	 */
	class Text
	{
	private:
		FT_Library ftLibrary;
		
		GLuint textVao, textVbo;
		ShaderProgram textShaders;
		Uniform u_projection, u_textColor, u_textTexture;

	public:
		Text();
		~Text();

		/**
		 * @brief Loads a font face from a given path.
		 *
		 * TAKE NOTE: This method sets the active texture slot to slot 0 to avoid
		 * interfering with other textures loaded in other texture slots.
		 */
		const FontFace loadFont(
			const char* path, 
			unsigned int pxWidth, 
			unsigned int pxHeight) const;

		/**
		 * @brief Renders a string of text on an OpenGL viewport based on given
		 * parameters.
		 * 
		 * TAKE NOTE: This method binds its own VAO, VBO, shader program, and
		 * textures (at slot 0; this is also set), and then unbinds them once
		 * text is rendered.
		 */
		void render(
			std::string text,
			FontFace& face,
			float scale,
			const glm::vec4& color,
			const glm::vec2& position,
			const glm::mat4& projection) const;
	};

}

#endif