/*
 * GLMesh.cpp
 *
 *  Created on: May 7, 2013
 *      Author: jusabiaga
 */

// Local includes
#include "GLMesh.hpp"
#include "Mesh2.hpp"        // Mesh2
#include "GLSLProgram.hpp"  // static constants for attribute locations
// Global includes
#include <iostream>         // std::cout, std::endl


namespace JU
{

/**
* @brief Non-Default Constructor
*
* @param mesh Mesh2 object containing the data for this object
*/
GLMesh::GLMesh() : is_initialized_(false), vao_handle_(0), vbo_handles_(nullptr), num_buffers_(0), num_triangles_(0)
{
}


/**
* @brief Destructor
*/
GLMesh::~GLMesh()
{
    release();
}


/**
* @brief Release GPU buffers
*/
void GLMesh::release()
{
    // Delete the buffers
    gl::DeleteBuffers(num_buffers_, vbo_handles_);
    // Delete the vertex array
    gl::DeleteVertexArrays(1, &vao_handle_);
    // Release the handles
    delete [] vbo_handles_;

    num_buffers_ = num_triangles_ = 0;
    is_initialized_ = false;
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
bool GLMesh::init(const Mesh2& mesh)
{
    if (is_initialized_)
        release();

    return initVBOs(mesh);
}


/**
* @brief Create Vertmesh.getTriangleIndices()ex Buffer Object
*
* @detail If the data is not yet in a VBO, create and update the handle to it
*
* @param name Id of the Mesh2
* @param positions Vector with all vertex positions
* @param normals Vector with all vertex normals
* @param colors Vector with all vertex colors
* @param tex_coords Vector with all vertex colors
* @param faces Vector with all info about the faces of the Mesh2

* @return Successful?
*
* \todo Avoid duplicity of data by not duplicating vertices
* \todo Warning, this assumes each face is a triangle
*/
bool GLMesh::initVBOs(const Mesh2& mesh)
{
    const std::string& name                       = mesh.getName();
    const VectorPositions&       vPositions       = mesh.getPositions();
    const VectorNormals&         vNormals         = mesh.getNormals();
    const VectorTangents&        vTangents        = mesh.getTangents();
    const VectorTexCoords&       vTexCoords       = mesh.getTexCoords();
    const VectorVertexIndices&   vVertexIndices   = mesh.getVertexIndices();
    const VectorTriangleIndices& vTriangleIndices = mesh.getTriangleIndices();

	// Attribute data sizes
	const JU::uint8 POSITION_VECTOR_SIZE = 3;
	const JU::uint8 NORMAL_VECTOR_SIZE 	 = 3;
	const JU::uint8 TEX_VECTOR_SIZE      = 2;
	const JU::uint8 TANGENT_VECTOR_SIZE  = 4;

	// Compute number of VBOs needed
	num_buffers_ = 0;

    if (vPositions.size())
        num_buffers_++;
    else
    {
        std::printf("Mesh %s has no positions\n", name.c_str());
    }
    if (vTriangleIndices.size())
        num_buffers_++;
    else
    {
        std::printf("Mesh %s has no indices\n", name.c_str());
    }
    if (vNormals.size())
        num_buffers_++;
    if (vTangents.size())
        num_buffers_++;
    if (vTexCoords.size())
        num_buffers_++;

    // Create and bind VAO
    gl::GenVertexArrays(1, &vao_handle_);
    gl::BindVertexArray(vao_handle_);

    // Create Buffers
    vbo_handles_ = new GLuint[num_buffers_];
    gl::GenBuffers(num_buffers_, vbo_handles_);

    // The size of the VBOs must be equal to the number of unique vertices
    JU::uint32 num_vertices = vVertexIndices.size();

    JU::uint8 vbo_index = 0;

    // VERTEX POSITIONS
    if (vPositions.size())
    {
        float *aPositions   = new float [num_vertices * POSITION_VECTOR_SIZE];

        for (JU::uint32 index = 0; index < num_vertices; ++index)
        {
            aPositions[index * POSITION_VECTOR_SIZE + 0] = vPositions[vVertexIndices[index].position_].x;
            aPositions[index * POSITION_VECTOR_SIZE + 1] = vPositions[vVertexIndices[index].position_].y;
            aPositions[index * POSITION_VECTOR_SIZE + 2] = vPositions[vVertexIndices[index].position_].z;
        }

        // Position VBO
        gl::BindBuffer(gl::ARRAY_BUFFER, vbo_handles_[vbo_index]);
        gl::BufferData(gl::ARRAY_BUFFER, num_vertices * POSITION_VECTOR_SIZE * sizeof(aPositions[0]), aPositions, gl::STATIC_DRAW);
        gl::VertexAttribPointer(GLSLProgram::POSITION_ATTRIBUTE_LOCATION, POSITION_VECTOR_SIZE, gl::FLOAT, gl::FALSE_, 0, (GLubyte *)NULL);
        gl::EnableVertexAttribArray(GLSLProgram::POSITION_ATTRIBUTE_LOCATION);   // Vertex positions

        delete [] aPositions;

        ++vbo_index;
    }

    // VERTEX NORMALS
    if (vNormals.size())
    {
        float *aNormals     = new float [num_vertices * NORMAL_VECTOR_SIZE];

        for (JU::uint32 index = 0; index < num_vertices; ++index)
        {
            aNormals[index * NORMAL_VECTOR_SIZE + 0] = vNormals[vVertexIndices[index].normal_].x;
            aNormals[index * NORMAL_VECTOR_SIZE + 1] = vNormals[vVertexIndices[index].normal_].y;
            aNormals[index * NORMAL_VECTOR_SIZE + 2] = vNormals[vVertexIndices[index].normal_].z;
        }

        // Normal VBO
        gl::BindBuffer(gl::ARRAY_BUFFER, vbo_handles_[vbo_index]);
        gl::BufferData(gl::ARRAY_BUFFER, num_vertices * NORMAL_VECTOR_SIZE * sizeof(aNormals[0]), aNormals, gl::STATIC_DRAW);
        gl::VertexAttribPointer(GLSLProgram::NORMAL_ATTRIBUTE_LOCATION, NORMAL_VECTOR_SIZE, gl::FLOAT, gl::FALSE_, 0, (GLubyte *)NULL);
        gl::EnableVertexAttribArray(GLSLProgram::NORMAL_ATTRIBUTE_LOCATION);   // Vertex normals

        delete [] aNormals;

        ++vbo_index;
    }

    // VERTEX TEXTURE COORDINATES
    if (vTexCoords.size())
    {
        float *aTexCoords   = new float [num_vertices * TEX_VECTOR_SIZE];

        for (JU::uint32 index = 0; index < num_vertices; ++index)
        {
            aTexCoords[index * TEX_VECTOR_SIZE + 0] = vTexCoords[vVertexIndices[index].tex_].s;
            aTexCoords[index * TEX_VECTOR_SIZE + 1] = vTexCoords[vVertexIndices[index].tex_].t;
        }

        // Texture Coordinates VBO
        gl::BindBuffer(gl::ARRAY_BUFFER, vbo_handles_[vbo_index]);
        gl::BufferData(gl::ARRAY_BUFFER, num_vertices * TEX_VECTOR_SIZE * sizeof(aTexCoords[0]), aTexCoords, gl::STATIC_DRAW);
        gl::VertexAttribPointer(GLSLProgram::TEXCOORD_ATTRIBUTE_LOCATION, TEX_VECTOR_SIZE, gl::FLOAT, gl::FALSE_, 0, (GLubyte *)NULL);
        gl::EnableVertexAttribArray(GLSLProgram::TEXCOORD_ATTRIBUTE_LOCATION);   // Vertex texture coordinates

        delete [] aTexCoords;

        ++vbo_index;
    }

    if (vTangents.size())
    {
        float *aTangents = new float [num_vertices * TANGENT_VECTOR_SIZE];

        for (JU::uint32 index = 0; index < num_vertices; ++index)
        {
            aTangents[index * TANGENT_VECTOR_SIZE + 0] = vTangents[index].x;
            aTangents[index * TANGENT_VECTOR_SIZE + 1] = vTangents[index].y;
            aTangents[index * TANGENT_VECTOR_SIZE + 2] = vTangents[index].z;
            aTangents[index * TANGENT_VECTOR_SIZE + 3] = vTangents[index].w;
        }

        gl::BindBuffer(gl::ARRAY_BUFFER, vbo_handles_[vbo_index]);
        gl::BufferData(gl::ARRAY_BUFFER, num_vertices * TANGENT_VECTOR_SIZE * sizeof(aTangents[0]), aTangents, gl::STATIC_DRAW);
        gl::VertexAttribPointer(GLSLProgram::TANGENT_ATTRIBUTE_LOCATION, TANGENT_VECTOR_SIZE, gl::FLOAT, gl::FALSE_, 0, (GLubyte *)NULL);
        gl::EnableVertexAttribArray(GLSLProgram::TANGENT_ATTRIBUTE_LOCATION);   // Vertex tangents

        delete [] aTangents;

        ++vbo_index;
    }

    if (vTriangleIndices.size())
    {
        num_triangles_ = vTriangleIndices.size();
        JU::uint16* aIndices = new JU::uint16[num_triangles_ * 3];

        for (JU::uint32 triangle = 0; triangle < num_triangles_; ++triangle)
        {
            aIndices[triangle * 3 + 0] = vTriangleIndices[triangle].v0_;
            aIndices[triangle * 3 + 1] = vTriangleIndices[triangle].v1_;
            aIndices[triangle * 3 + 2] = vTriangleIndices[triangle].v2_;
        }

        // Allocate and initialize VBO for vertex indices
        gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, vbo_handles_[vbo_index]);
        gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, num_triangles_ * 3 * sizeof(aIndices[0]), aIndices, gl::STATIC_DRAW);

        delete [] aIndices;
    }

    is_initialized_ = true;

    return true;
}



/**
* @brief    Draw using OpenGL API
*
* @detail   + Bind the VAO for this GLMesh.
*           + Draw.
*           + Unbind
*
* @param    model Model matrix
* @param    view View matrix
* @param    projection Projection matrix
*/
void GLMesh::draw(void) const
{
    gl::BindVertexArray(vao_handle_);
    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, vbo_handles_[num_buffers_ - 1]);
    gl::DrawElements(gl::TRIANGLES, 3 * num_triangles_, gl::UNSIGNED_SHORT, 0);
}

} // namespace JU
