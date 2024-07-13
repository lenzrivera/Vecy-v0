#ifndef GLY_IMAGE_INCLUDED
#define GLY_IMAGE_INCLUDED

namespace gly {

    /**
     * @brief Super-duper pedentically speaking, this should implement the rule
     * of five, but...
     */
    class Image
    {
    private:
        unsigned char* m_data;
        int m_width, m_height;

    public:
        /**
         * @brief Formats provided by stb_image.
         */
        enum class Format : int
        {
            STBI_default = 0,

            STBI_grey = 1,
            STBI_grey_alpha = 2,
            STBI_rgb = 3,
            STBI_rgb_alpha = 4
        };

    public:
        Image() = delete;
        ~Image();

        /**
         * @brief Loads in an image of a particular format from a given path.
         */
        Image(Format format, const char* path, bool flip = false);


        /**
         * @brief Returns the pointer to the image data.
         */
        unsigned char* data() const;

        /**
         * @brief Returns the image height.
         */
        int height() const;

        /**
         * @brief Returns the image width.
         */
        int width() const;
    };

}

#endif