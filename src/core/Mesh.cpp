/*
 *  Mesh.cpp
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
#include "Mesh.h"
#include "HalfEdge.h"
#include "Face.h"

namespace ofxHalfEdgeMesh
{
	Mesh::~Mesh() {}
	
	void Mesh::pairHalfEdges()
	{
		vector<HalfEdge::Ptr> unpairedHalfEdges = getUnpairedHalfEdges();
		map<int, VertexInfo::Ptr> vertexInfos;
		for (int i = 0; i < unpairedHalfEdges.size(); ++i)
		{
			// add this outgoing vertex info from the half edge
			int idx = unpairedHalfEdges[i]->getVertexIdx();
			map<int, VertexInfo::Ptr>::iterator it = vertexInfos.find(idx);
			if (it == vertexInfos.end())
			{
				vertexInfos.insert(make_pair(idx, VertexInfo::Ptr(new VertexInfo)));
				it = vertexInfos.find(idx);
			}
			it->second->out.push_back(unpairedHalfEdges[i]);
			
			// add the incoming vertex info from the half edge
			idx = unpairedHalfEdges[i]->getNext()->getVertexIdx();
			it = vertexInfos.find(idx);
			if (it == vertexInfos.end())
			{
				vertexInfos.insert(make_pair(idx, VertexInfo::Ptr(new VertexInfo)));
				it = vertexInfos.find(idx);
			}
			it->second->in.push_back(unpairedHalfEdges[i]);
		}
		
		for (map<int, VertexInfo::Ptr>::iterator it = vertexInfos.begin(); it != vertexInfos.end(); ++it)
		{
			VertexInfo::Ptr vInfo = it->second;
			for (int i = 0; i < vInfo->out.size(); ++i)
			{
				HalfEdge::Ptr out = vInfo->out[i];
				if (!out->getPair())
				{
					for (int j = 0; j < vInfo->in.size(); ++j)
					{
						HalfEdge::Ptr in = vInfo->in[j];
						if (!in->getPair() && 
							out->getVertexIdx() == in->getNext()->getVertexIdx() && 
							in->getVertexIdx() == out->getNext()->getVertexIdx())
						{
							out->setPair(in);
							in->setPair(out);
							Edge::Ptr edge = Edge::Ptr(new Edge);
							edge->setHalfEdge(out);
							out->setEdge(edge);
							in->setEdge(edge);
							edges.push_back(edge);
							break;
						}
					}
				}
			}
		}
	}
	
	vector<HalfEdge::Ptr> Mesh::getUnpairedHalfEdges()
	{
		vector<HalfEdge::Ptr> unpairedHalfEdges;
		unpairedHalfEdges.reserve(halfEdges.size());
		for (int i = 0; i < halfEdges.size(); ++i)
		{
			if (!halfEdges[i]->getPair()) unpairedHalfEdges.push_back(halfEdges[i]);
		}
		return unpairedHalfEdges;
	}
}
