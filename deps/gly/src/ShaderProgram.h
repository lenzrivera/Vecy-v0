#ifndef GLY_SHADERPROGRAM_INCLUDED
#define GLY_SHADERPROGRAM_INCLUDED

#include "GL/glew.h"

#include "Shader.h"
#include "Uniform.h"

namespace gly {

    class ShaderProgram
    {
    private:
        GLuint m_id;

    public:
        ShaderProgram();
        ~ShaderProgram();


        /**
         * @brief Returns the id of the shader program.
         */
        GLuint id() const;


        /**
         * @brief Attaches a `gly::Shader` object to a shader program.
         */
        void attach(const Shader& shader) const;

        /**
         * @brief Attaches a shader from a given file path.
         */
        void attachFile(GLenum type, const char* path) const;

        /**
         * @brief Attaches a shader from a given string acting as its source
         * code.
         */
        void attachSourceString(GLenum type, const char* sourceString) const;

        /**
         * @brief Links the attached shader objects to a shader program.
         */
        void link() const;


        /**
         * @brief Returns an object representing a shader uniform whose value
         * can be set.
         */
        Uniform getUniform(const char* name) const;


        /**
         * @brief Lets subsequent render calls use a shader.
         */
        void use() const;
    };

}

#endif