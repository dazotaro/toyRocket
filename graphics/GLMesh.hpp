/*
 * GLMesh.hpp
 *
 *  Created on: May 7, 2013
 *      Author: jusabiaga
 */

#ifndef GLMESH2_HPP_
#define GLMESH2_HPP_

#include "gl_core_4_2.h"                // glLoadGen generated header file
#include "Mesh2.hpp"     // Mesh2

/**
 * @brief      Mesh2 adapter to OpenGL.
 *
 * @details    This should be a 'Flyweight' pattern, so models only exist once. It needs to:
 *              + Load the Mesh2 into GL's VBOs (Vertex Buffer Object) and VAO (Vertex Array Object)
 *              + It needs to draw the Mesh2 in OpenGL
 *              There should only be a GLMesh per Mesh2 object; if we want to have two instances of the same model,
 *              this is accomplish by creating to GLMeshInstance objects, both sharing the same GLMesh under the hood.
 *
 * \todo Turn into 'flyweight'
 */
class GLMesh : public Mesh2
{
    public:
        explicit GLMesh(const Mesh2 &mesh);
        GLMesh(const std::string&				name,
        		const VectorPositions&			vPositions,
        		const VectorNormals&			vNormals,
        		const VectorTexCoords&			vTexCoords,
        		const VectorVertexIndices&		vVertexIndices,
        		const VectorTriangleIndices& 	vTriangleIndices);
        virtual ~GLMesh();

        virtual void draw(void) const;
        bool init(void);
        bool initVBOs(void);

    private:
        GLuint vao_handle_;         //!< Handle to VAO
        GLuint *vbo_handles_;
        JU::uint8 num_buffers_;
};

#endif /* GLMESH2_HPP_ */
