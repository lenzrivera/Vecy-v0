#ifndef GLY_UNIFORM_INCLUDED
#define GLY_UNIFORM_INCLUDED

#include "GL/glew.h"
#include "glm/glm.hpp"

namespace gly {

    class Uniform
    {
    private:
        GLint m_location;

    public:
        Uniform();

        /**
         * @brief Stores the location of a uniform named `name`.
         */
        Uniform(GLuint programId, const char* name);


        /**
         * @brief Returns the location of the uniform.
         */
        GLint location() const;
        

        // Individual Value Setters //
        // ---------------------------

        /**
         * @brief Sets an integer as the value of a uniform.
         */
        void setUniform(GLint value) const;
        /**
         * @brief Sets an unisgned integer as the value of a uniform.
         */
		void setUniform(GLuint value) const;
        /**
         * @brief Sets a float as the value of a uniform.
         */
		void setUniform(GLfloat value) const;

        /**
         * @brief Sets a `vec2<int>` as the value of a uniform.
         */
		void setUniform(glm::vec<2, GLint> value) const;
        /**
         * @brief Sets a `vec3<int>` as the value of a uniform.
         */
		void setUniform(glm::vec<3, GLint> value) const;
        /**
         * @brief Sets a `vec4<int>` as the value of a uniform.
         */
		void setUniform(glm::vec<4, GLint> value) const;

        /**
         * @brief Sets a `vec2<unsigned int>` as the value of a uniform.
         */
		void setUniform(glm::vec<2, GLuint> value) const;
        /**
         * @brief Sets a `vec3<unsigned int>` as the value of a uniform.
         */
		void setUniform(glm::vec<3, GLuint> value) const;
        /**
         * @brief Sets a `vec4<unsigned int>` as the value of a uniform.
         */
		void setUniform(glm::vec<4, GLuint> value) const;

        /**
         * @brief Sets a `vec2<float>` as the value of a uniform.
         */
		void setUniform(glm::vec<2, GLfloat> value) const;
        /**
         * @brief Sets a `vec3<float>` as the value of a uniform.
         */
		void setUniform(glm::vec<3, GLfloat> value) const;
        /**
         * @brief Sets a `vec4<float>` as the value of a uniform.
         */
		void setUniform(glm::vec<4, GLfloat> value) const;

        /**
         * @brief Sets a `mat2<float>` as the value of a uniform.
         */
		void setUniform(glm::mat<2, 2, GLfloat> value) const;
        /**
         * @brief Sets a `mat3<float>` as the value of a uniform.
         */
		void setUniform(glm::mat<3, 3, GLfloat> value) const;
        /**
         * @brief Sets a `mat4<float>` as the value of a uniform.
         */
		void setUniform(glm::mat<4, 4, GLfloat> value) const;


        // Array Value Setters //
        // ---------------------
    
        /**
         * @brief Sets an array of integers as the value of a uniform.
         */
		void setUniform(GLint* value, GLsizei count) const;
        /**
         * @brief Sets an array of unsigned integers as the value of a uniform.
         */
		void setUniform(GLuint* value, GLsizei count) const;
        /**
         * @brief Sets an array of floats as the value of a uniform.
         */
		void setUniform(GLfloat* value, GLsizei count) const;
    };

}

#endif