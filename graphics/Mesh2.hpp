/*
 * Mesh2.hpp
 *
 *  Created on: Jun 2, 2014
 *      Author: jusabiaga
 */

#ifndef MESH2_HPP_
#define MESH2_HPP_

// Global includes
#include <glm/glm.hpp>      // glm::vec3, glm::vec2
#include <vector>           // std::vector
#include <string>           // std::string

// Local includes
#include "../core/Defs.hpp"	// uint32
#include "GraphicsDefs.hpp" // VertexPositions, VertexNormals...

namespace JU
{

class Mesh2
{
	public:

		Mesh2();
		Mesh2(const std::string&			name,
			  const VectorPositions&		vPositions,
			  const VectorNormals&			vNormals,
			  const VectorTexCoords&		vTexCoords,
			  const VectorVertexIndices&	vVertexIndices,
			  const VectorTriangleIndices& 	vTriangleIndices);

		virtual ~Mesh2();

		// UTILITY FUNCTIONS
		void computeTangents();

		// GETTERS
		const VectorVertexIndices& 		getVertexIndices() const;
		const VectorTriangleIndices& 	getTriangleIndices() const;
		const std::string& 				getName() const;
		const VectorNormals& 			getNormals() const;
		const VectorPositions& 			getPositions() const;
		const VectorTexCoords& 			getTexCoords() const;
		const VectorTangents&			getTangents() const;

		// EXPORT AND OUTPUT FUNCTIONS
		void exportOBJ(void) const;
		void export2OBJ(const char *filename) const;
		friend std::ostream& operator<<(std::ostream &out, const Mesh2 &rhs);

	private:

		std::string     	  name_;          	//!< ID of the Mesh
		VectorPositions		  vPositions_;    	//!< Vector of vertex coordinates
		VectorNormals      	  vNormals_;      	//!< Vector of vertex normals
		VectorTexCoords    	  vTexCoords_;    	//!< Vector of vertex texture coordinates
		VectorTangents		  vTangents_;		//!< Vector of vertex tangents
		VectorVertexIndices   vVertexIndices_;  //!< Vector of face indices
		VectorTriangleIndices vTriangleIndices_;//!< Vector of triangle indices
};

} // namespace JU

#endif /* MESH2_HPP_ */
