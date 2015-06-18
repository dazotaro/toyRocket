/*
 * GLMesh.cpp
 *
 *  Created on: May 7, 2013
 *      Author: jusabiaga
 */

#include "GLMesh.hpp"
#include <iostream>     // std::cout, std::endl
#include "DebugGlm.hpp" // overloaded 'operator<<' for GLM classes

namespace JU
{

/**
* @brief Non-Default Constructor
*
* @param mesh Mesh2 object containing the data for this object
*/
GLMesh::GLMesh(const Mesh2 &mesh) : Mesh2(mesh), vao_handle_(0), vbo_handles_(nullptr), num_buffers_(0)
{
}

/**
* @brief Non-Default Constructor
*
* @param name Id of the Mesh2
* @param positions Vector with all vertex positions
* @param normals Vector with all vertex normals
* @param colors Vector with all vertex colors
* @param tex_coords Vector with all vertex colors
* @param faces Vector with all info about the faces of the Mesh2
*/
GLMesh::GLMesh(const std::string&				name,
				 const VectorPositions&			vPositions,
				 const VectorNormals&			vNormals,
				 const VectorTexCoords&			vTexCoords,
				 const VectorVertexIndices&		vVertexIndices,
				 const VectorTriangleIndices& 	vTriangleIndices)
		: Mesh2(name, vPositions, vNormals, vTexCoords, vVertexIndices, vTriangleIndices),
		  vao_handle_(0), vbo_handles_(0), num_buffers_(4)
{
    vao_handle_ = 0;
}

/**
* @brief Destructor
*/
GLMesh::~GLMesh()
{
	// Delete the buffers
    gl::DeleteBuffers(num_buffers_, vbo_handles_);
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
bool GLMesh::init(void)
{
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
bool GLMesh::initVBOs(void)
{
	// Attribute data sizes
	const JU::uint8 POSITION_VECTOR_SIZE = 3;
	const JU::uint8 NORMAL_VECTOR_SIZE 	 = 3;
	const JU::uint8 TEX_VECTOR_SIZE      = 2;
	const JU::uint8 TANGENT_VECTOR_SIZE  = 4;

    // Retrieve the data from the Mesh2 object
	//const std::string& 			 name			  = getName();
	const VectorPositions& 		 vPositions		  = getPositions();
	const VectorNormals& 		 vNormals		  = getNormals();
	const VectorTexCoords& 		 vTexCoords		  = getTexCoords();
	const VectorTangents&		 vTangents		  = getTangents();
	const VectorVertexIndices&   vVertexIndices   = getVertexIndices();
	const VectorTriangleIndices& vTriangleIndices = getTriangleIndices();

	// Local variables
	bool load_tangents = false;
	JU::uint8 vbo_index = 0;

	if (vTangents.size() > 0)
	{
		num_buffers_ = 5;	// positions, texture_coordinates, normals, tangents and indices
		load_tangents = true;
	}
	else
		num_buffers_ = 4;

    // The size of the VBOs must be equal to the number of unique vertices
	JU::uint32 num_vertices = vVertexIndices.size();

    float *aPositions	= new float [num_vertices * POSITION_VECTOR_SIZE];
    float *aNormals     = new float [num_vertices * NORMAL_VECTOR_SIZE];
    float *aTexCoords   = new float [num_vertices * TEX_VECTOR_SIZE];

    //
    for (JU::uint32 index = 0; index < num_vertices; ++index)
    {
		aPositions[index * POSITION_VECTOR_SIZE + 0] = vPositions[vVertexIndices[index].position_].x;
		aPositions[index * POSITION_VECTOR_SIZE + 1] = vPositions[vVertexIndices[index].position_].y;
		aPositions[index * POSITION_VECTOR_SIZE + 2] = vPositions[vVertexIndices[index].position_].z;

		aNormals[index * NORMAL_VECTOR_SIZE + 0] = vNormals[vVertexIndices[index].normal_].x;
		aNormals[index * NORMAL_VECTOR_SIZE + 1] = vNormals[vVertexIndices[index].normal_].y;
		aNormals[index * NORMAL_VECTOR_SIZE + 2] = vNormals[vVertexIndices[index].normal_].z;

		aTexCoords[index * TEX_VECTOR_SIZE + 0] = vTexCoords[vVertexIndices[index].tex_].s;
		aTexCoords[index * TEX_VECTOR_SIZE + 1] = vTexCoords[vVertexIndices[index].tex_].t;
    }

    // Create and bind VAO
    gl::GenVertexArrays(1, &vao_handle_);
    gl::BindVertexArray(vao_handle_);

    // Create Buffers
    vbo_handles_ = new GLuint[num_buffers_];
    gl::GenBuffers(num_buffers_, vbo_handles_);

    // Position VBO
    gl::BindBuffer(gl::ARRAY_BUFFER, vbo_handles_[vbo_index]);
    gl::BufferData(gl::ARRAY_BUFFER, num_vertices * POSITION_VECTOR_SIZE * sizeof(aPositions[0]), aPositions, gl::STATIC_DRAW);
    gl::VertexAttribPointer(vbo_index, POSITION_VECTOR_SIZE, gl::FLOAT, gl::FALSE_, 0, (GLubyte *)NULL);
    gl::EnableVertexAttribArray(vbo_index);   // Vertex positions

    ++vbo_index;

    // Texture Coordinates VBO
    gl::BindBuffer(gl::ARRAY_BUFFER, vbo_handles_[vbo_index]);
    gl::BufferData(gl::ARRAY_BUFFER, num_vertices * TEX_VECTOR_SIZE * sizeof(aTexCoords[0]), aTexCoords, gl::STATIC_DRAW);
    gl::VertexAttribPointer(vbo_index, TEX_VECTOR_SIZE, gl::FLOAT, gl::FALSE_, 0, (GLubyte *)NULL);
    gl::EnableVertexAttribArray(vbo_index);   // Vertex texture coordinates

    ++vbo_index;

    // Normal VBO
    gl::BindBuffer(gl::ARRAY_BUFFER, vbo_handles_[vbo_index]);
    gl::BufferData(gl::ARRAY_BUFFER, num_vertices * NORMAL_VECTOR_SIZE * sizeof(aNormals[0]), aNormals, gl::STATIC_DRAW);
    gl::VertexAttribPointer(vbo_index, NORMAL_VECTOR_SIZE, gl::FLOAT, gl::FALSE_, 0, (GLubyte *)NULL);
    gl::EnableVertexAttribArray(vbo_index);   // Vertex normals

    ++vbo_index;

    // Load Tangents
    if (load_tangents)
    {
        float *aTangents = new float [num_vertices * TANGENT_VECTOR_SIZE];

        for (JU::uint32 index = 0; index < num_vertices; ++index)
        {
    		aTangents[index * TANGENT_VECTOR_SIZE + 0] = vTangents[index].x;
    		aTangents[index * TANGENT_VECTOR_SIZE + 1] = vTangents[index].y;
    		aTangents[index * TANGENT_VECTOR_SIZE + 2] = vTangents[index].z;
    		aTangents[index * TANGENT_VECTOR_SIZE + 3] = vTangents[index].w;
        }

        // Normal VBO
        gl::BindBuffer(gl::ARRAY_BUFFER, vbo_handles_[vbo_index]);
        gl::BufferData(gl::ARRAY_BUFFER, num_vertices * TANGENT_VECTOR_SIZE * sizeof(aTangents[0]), aTangents, gl::STATIC_DRAW);
        gl::VertexAttribPointer(vbo_index, TANGENT_VECTOR_SIZE, gl::FLOAT, gl::FALSE_, 0, (GLubyte *)NULL);
        gl::EnableVertexAttribArray(vbo_index);   // Vertex tangents

        delete [] aTangents;

        ++vbo_index;
    }

    // Load the INDICES
    JU::uint32 num_triangles = vTriangleIndices.size();
    JU::uint16* aIndices = new JU::uint16[num_triangles * 3];

    for (JU::uint32 triangle = 0; triangle < num_triangles; ++triangle)
    {
    	aIndices[triangle * 3 + 0] = vTriangleIndices[triangle].v0_;
    	aIndices[triangle * 3 + 1] = vTriangleIndices[triangle].v1_;
    	aIndices[triangle * 3 + 2] = vTriangleIndices[triangle].v2_;
    }

    // Allocate and initialize VBO for vertex indices
    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, vbo_handles_[vbo_index]);
    gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, num_triangles * 3 * sizeof(aIndices[0]), aIndices, gl::STATIC_DRAW);

    // Clean up
    delete [] aPositions;
    delete [] aNormals;
    delete [] aTexCoords;
    delete [] aIndices;

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
	const VectorTriangleIndices& vTriangleIndices = getTriangleIndices();

    gl::BindVertexArray(vao_handle_);
    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, vbo_handles_[num_buffers_ - 1]);
    gl::DrawElements(gl::TRIANGLES, 3 * vTriangleIndices.size(), gl::UNSIGNED_SHORT, 0);
}

} // namespace JU
