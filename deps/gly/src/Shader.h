#ifndef GLY_SHADER_INCLUDED
#define GLY_SHADER_INCLUDED

#include "GL/glew.h"

namespace gly {

    class Shader
    {
    private:
        GLuint m_id;

    public:
        Shader() = delete;
        ~Shader();

        /**
         * @brief Creates a shader object of type `type`.
         */
        Shader(GLenum type);


        /**
         * @brief Returns the id of the shader object.
         */
        GLuint id() const;


        /**
         * @brief Compiles a shader from a file path.
         */
        void loadFile(const char* path) const;

        /**
         * @brief Compiles a shader from a string representing its source code.
         */
        void loadSourceString(const char* source) const;
    };

}

#endif