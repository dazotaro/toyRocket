/*
 * MeshImporter.hpp
 *
 *  Created on: Feb 16, 2017
 *      Author: jusabiaga
 */

#ifndef MESHIMPORTER_HPP_
#define MESHIMPORTER_HPP_


namespace JU
{

// Forward Declarations
class Mesh2;

class MeshImporter
{
    public:
        static bool import(const char* filename, Mesh2& mesh);
};

} /* namespace JU */

#endif /* MESHIMPORTER_HPP_ */
