#pragma once
#include "Util.h"
#include "Cell.h"

struct RcIndex {
	int r = 0; int c = 0;
	RcIndex(int r_, int c_) : r(r_), c(c_) {};
};

using Index = RcIndex;
using D = MyDirection;

class Maze;


class Agent //mazeBuilder
{

private:
	int r = 0;
	int c = 0;
	int stepSize = 0;
	
	std::vector<Index> history;
	Maze& maze();

public:
	Cell* currentCellPtr();
	
	void init(int r_, int c_, int stepSize_) { 
		r = r_; 
		c = c_;
		stepSize = stepSize_;
		currentCellPtr()->setVisit(true);
		history.emplace_back(r, c);
	}


	void move(D d);

	void update();

	Cell* peek(D d, int peekSize);

	Cell* peek(D d);

	const std::vector<D> unVisitedNeigbourDirections();
	
	D backtrack();

	D nextDirection() {
		auto dirs = unVisitedNeigbourDirections();
		int nDirs = static_cast<int>(dirs.size());
		if (!nDirs) return D::NA;
		D nd = static_cast<D>(getRandInt(nDirs) + 1);
		return nd;
	}

	void draw(HDC hdc) ;
};

