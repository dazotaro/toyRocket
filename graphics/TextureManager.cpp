/*
 * TextureManager.cpp
 *
 *  Created on: Jul 24, 2013
 *      Author: jusabiaga
 */

// Local includes
#include "TextureManager.hpp"       // Class declaration
#include "GLSLProgram.hpp"          // GLSLProgram
#include "ImageHelper.hpp"			// imageInvertVertically
// Global includes
#include <SOIL/SOIL.h>                   // SOIL_load_image
#include <iostream>                 // cout, endl

namespace JU
{

// STATIC MMEMBER VARIABLES
// ------------------------
std::map<std::string, GLuint> TextureManager::texture_map_;  //!< Handle to the texture
int TextureManager::num_tex_bound_ = 0;



// STATIC MEMBER FUNCTIONS
// -----------------------

bool TextureManager::loadTexture(const std::string &texture_name, const std::string &filename)
{
    // If the texture is not yet in memory
    if (texture_map_.find(texture_name) == texture_map_.end())
    {
        GLuint tex_2d;
        gl::GenTextures(1, &tex_2d);
        texture_map_[texture_name] = tex_2d;
    }


    int width, height, channels;
    unsigned char *image = SOIL_load_image(filename.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

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
			std::printf("Loading \"%s\": number or channels %i not supported\n", filename.c_str(), channels);
			exit(0);
    }

    // Flip the image vertically
    JU::imageInvertVertically(width, height, channels, image);

    gl::BindTexture(gl::TEXTURE_2D, texture_map_[texture_name]);
    gl::TexImage2D(gl::TEXTURE_2D, 0, mode, width, height, 0, mode, gl::UNSIGNED_BYTE, image);


    GLfloat filtering_mode = gl::LINEAR_MIPMAP_LINEAR;
    gl::GenerateMipmap(gl::TEXTURE_2D);


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


bool TextureManager::registerTexture(const std::string &texture_name, JU::uint32 tex_id)
{
    // If the texture is not yet in memory
    if (texture_map_.find(texture_name) == texture_map_.end())
    {
        texture_map_[texture_name] = tex_id;
    }

    return true;
}

void TextureManager::bindTexture(const std::string &texture_name)
{
    gl::BindTexture(gl::TEXTURE_2D, texture_map_[texture_name]);
}


void TextureManager::bindTexture(const GLSLProgram &program, const std::string &texture_name, const std::string &uniform_name)
{
    bindTexture(program, texture_map_[texture_name], uniform_name);
}



void TextureManager::bindTexture(const GLSLProgram &program, JU::uint32 tex_id, const std::string &uniform_name)
{
    gl::ActiveTexture(gl::TEXTURE0 + num_tex_bound_);
    gl::BindTexture(gl::TEXTURE_2D, tex_id);

    program.setUniform(uniform_name.c_str(), num_tex_bound_);

    num_tex_bound_++;
}



void TextureManager::unbindAllTextures()
{
    num_tex_bound_ = 0;
}



void TextureManager::deleteTexture(const std::string& texture_name)
{
    TextureMapIterator iter = texture_map_.find(texture_name);

    if (iter != texture_map_.end())
        gl::DeleteTextures(1, &iter->second);
}



void TextureManager::deleteAllTextures()
{
    TextureMapIterator iter = texture_map_.begin();
    for(; iter != texture_map_.end(); ++iter)
    {
    	gl::DeleteTextures(1, &iter->second);
    }
}

} // namespace JU
