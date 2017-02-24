/*
 * GLMesh.hpp
 *
 *  Created on: May 7, 2013
 *      Author: jusabiaga
 */

#ifndef GLMESH2_HPP_
#define GLMESH2_HPP_

// Local includes
#include "gl_core_4_2.hpp"      // glLoadGen generated header file
#include "GraphicsDefs.hpp"     // VectorPositions, VectorNormas...
// Global includes
#include <string>               // std::string

namespace JU
{

// Forward declarations
class Mesh2;

/**
 * @brief      Mesh2 adapter to OpenGL.
 *
 * @details    This should be a 'Flyweight' pattern, so models only exist once. It needs to:
 *              + Load the Mesh2 into GL's VBOs (Vertex Buffer Object) and VAO (Vertex Array Object)
 *              + It needs to draw the Mesh2 in OpenGL
 *              There should only be a GLMesh per Mesh2 object; if we want to have two instances of the same model,
 *              this is accomplish by creating to GLMeshInstance objects, both sharing the same GLMesh under the hood.
 *
 */
class GLMesh
{
    public:
        GLMesh();
        virtual ~GLMesh();

        void release();
        virtual void draw(void) const;
        bool init(const Mesh2& mesh);
        bool initVBOs(const std::string&              name,
                      const VectorPositions&          vPositions,
                      const VectorNormals&            vNormals,
                      const VectorTangents&           vTangents,
                      const VectorTexCoords&          vTexCoords,
                      const VectorVertexIndices&      vVertexIndices,
                      const VectorTriangleIndices&    vTriangleIndices);

    private:
        bool        is_initialized_;    //!< Is mesh initialized
        GLuint      vao_handle_;        //!< Handle to VAO
        GLuint*     vbo_handles_;       //!< Array of vbo handles
        JU::uint8   num_buffers_;       //!< Number of vbos
        GLuint      num_triangles_;     //!< Number of triangles
};

} // namespace JU

#endif /* GLMESH2_HPP_ */
