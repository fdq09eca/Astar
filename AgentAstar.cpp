#include "AgentAstar.h"
#include "App.h"



AgentAstar::AgentAstar() : Agent() { }

void AgentAstar::init() {
	Agent::init(1, 1, 1);
	setSrc(r, c);
	dst = randomIndex();
}

Index AgentAstar::cellPtrToIndex(Cell* p) {
	assert(p);
	int r = maze().cellRow(p);
	int c = maze().cellCol(p);
	return Index(r, c); 
}



Index AgentAstar::randomIndex() {
	Maze& m = maze();
	auto unvisitedCells = m.unVisitedCells();
	int n = (int)unvisitedCells.size();
	int r = getRandInt(n);
	Cell* p = unvisitedCells[r];
	Index rIdx = cellPtrToIndex(p);
	if (maze().inRange(rIdx.r, rIdx.c)) {
		return rIdx;
	}
	assert(false);
	return Index{ -1, -1 };
}

void AgentAstar::setDst(int r, int c) {
	assert(maze().inRange(r, c));
	dst.r = r;
	dst.c = c;
}


void AgentAstar::setDst(Cell* p) {
	Index idx = cellPtrToIndex(p);
	setDst(idx.r, idx.c);

}

void AgentAstar::setCurrentIndex(Index idx) { r = idx.r; c = idx.c; }

Index AgentAstar::nextIndex() {
	std::vector<Cell*> pCells = possibleCells();

	if (pCells.size() == 0) { return Index{ -1, -1 }; }

	for (auto p : pCells) {
		Index idx = cellPtrToIndex(p);

		if (contains(history, idx)) continue;
		if (contains(frontier, idx)) continue;

		frontier.emplace_back(idx);
	}

	if (frontier.size() == 0) { return Index{ -1, -1 }; }

	std::sort(frontier.begin(), frontier.end(),  [this](Index p0, Index p1) { return cost(p0) > cost(p1); } );

	return frontier.back(); //minCostCell
}

void AgentAstar::moveTo(Index idx) {
	assert(maze().inRange(idx.r, idx.c));

	setCurrentIndex(idx);
	onVisitCell();
	return;
}

void AgentAstar::onVisitCell() {
	Agent::onVisitCell();
	frontier.pop_back();
}

inline Cell* AgentAstar::dstCellPtr() { return maze().cellPtr(dst.r, dst.c); }

Index AgentAstar::backtrackIndex() {
	printf("!!");
	return Index{ -1, -1 };
}

void AgentAstar::update() {

	if (complete) return;
	if (currentCellPtr() == dstCellPtr()) {
		onComplete();
		return;
	}

	Index nextIdx = nextIndex();

	if (nextIdx.isInvalid()) {
		nextIdx = backtrackIndex();
	}

	if (nextIdx.isInvalid()) {
		onComplete();
		return;
	}

	moveTo(nextIdx);
}

void AgentAstar::onComplete() {
	complete = true;
}

void AgentAstar::draw(HDC hdc) {
	Agent::draw(hdc);
	for (Index idx : frontier) {
		auto p = maze().cellPtr(idx.r, idx.c);
		assert(p);
		p->drawAt(hdc, maze().cellPos(idx.r, idx.c), COLOR_BLUE);
	}

	dstCellPtr()->drawAt(hdc, maze().cellPos(dst.r, dst.c), COLOR_GREEN);
	
}

