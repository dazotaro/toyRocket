#ifndef GRAPHICSDEFS_HPP_
#define GRAPHICSDEFS_HPP_

// Global includes
#include <vector>               // vector
#include <glm/glm.hpp>          // glm::vec*
// Local includes
#include "../core/Defs.hpp"     // Built-in data types typdefs

namespace JU
{

const int TAB_KEY = 9;

const int MIDDLE_BUTTON_SCROLL_UP   = 3;
const int MIDDLE_BUTTON_SCROLL_DOWN = 4;

typedef uint16 VertexIndex;

struct VertexIndices
{
    VertexIndices (JU::uint32 position = 0, JU::uint32 normal = 0, JU::uint32 tex = 0)
        : position_(position), normal_(normal), tex_(tex) {}

    JU::uint32 position_;
    JU::uint32 normal_;
    JU::uint32 tex_;

    bool operator==(const VertexIndices& rhs) const
    {
        if (position_ != rhs.position_ || normal_ != rhs.normal_ || tex_ != rhs.tex_)
            return false;

        return true;
    }
};

struct TriangleIndices
{
    TriangleIndices (VertexIndex v0 = 0, VertexIndex v1 = 0, VertexIndex v2 = 0)
        : v0_(v0), v1_(v1), v2_(v2) {}

    VertexIndex v0_;
    VertexIndex v1_;
    VertexIndex v2_;
};

// TYPEDEFS
typedef std::vector<glm::vec3> VectorPositions;
typedef VectorPositions::const_iterator VectorPositionsConstIter;
typedef std::vector<glm::vec3> VectorNormals;
typedef VectorNormals::const_iterator VectorNormalsConstIter;
typedef std::vector<glm::vec2> VectorTexCoords;
typedef VectorTexCoords::const_iterator VectorTexCoordsConstIter;
typedef std::vector<glm::vec4> VectorTangents;
typedef VectorTangents::const_iterator VectorTangentsConstIter;
typedef std::vector<VertexIndices> VectorVertexIndices;
typedef VectorVertexIndices::const_iterator VectorVertexIndicesConstIter;
typedef std::vector<TriangleIndices> VectorTriangleIndices;
typedef VectorTriangleIndices::const_iterator VectorTriangleIndicesConstIter;

} // namespace JU

#endif // GRAPHICSDEFS_HPP_
