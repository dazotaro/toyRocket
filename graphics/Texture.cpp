/*
 * Texture.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: jusabiaga
 */

// Local includes
#include "Texture.hpp"

// Global includes
#include <SOIL.h>                   // SOIL_load_image
#include "ImageHelper.hpp"       	// imageInvertVertically
#include <cstdio>                   // std::printf

namespace JU
{

Texture::~Texture()
{
    // TODO Auto-generated destructor stub
}



bool Texture::init(const char* name, const char* filename)
{
    name_ = name;
    filename_ = filename;

    return load();
}


bool Texture::load()
{
    gl::GenTextures(1, &handle_);


    int width, height, channels;
    unsigned char *image = SOIL_load_image(filename_.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

    GLuint mode;

    switch (channels)
    {
        case 3:
            mode = gl::RGB;
            break;

        case 4:
            mode = gl::RGBA;
            break;

        default:
            std::printf("Loading \"%s\": number or channels %i not supported\n", filename_.c_str(), channels);
            exit(0);
    }

    // Flip the image vertically
    JU::imageInvertVertically(width, height, channels, image);

    gl::BindTexture(gl::TEXTURE_2D, handle_);
    gl::TexImage2D(gl::TEXTURE_2D, 0, mode, width, height, 0, mode, gl::UNSIGNED_BYTE, image);

    GLfloat filtering_mode = gl::NEAREST;


    //GLfloat filtering_mode = gl::LINEAR_MIPMAP_LINEAR;
    //glGenerateMipmap(gl::TEXTURE_2D);


    gl::TexParameterf(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, filtering_mode);
    gl::TexParameterf(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, filtering_mode);

    /*
    float color[] = { 1.0f, 0.0f, 1.0f, 1.0f };
    gl::TexParameterfv(gl::TEXTURE_2D, gl::TEXTURE_BORDER_COLOR, color);

    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::REPEAT);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::REPEAT);
    */

    SOIL_free_image_data(image);

    return true;
}



JU::uint32 Texture::getHandle() const
{
    return handle_;
}

} // namespace JU
