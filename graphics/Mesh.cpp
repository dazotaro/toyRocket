/*
 * Mesh.cpp
 *
 *  Created on: May 2, 2013
 *      Author: jusabiaga
 */

#include <iostream>     // std::cout
#include "Mesh.hpp"       // Mesh

namespace JU
{

/**
* @brief Non-Default Constructor
*
* @param name Id of the Mesh
* @param positions Vector with all vertex positions
* @param normals Vector with all vertex normals
* @param colors Vector with all vertex colors
* @param tex_coords Vector with all vertex colors
* @param faces Vector with all info about the faces of the Mesh
*/
Mesh::Mesh(const std::string  &name,
           const PositionList &positions,
           const NormalList   &normals,
           const TangentList  &tangents,
           const ColorList    &colors,
           const TexCoordList &tex_coords,
           const FaceList     &faces) :
                   name_(name),
                   positions_(positions),
                   normals_(normals),
                   tangents_(tangents),
                   colors_(colors),
                   tex_coords_(tex_coords),
                   faces_(faces)
{
}

Mesh::~Mesh()
{
    // TODO Auto-generated destructor stub
}

const Mesh::ColorList& Mesh::getColors() const
{
    return colors_;
}

const Mesh::FaceList& Mesh::getFaces() const
{
    return faces_;
}

const std::string& Mesh::getName() const
{
    return name_;
}

const Mesh::NormalList& Mesh::getNormals() const
{
    return normals_;
}

const Mesh::TangentList& Mesh::getTangents() const
{
    return tangents_;
}

const Mesh::PositionList& Mesh::getPositions() const
{
    return positions_;
}

const Mesh::TexCoordList& Mesh::getTexCoords() const
{
    return tex_coords_;
}

void Mesh::exportOBJ(void) const
{
    std::cout << "Object Name =  " << name_ << std::endl;

    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "POSITIONS START:" << std::endl;
    std::cout << "Number of positions: " << positions_.size() << std::endl;
    for (PositionListConstIterator iter = positions_.begin(); iter != positions_.end(); ++iter)
    {
        std::cout << "\t" << iter->x << ", " << iter->y << ", " << iter->z << std::endl;
    }
    std::cout << "POSITIONS END:" << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "NORMALS START:" << std::endl;
    std::cout << "Number of normals: " << normals_.size() << std::endl;
    for (NormalListConstIterator iter = normals_.begin(); iter != normals_.end(); ++iter)
    {
        std::cout << "\t" << iter->x << ", " << iter->y << ", " << iter->z << std::endl;
    }
    std::cout << "NORMALS END:" << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "TANGENTS START:" << std::endl;
    std::cout << "Number of tangents: " << tangents_.size() << std::endl;
    for (TangentListConstIterator iter = tangents_.begin(); iter != tangents_.end(); ++iter)
    {
        std::cout << "\t" << iter->x << ", " << iter->y << ", " << iter->z << std::endl;
    }
    std::cout << "TANGENTS END:" << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "COLORS START:" << std::endl;
    std::cout << "Number of colors: " << colors_.size() << std::endl;
    for (ColorListConstIterator iter = colors_.begin(); iter != colors_.end(); ++iter)
    {
        std::cout << "\t" << iter->r << ", " << iter->g << ", " << iter->b << ", " << iter->a << std::endl;
    }
    std::cout << "COLORS END:" << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "TEXTURE COORDINATES START:" << std::endl;
    std::cout << "Number of texture-coordinates: " << tex_coords_.size() << std::endl;
    for (TexCoordListConstIterator iter = tex_coords_.begin(); iter != tex_coords_.end(); ++iter)
    {
        std::cout << "\t" << iter->s << ", " << iter->t << std::endl;
    }
    std::cout << "TEXTURE COORDINATES END:" << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "Faces START:" << std::endl;

    // For each face
    FaceListConstIterator face_iter;
    for (face_iter = faces_.begin(); face_iter != faces_.end(); ++face_iter)
    {
        IndexList indices;

        std::cout << "  Face" << std::endl;
        
        // POSITIONS
        face_iter->getIndices(Face::VERTEX_INDEX, indices);

        std::cout << "\tVertex Indexes = (";
        // For each vertex of a face
        IndexListConstIterator index_iter;
        for (index_iter = indices.begin(); index_iter != indices.end(); ++index_iter)
        {
            std::cout << *index_iter << " ";
        }
        std::cout << ")" << std::endl;

        // COLORS
        face_iter->getIndices(Face::COLOR_INDEX, indices);

        std::cout << "\tColor Indexes = (";
        // For each vertex of a face
        for (index_iter = indices.begin(); index_iter != indices.end(); ++index_iter)
        {
            std::cout << *index_iter << " ";
        }
        std::cout << ")" << std::endl;

        // TEXTURE COORDINATES
        face_iter->getIndices(Face::TEXTURE_INDEX, indices);

        std::cout << "\tTexture Indexes = (";
        // For each vertex of a face
        for (index_iter = indices.begin(); index_iter != indices.end(); ++index_iter)
        {
            std::cout << *index_iter << " ";
        }
        std::cout << ")" << std::endl;

    }

    std::cout << "Faces END:" << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

}

std::ostream & operator<<(std::ostream &out, const Mesh &rhs)
{
    out << "Object Name =  " << rhs.name_ << std::endl;

    out << "----------------------------------------------------------" << std::endl;
    out << "POSITIONS START:" << std::endl;
    out << "Number of positions: " << rhs.positions_.size() << std::endl;
    for (Mesh::PositionListConstIterator iter = rhs.positions_.begin(); iter != rhs.positions_.end(); ++iter)
    {
        out << "\t" << iter->x << ", " << iter->y << ", " << iter->z << std::endl;
    }
    out << "POSITIONS END:" << std::endl;
    out << "----------------------------------------------------------" << std::endl;

    out << "----------------------------------------------------------" << std::endl;
    out << "NORMALS START:" << std::endl;
    out << "Number of normals: " << rhs.normals_.size() << std::endl;
    for (Mesh::NormalListConstIterator iter = rhs.normals_.begin(); iter != rhs.normals_.end(); ++iter)
    {
        out << "\t" << iter->x << ", " << iter->y << ", " << iter->z << std::endl;
    }
    out << "NORMALS END:" << std::endl;
    out << "----------------------------------------------------------" << std::endl;

    out << "----------------------------------------------------------" << std::endl;
    out << "TANGENTS START:" << std::endl;
    out << "Number of tangents: " << rhs.tangents_.size() << std::endl;
    for (Mesh::TangentListConstIterator iter = rhs.tangents_.begin(); iter != rhs.tangents_.end(); ++iter)
    {
        out << "\t" << iter->x << ", " << iter->y << ", " << iter->z << std::endl;
    }
    out << "TANGENTS END:" << std::endl;
    out << "----------------------------------------------------------" << std::endl;

    out << "----------------------------------------------------------" << std::endl;
    out << "COLORS START:" << std::endl;
    out << "Number of colors: " << rhs.colors_.size() << std::endl;
    for (Mesh::ColorListConstIterator iter = rhs.colors_.begin(); iter != rhs.colors_.end(); ++iter)
    {
        out << "\t" << iter->r << ", " << iter->g << ", " << iter->b << ", " << iter->a << std::endl;
    }
    out << "COLORS END:" << std::endl;
    out << "----------------------------------------------------------" << std::endl;

    out << "----------------------------------------------------------" << std::endl;
    out << "TEXTURE COORDINATES START:" << std::endl;
    out << "Number of texture-coordinates: " << rhs.tex_coords_.size() << std::endl;
    for (Mesh::TexCoordListConstIterator iter = rhs.tex_coords_.begin(); iter != rhs.tex_coords_.end(); ++iter)
    {
        out << "\t" << iter->s << ", " << iter->t << std::endl;
    }
    out << "TEXTURE COORDINATES END:" << std::endl;
    out << "----------------------------------------------------------" << std::endl;

    out << "----------------------------------------------------------" << std::endl;
    out << "Faces START:" << std::endl;

    // For each face
    Mesh::FaceListConstIterator face_iter;
    for (face_iter = rhs.faces_.begin(); face_iter != rhs.faces_.end(); ++face_iter)
    {
        Mesh::IndexList indices;

        out << "  Face" << std::endl;

        // VERTICES
        face_iter->getIndices(Mesh::Face::VERTEX_INDEX, indices);

        out << "\tPosition Indexes = (";
        // For each vertex of a face
        Mesh::IndexListConstIterator index_iter;
        for (index_iter = indices.begin(); index_iter != indices.end(); ++index_iter)
        {
            out << *index_iter << " ";
        }
        out << ")" << std::endl;

        // COLORS
        face_iter->getIndices(Mesh::Face::COLOR_INDEX, indices);

        out << "\tColor Indexes = (";
        // For each vertex of a face
        for (index_iter = indices.begin(); index_iter != indices.end(); ++index_iter)
        {
            out << *index_iter << " ";
        }
        out << ")" << std::endl;

        // TEXTURE COORDINATES
        face_iter->getIndices(Mesh::Face::TEXTURE_INDEX, indices);

        out << "\tTexture Indexes = (";
        // For each vertex of a face
        for (index_iter = indices.begin(); index_iter != indices.end(); ++index_iter)
        {
            out << *index_iter << " ";
        }
        out << ")" << std::endl;

    }

    out << "Faces END:" << std::endl;
    out << "----------------------------------------------------------" << std::endl;

    return out;
}

void Mesh::export2OBJ(const char *filename) const
{
    FILE *file = fopen(filename, "w");

    if (!file)
    {
        printf("Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Print the header
    fprintf(file, "# CS300 Graphics::Mesh to obj exporter\n");

    // POSITIONS
    for (PositionListConstIterator iter = positions_.begin(); iter != positions_.end(); ++iter)
    {
        fprintf(file, "v %f %f %f\n", iter->x, iter->y, iter->z);
    }

    // TEXTURE COORDINATES
    for (TexCoordListConstIterator iter = tex_coords_.begin(); iter != tex_coords_.end(); ++iter)
    {
        fprintf(file, "vt %f %f\n", iter->s, iter->t);
    }

    // NORMALS
    for (NormalListConstIterator iter = normals_.begin(); iter != normals_.end(); ++iter)
    {
        fprintf(file, "vn %f %f %f\n", iter->x, iter->y, iter->z);
    }

    // Use material
    fprintf(file, "usemtl (null)\n");

    // Smoothing
    fprintf(file, "s off\n");

    // Print face information (each face is a triangle)
    FaceListConstIterator face_iter;
    for (face_iter = faces_.begin(); face_iter != faces_.end(); ++face_iter)
    {
        fprintf(file, "f ");

        // For each vertex of a face
        IndexList vertex_indices;
        face_iter->getIndices(Face::VERTEX_INDEX, vertex_indices);
        IndexList color_indices;
        face_iter->getIndices(Face::COLOR_INDEX, color_indices);
        IndexList tex_coord_indices;
        face_iter->getIndices(Face::TEXTURE_INDEX, tex_coord_indices);

        if ((vertex_indices.size() != color_indices.size()) || (vertex_indices.size() != tex_coord_indices.size()))
        {
            std::cout << "Incorrect number of indices for one of the attributes" << std::endl;
            exit(EXIT_FAILURE);
        }
        // For each vertex of a face
        unsigned int index;
        for (index = 0; index < vertex_indices.size(); ++index)
        {
            fprintf (file, "  %i/%i/%i",  vertex_indices[index] + 1, tex_coord_indices[index] + 1, vertex_indices[index] + 1);
        }

        fprintf (file, " \n");
    }

    fclose(file);
}

} // namespace JU
