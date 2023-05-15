#pragma once
#include "Util.h"
#include "Cell.h"

struct RcIndex {
	int r = 0; int c = 0;
	
	RcIndex() = default;
	RcIndex(int r_, int c_) : r(r_), c(c_) {};
	
	bool isInvalid() { return  r < 0 || c < 0; }
	bool setInvalid() { return r = -1; c = -1; }

	bool operator==(const RcIndex& idx) const { return idx.r == r && idx.c == c; }
	bool operator!=(const RcIndex& idx) const { return !operator==(idx); }
};

using Index = RcIndex;
using D = MyDirection;

class Maze;
class Agent
{

protected:
	int r = 0;
	int c = 0;
	int stepSize = 0;

	bool complete = false;
	std::vector<Index> history;
	

public:
	Maze& maze();
	Agent() = default;
	Agent(int r_, int c_, int stepSize_) : r(r_), c(c_), stepSize(stepSize_) {};

	virtual ~Agent() {};
	Cell* currentCellPtr();
	inline Index currentCellIndex() { return Index(r, c); }
	void move(D d);

	virtual void update();

	Cell* peek(D d, int peekSize);

	Cell* peek(D d);
	
	D backtrack();
	virtual void onComplete();
	virtual D nextDirection();
	virtual std::vector<D> possibleDirections();
	std::vector<Cell*> possibleCells();
	virtual void init(int r_, int c_, int stepSize_) ;
	virtual void onVisitCell();


	virtual void draw(HDC hdc);

};

