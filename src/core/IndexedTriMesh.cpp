/*
 *  IndexedTriMesh.cpp
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
#include "IndexedTriMesh.h"
#include "Face.h"

namespace ofxHalfEdgeMesh
{
	void IndexedTriMesh::buildEdgeData()
	{
		if (getNumIndices())
		{
			switch (getMode())
			{
				case OF_PRIMITIVE_TRIANGLES:
				{
					for (int i = 0; i < getNumIndices() / 3; ++i)
					{
						Face::Ptr face = Face::Ptr(new Face);
						
						for (int j = 0; j < 3; ++j)
						{
							int idx = getIndex(3 * i + j);
							HalfEdge::Ptr halfEdge = HalfEdge::Ptr(new HalfEdge());
							halfEdges.push_back(halfEdge);
							halfEdge->setFace(face);
							if (!face->getHalfEdge()) face->setHalfEdge(halfEdge);
							halfEdge->setVertexIdx(idx);
							if (vertHalfEdge.find(idx) == vertHalfEdge.end())
							{
								vertHalfEdge.insert(make_pair(idx, halfEdge));
							}
						}
						
						// set up nexts
						for (int j = halfEdges.size() - 3; j < halfEdges.size() - 1; ++j)
						{
							halfEdges[j]->setNext(halfEdges[j + 1]);
						}
						halfEdges.back()->setNext(halfEdges[halfEdges.size() - 3]);
					}
					pairHalfEdges();
				}
					break;
				case OF_PRIMITIVE_TRIANGLE_STRIP:
				case OF_PRIMITIVE_TRIANGLE_FAN:
					break;
				default:
					break;
			}
		}
	}
}