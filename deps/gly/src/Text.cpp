#include "Text.h"

#include <iostream>

#include "GLException.h"

using namespace gly;

FontFace::FontFace(
	const FT_Library& ftLib,
	const char* fontPath,
	unsigned int pixelWidth,
	unsigned int pixelHeight
)
	: textureMap()
{
	FT_Face fontFace;

	// Returns non-zero number on failure.
	if (FT_New_Face(ftLib, fontPath, 0, &fontFace))
	{
		std::string errMsg = "Font '";
		errMsg += fontPath;
		errMsg += "' failed to load.";

		throw GLException(errMsg);
	}

	FT_Set_Pixel_Sizes(fontFace, pixelWidth, pixelHeight);

	// OpenGL expects each "pixel" in a texture to take up 4 bytes of space, but
	// since only 1 byte is needed (and is also stored by FreeType) to store a 
	// font glyph, OpenGL must be indicated otherwise.
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Explicitly work on texture slot 0 to avoid interfering with other textures
	// in other texture slots in case another texture slot is currently active.
	glActiveTexture(GL_TEXTURE0);

	// Cache the first 128 ASCII character glyphs of the font face.
	for (unsigned char c = 0; c < 128; c++)
	{
		// Returns non-zero number on failure.
		if (FT_Load_Char(fontFace, c, FT_LOAD_RENDER))
		{
			std::string errMsg = "Character '";
			errMsg += c;
			errMsg += "' from font '";
			errMsg += fontPath;
			errMsg += "' failed to load.";

			throw GLException(errMsg);
		}

		GLuint charTexId;
		glGenTextures(1, &charTexId);
		glBindTexture(GL_TEXTURE_2D, charTexId);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			fontFace->glyph->bitmap.width,
			fontFace->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			fontFace->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		CharData characterInfo = {
			charTexId,
			glm::ivec2(fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows),
			glm::ivec2(fontFace->glyph->bitmap_left, fontFace->glyph->bitmap_top),
			fontFace->glyph->advance.x
		};
		textureMap.insert({ c, characterInfo });
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	FT_Done_Face(fontFace);
}

FontFace::~FontFace()
{
	for (const auto& it : textureMap)
		glDeleteTextures(1, &(it.second.textureId));
}

const CharData FontFace::getCharData(unsigned char c)
{
	return textureMap[c];
}


Text::Text() : 
	ftLibrary(nullptr), 
	textVao(0), 
	textVbo(0), 
	textShaders(), 
	u_projection(), 
	u_textColor()
{
	// Initialize FreeType.
	// Returns nonzero number on failure.
	if (FT_Init_FreeType(&ftLibrary))
		throw GLException("FreeType failed to initialize.");

	// Initialize Text VAO.
	glGenVertexArrays(1, &textVao);
	glBindVertexArray(textVao);
	
	// Initialize Text VBO.
	glGenBuffers(1, &textVbo);
	glBindBuffer(GL_ARRAY_BUFFER, textVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 6, nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (const void*)0);
	glEnableVertexAttribArray(0);

	// Initialize shaders.
	textShaders.attachSourceString(GL_VERTEX_SHADER,
		"#version 450 core\n"
		""
		"// As per the LearnOpenGL website, store position and texCoords"
		"// in one vertex attribute.\n"
		"in layout(location = 0) vec4 a_posAndTex;\n"
		"out vec2 v_texCoords;\n"
		""
		"uniform mat4 u_projection;\n"
		""
		"void main()\n"
		"{\n"
		"	gl_Position = u_projection * vec4(a_posAndTex.xy, 0.0, 1.0);\n"
		"	v_texCoords = a_posAndTex.zw;\n"
		"}"
	);

	textShaders.attachSourceString(GL_FRAGMENT_SHADER,
		"#version 450 core\n"
		""
		"in vec2 v_texCoords;\n"
		"out vec4 o_color;\n"
		""
		"uniform sampler2D u_textTexture;\n"
		"uniform vec4 u_textColor;\n"
		""
		"void main()\n"
		"{\n"
		"	o_color = u_textColor *"
		"		vec4(1.0, 1.0, 1.0, texture(u_textTexture, v_texCoords).r);\n"
		"}"
	);

	textShaders.link();
	u_projection = textShaders.getUniform("u_projection");
	u_textColor = textShaders.getUniform("u_textColor");
	u_textTexture = textShaders.getUniform("u_textTexture");

	// Unbind VAO and VBO to reduce potential conflict. Note that the shader 
	// program was never used, so there is no need to unbind.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Text::~Text()
{
	FT_Done_FreeType(ftLibrary);
	glDeleteVertexArrays(1, &textVao);
	glDeleteBuffers(1, &textVbo);
}

const FontFace Text::loadFont(
	const char* path, unsigned int pxWidth, unsigned int pxHeight) const
{
	return FontFace(ftLibrary, path, pxWidth, pxHeight);
};

void Text::render(
	std::string text,
	FontFace& face,
	float scale,
	const glm::vec4& color,
	const glm::vec2& position,
	const glm::mat4& projection) const
{
	glBindVertexArray(textVao);
	glBindBuffer(GL_ARRAY_BUFFER, textVbo);

	// Explicitly work on texture slot 0 to avoid interfering with other textures
	// in other texture slots in case another texture slot is currently active.
	glActiveTexture(GL_TEXTURE0);

	textShaders.use();
	u_projection.setUniform(projection);
	u_textColor.setUniform(color);
	u_textTexture.setUniform(0);

	float maxY = (float) face.getCharData('H').bearing.y;
	float xOffset = 0.0f;
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		const CharData charData = face.getCharData(*c);
	
		float xPos = position.x + xOffset + charData.bearing.x * scale;
		float yPos = position.y - (maxY - charData.bearing.y) * scale;
	
		float width = charData.size.x * scale;
		float height = charData.size.y * scale;
		
		// Texcoords are reversed.
		float vertices[6][4] = {
			{ xPos,         yPos,            0.0f, 0.0f },
			{ xPos,         yPos - height,   0.0f, 1.0f },
			{ xPos + width, yPos,            1.0f, 0.0f },

			{ xPos + width, yPos,            1.0f, 0.0f },
			{ xPos,         yPos - height,   0.0f, 1.0f },
			{ xPos + width, yPos - height,   1.0f, 1.0f }
		};
	
		glBindTexture(GL_TEXTURE_2D, charData.textureId);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	
		// x >> 6 = 2 ** 6; check LearnOpenGL for more info.
		xOffset += (charData.advance >> 6) * scale;
	}
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}