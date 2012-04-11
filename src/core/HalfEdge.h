/*
 *  HalfEdge.h
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

namespace ofxHalfEdgeMesh
{
	using namespace std;
	using namespace tr1;
	
	class Face;
	class Edge;
	
	class HalfEdge
	{
	public:
		typedef shared_ptr<HalfEdge> Ptr;
		
		int getVertexIdx() const { return vertexIdx; }
		void setVertexIdx(const int vertexIdx) { this->vertexIdx = vertexIdx; }
		
		shared_ptr<HalfEdge> getPrev() const { return prev; }
		void setPrev(const shared_ptr<HalfEdge> prev) { this->prev = prev; }
		
		shared_ptr<HalfEdge> getNext() const { return next; }
		void setNext(const shared_ptr<HalfEdge> next) { this->next = next; }
		
		shared_ptr<HalfEdge> getPair() const { return pair; }
		void setPair(const shared_ptr<HalfEdge> pair) { this->pair = pair; }
		
		shared_ptr<Edge> getEdge() const { return edge; }
		void setEdge(const shared_ptr<Edge> edge) { this->edge = edge; }
		
		shared_ptr<Face> getFace() const { return face; }
		void setFace(const shared_ptr<Face> face) { this->face = face; }
		
	private:
		int vertexIdx;
		shared_ptr<HalfEdge> prev;
		shared_ptr<HalfEdge> next;
		shared_ptr<HalfEdge> pair;
		shared_ptr<Face> face;
		shared_ptr<Edge> edge;
	};
}