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
	bool complete = false;

public:
	Cell* currentCellPtr();
	D nextDirection();
	
	void init(int r_, int c_, int stepSize_) { 
		r = r_; 
		c = c_;
		stepSize = stepSize_;
		onVisitCell();
	}
	
	inline void reset(){ init(1, 1, stepSize); }
	
	void move(D d);

	void update();

	Cell* peek(D d, int peekSize);

	Cell* peek(D d);

	const std::vector<D> possibleDirections();
	
	D backtrack();
	
	void draw(HDC hdc);

	void onComplete();

	void onVisitCell();

	void breakWall(D nd);
};

