#include "AgentAstar.h"
#include "App.h"

Index AgentAstar::cellPtrToIndex(Cell* p) { 
	int r = maze().cellRow(p);
	int c = maze().cellCol(p);
	return Index(r, c); 
}

void AgentAstar::setRandomGoal() {
	Maze& m = maze();
	int n = m.nCells();
	int randIdx = getRandInt(n);
	setGoal(m.unVisitedCells()[randIdx]);
}

void AgentAstar::setGoal(Cell* p) { goal = cellPtrToIndex(p); }
