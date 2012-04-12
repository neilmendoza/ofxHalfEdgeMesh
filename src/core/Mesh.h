/*
 *  Mesh.h
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
#pragma once

#include <tr1/memory>
#include <map>

#include "ofVec3f.h"
#include "ofVboMesh.h"
#include "HalfEdge.h"
#include "Edge.h"

namespace ofxHalfEdgeMesh
{
	using namespace tr1;

	class Mesh : public ofVboMesh
	{
	public:
		typedef shared_ptr<Mesh> Ptr;
		virtual void buildEdgeData() = 0;
		virtual ~Mesh();
        
        HalfEdge::Ptr getHalfEdge(int vertexIdx);
		
	protected:
		void pairHalfEdges();
		vector<HalfEdge::Ptr> halfEdges;
		map<int, HalfEdge::Ptr> vertHalfEdges;
		
	private:
		vector<HalfEdge::Ptr> getUnpairedHalfEdges();
		vector<Edge::Ptr> edges;
		
		struct VertexInfo
		{
			typedef shared_ptr<VertexInfo> Ptr;
			vector<HalfEdge::Ptr> out;
			vector<HalfEdge::Ptr> in;
		};
	};	
}
