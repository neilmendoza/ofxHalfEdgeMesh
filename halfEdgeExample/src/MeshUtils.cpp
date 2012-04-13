/*
 *  GeomUtils.cpp
 *
 *  Copyright (c) 2011, Neil Mendoza, http://www.neilmendoza.com
 *  All rights reserved. 
 *  
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions are met: 
 *  
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *  * Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 *  * Neither the name of 16b.it nor the names of its contributors may be used 
 *    to endorse or promote products derived from this software without 
 *    specific prior written permission. 
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 *  POSSIBILITY OF SUCH DAMAGE. 
 *
 */
#include "MeshUtils.h"

namespace itg
{
	void MeshUtils::genNormals(ofMesh& mesh)
	{
        zeroNormals(mesh);
		if (mesh.getMode() == OF_PRIMITIVE_TRIANGLE_STRIP || mesh.getMode() == OF_PRIMITIVE_TRIANGLE_FAN)
		{
			ofVec3f prevEdge = mesh.getVertex(getIndex(mesh, 1)) - mesh.getVertex(getIndex(mesh, 0));	
			for (int i = 2; i < getSize(mesh); ++i)
			{
				ofVec3f edge;
				switch (mesh.getMode())
				{
					case OF_PRIMITIVE_TRIANGLE_STRIP:
					{
						// calculate new edge
						edge = mesh.getVertex(getIndex(mesh, i)) - mesh.getVertex(getIndex(mesh, i - 1));
						// calcualte normal to new triangle
						ofVec3f normal = prevEdge.crossed(edge).normalize();
						if (i % 2) normal = -normal;
						// add normalised normal to every vertex in new triangle
						for (int j = 0; j < 3; ++j)
						{
							mesh.setNormal(getIndex(mesh, i - j), normal + mesh.getNormal(getIndex(mesh, i - j)));
						}
						break;
					}
						
					case OF_PRIMITIVE_TRIANGLE_FAN:
					{
						// calculate new edge
						edge = mesh.getVertex(getIndex(mesh, i)) - mesh.getVertex(getIndex(mesh, 0));
						// calcualte normal to new triangle
						ofVec3f normal = prevEdge.crossed(edge).normalize();
						// add normalised normal to every vertex in new triangle
						for (int j = 0; j < 2; ++j)
						{
							mesh.setNormal(getIndex(mesh, i - j), normal + mesh.getNormal(getIndex(mesh, i - j)));
						}
						mesh.setNormal(getIndex(mesh, 0), normal + mesh.getNormal(getIndex(mesh, 0)));
						break;
					}
						
					default:
						break;
				}
				prevEdge = edge;
			}
		}
        else if (mesh.getMode() == OF_PRIMITIVE_TRIANGLES)
        {
            if (getSize(mesh) % 3) ofLogError() << "Triangle mesh with number of vertices that is not divisible by 3";
            for (int i = 0; i < getSize(mesh) / 3; ++i)
            {
                ofVec3f side1 = mesh.getVertex(getIndex(mesh, i * 3 + 1)) - mesh.getVertex(getIndex(mesh, i * 3));
                ofVec3f side2 = mesh.getVertex(getIndex(mesh, i * 3 + 2)) - mesh.getVertex(getIndex(mesh, i * 3 + 1));
                ofVec3f normal = side1.crossed(side2).normalize();
                for (int j = 0; j < 3; ++j)
                {
                    mesh.setNormal(getIndex(mesh, i * 3 + j), normal + mesh.getNormal(i * 3 + j));
                }
            }
        }
        else ofLog(OF_LOG_ERROR, "mesh mode not specified");
        normalizeNormals(mesh);
	}
	
	int MeshUtils::getSize(ofMesh& mesh)
	{
		if (mesh.getNumIndices()) return mesh.getNumIndices();
		return mesh.getNumVertices();
	}
	
	int MeshUtils::getIndex(ofMesh& mesh, const int idx)
	{
		if (mesh.getNumIndices()) return mesh.getIndex(idx);
		return idx;
	}
	
	void MeshUtils::normalizeNormals(ofMesh& mesh)
	{
		for (int i = 0; i < mesh.getNumNormals(); ++i)
		{
			mesh.setNormal(i, mesh.getNormal(i).normalize());
		}
	}
	
	void MeshUtils::zeroNormals(ofMesh& mesh)
	{
		for (int i = 0; i < mesh.getNumVertices(); ++i)
		{
			mesh.addNormal(ofVec3f());
		}
	}
}