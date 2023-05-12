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
	int r = 1;
	int c = 1;
	std::vector<Index> history;


public:
	Maze& maze();

	Cell* currentCellPtr();

	void move(D d, int stepSize = 2);

	Cell* peek(D d, int stepSize = 2);

	D opposite(D d);

	Cell* unVisitedNeigbour(D& outD);;

	Cell* backTrackNeighbour();;

	void draw(HDC hdc) const;
};

