/*
 * GLParticleSystem.cpp
 *
 *  Created on: Apr 7, 2014
 *      Author: jusabiaga
 */

// Local includes
#include "GLParticleSystem.hpp"		// GLParticleSystem
#include "GLSLProgram.hpp"			// GLSLProgram

namespace JU
{

GLParticleSystem::GLParticleSystem() : max_particles_(0)
{
    vao_handle_  = 0;
    vbo_handles_ = 0;
}



GLParticleSystem::~GLParticleSystem()
{
    // Delete the buffers
    gl::DeleteBuffers(2, vbo_handles_);
    // Delete the vertex array
    gl::DeleteVertexArrays(1, &vao_handle_);
    // Release the handles
    delete [] vbo_handles_;
}



/**
* @brief Create Vertex Buffer Object
*
* @detail If the data is not yet in a VBO, create and update the handle to it
*
* @return Successful?
*
* \todo Avoid duplicity of data by not duplicating vertices
* \todo Warning, this assumes each face is a triangle
*/
bool GLParticleSystem::init(JU::uint32 num_particles)
{
    max_particles_ = num_particles;

    positions_.resize(max_particles_, glm::vec3(0.0f));
    colors_.resize(max_particles_, glm::vec4(0.0f));

    return initVBOs();
}



/**
* @brief Create Vertex Buffer Object
*
* @detail If the data is not yet in a VBO, create and update the handle to it
*
* @return Successful?
*
* \todo Avoid duplicity of data by not duplicating vertices
* \todo Warning, this assumes each face is a triangle
*/
bool GLParticleSystem::initVBOs(void)
{
    // PARTICLES: VAO and BFO
    // ----------------------
    // VAO
    gl::GenVertexArrays(1, &vao_handle_);
    gl::BindVertexArray(vao_handle_);

    // VBO
    vbo_handles_ = new GLuint[2];
    gl::GenBuffers(2, vbo_handles_);

    // Position VBO
    gl::BindBuffer(gl::ARRAY_BUFFER, vbo_handles_[0]);

    gl::BufferData(gl::ARRAY_BUFFER,
                 max_particles_ * sizeof(positions_[0]),
                 &positions_[0],
                 gl::DYNAMIC_DRAW);

    gl::VertexAttribPointer(0,
                          POSITION_VECTOR_SIZE,
                          gl::FLOAT,
                          gl::FALSE_,
                          0,
                          (GLubyte *)NULL);

    gl::EnableVertexAttribArray(0);   // Vertex positions

    // Color VBO
    gl::BindBuffer(gl::ARRAY_BUFFER, vbo_handles_[1]);

    gl::BufferData(gl::ARRAY_BUFFER,
                 max_particles_ * sizeof(colors_[0]),
                 &colors_[0],
                 gl::DYNAMIC_DRAW);

    gl::VertexAttribPointer(1,
                          COLOR_VECTOR_SIZE,
                          gl::FLOAT,
                          gl::FALSE_,
                          0,
                          (GLubyte *)NULL);

    gl::EnableVertexAttribArray(1);   // Vertex colors

    return true;
}



void GLParticleSystem::setParticleData(const std::vector<glm::vec3>& positions, const std::vector<glm::vec4>& colors)
{
	if (positions.size() != colors.size())
	{
		printf("Position and color vectors differ in size (%li vs %li)\n", positions.size(), colors.size());
		exit(0);
	}

	set_positions(positions);
	set_colors(colors);
}



void GLParticleSystem::set_positions(const std::vector<glm::vec3>& positions)
{
	if (positions_.size() > max_particles_)
	{
		printf("Number of positions of particles (%li) larger than max (%i)\n", positions.size(), max_particles_);
		exit(0);
	}

	positions_ = positions;
}



void GLParticleSystem::set_colors(const std::vector<glm::vec4>& colors)
{
	if (colors_.size() > max_particles_)
	{
		printf("Number of colors of particles (%li) larger than max (%i)\n", colors.size(), max_particles_);
		exit(0);
	}

	colors_ = colors;
}



/**
* @brief    Draw using OpenGL API
*
* @detail   It needs to:
*           + Activate the GLMeshInstance Shader Program
*           + Set the Uniform variables
*           + Deactivate the Shader Program
*
* @param model      Model matrix
* @param view       View matrix
* @param projection Projection matrix
*/
void GLParticleSystem::draw(const GLSLProgram &program, const glm::mat4 & model, const glm::mat4 &view, const glm::mat4 &projection) const
{
    // View * Model
    glm::mat4 mv = view * model;
    // Compute MVP matrix_transform
    glm::mat4 MVP (projection * view * model);

    // LOAD UNIFORMS
    program.setUniform("Model", model);
    program.setUniform("ModelViewMatrix", mv);
    program.setUniform("NormalMatrix", glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])));
    program.setUniform("MVP", projection * mv);

    // Position VBO
    gl::BindBuffer(gl::ARRAY_BUFFER, vbo_handles_[0]);
    gl::BufferSubData(gl::ARRAY_BUFFER,
    					0,
    					positions_.size() * sizeof(positions_[0]),
                 	 	&positions_[0]);

    // Color VBO
    gl::BindBuffer(gl::ARRAY_BUFFER, vbo_handles_[1]);
    gl::BufferSubData(gl::ARRAY_BUFFER,
    					0,
    					colors_.size() * sizeof(colors_[0]),
                 	 	&colors_[0]);

    gl::BindVertexArray(vao_handle_);
    gl::DrawArrays(gl::POINTS, 0, positions_.size());
}

} // namespace JU
