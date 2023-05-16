#pragma once
#include "Agent.h"



class AgentAstar : public Agent 
	//https://www.youtube.com/watch?v=-L-WgKMFuhE
	//https://www.youtube.com/watch?v=i0x5fj4PqP4&t=454s //<--
{
private:
	class Node {

	private:
		Node* parent = nullptr;
		Index idx{ -1, -1 };
		int _gCost = 0;

	public:
		Node(Index idx_) :idx(idx_) {};

		void updateGcost(Node& src) {
			_gCost = src._gCost + distance(*this, src);
			parent = &src;
		}

		int cost(Node dstNode) { return _gCost + heuristic(dstNode); }
		int heuristic(Node dstNode) { return distance(*this, dstNode); }
		int distance(Node a, Node b) { return abs(a.idx.r - b.idx.r) + abs(a.idx.c - b.idx.c); }
	};


	inline void init(int r_, int c_, int stepSize_) override { Agent::init(r_, c_, stepSize_); }

public:
	Index dst{ -1, -1 };
	Index src{ -1, -1 };
	std::vector<Index> frontier;
	
	AgentAstar();
	AgentAstar(Index src_, Index dst_) :Agent(src.r, src.c, 1), src(src_), dst(dst_) { assert(src != dst); };
	
	void init();
	Index cellPtrToIndex(Cell* p);
	Index randomIndex();
	void setDst(int r, int c);
	void setDst(Cell* p);
	void setSrc(int r_, int c_) { src.r = r_; src.c = c_; }
	void setCurrentIndex(Index idx);

	Cell* dstCellPtr();
	Index nextIndex();


	void moveTo(Index idx);
	void onVisitCell() override;


	inline int srcDistance(Index idx)	{ return distance(idx, src);}
	inline int dstDistance(Index idx)	{ return distance(idx, dst); }
	inline int cost(Index idx)			{ return srcDistance(idx) + dstDistance(idx); }
	inline int distance(int r0, int c0, int r1, int c1) { return abs(r0 - r1) + abs(c0 - c1); }
	inline int distance(Index i0, Index i1) { return distance(i0.r, i0.c, i1.r, i1.c); }


	Index backtrackIndex();
	
	void update() override;

	void onComplete() override;

	virtual void draw(HDC hdc) override;


	
};

