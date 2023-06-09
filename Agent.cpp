#include "Agent.h"
#include "App.h"

Maze& Agent::maze() { return App::Instance()->maze; }


Cell* Agent::currentCellPtr() { 
	Maze& m = maze();
	return m.cellPtr(r, c); 
}

void Agent::move(D d) {

	switch (d)
	{
	case D::North: { r -= stepSize; } break;
	case D::East: { c += stepSize; } break;
	case D::South: { r += stepSize; } break;
	case D::West: { c -= stepSize; } break;
	default: { assert(false); } return;
	}

	onVisitCell();
	return;
}

void Agent::update() {
	if (complete) return;

	D nd = nextDirection();

	if (nd == D::NA)
		nd = backtrack();

	if (nd == D::NA) {
		onComplete();
		return;
	}

	move(nd);
}

Cell* Agent::peek(D d) { return peek(d, stepSize); }

Cell* Agent::peek(D d, int peekSize) {
	int pr = r;
	int pc = c;
	switch (d)
	{
	case D::North: { pr = r - peekSize; } break;
	case D::East: { pc = c + peekSize; } break;
	case D::South: { pr = r + peekSize; } break;
	case D::West: { pc = c - peekSize; } break;
	default: { assert(false); } break;
	}
	Cell* p = maze().cellPtr(pr, pc);
	return p;
}


std::vector<D> Agent::possibleDirections()
{
	std::vector<D> dirs;
	D ds[] = { D::North, D::East, D::South, D::West };
	for (D d : ds) {
		auto p = peek(d);
		if (!p)				continue;
		if (p->isBlock())	continue;
		if (p->isVisited()) continue;
		dirs.emplace_back(d);
	}
	return dirs;
}

std::vector<Cell*> Agent::possibleCells()
{
	std::vector<Cell*> ps;
	auto ds = possibleDirections();
	for (D d : ds) {
		auto p = peek(d);
		assert(p);
		ps.emplace_back(p);
	}
	return ps;
}

D Agent::backtrack() {

	while (true) {
		if (!history.size()) return D::NA;

		Index h = history.back();
		history.pop_back();
		r = h.r;
		c = h.c;
		D d = nextDirection();
		if (d == D::NA)
			continue;
		return d;
	}

	return D::NA;
}

D Agent::nextDirection() {
	auto dirs = possibleDirections();
	int nDirs = static_cast<int>(dirs.size());
	if (!nDirs)
		return D::NA;
	int idx = getRandInt(nDirs);
	assert(idx < nDirs);
	return dirs[idx];

}

void Agent::draw(HDC hdc) {
	POINT pos = maze().cellPos(r, c);
	auto oldBrush = SelectObject(hdc, GetStockObject(DC_BRUSH));
	auto oldColor = SetDCBrushColor(hdc, COLOR_RED);
	::Rectangle(hdc, pos.x, pos.y, pos.x + Cell::size, pos.y + Cell::size);
	SetDCBrushColor(hdc, oldColor);
	SelectObject(hdc, oldBrush);
}

void Agent::init(int r_, int c_, int stepSize_) {
	r = r_;
	c = c_;
	stepSize = stepSize_;
	Agent::onVisitCell();
}



void Agent::onComplete() { complete = true; }

void Agent::onVisitCell() {
	Cell* p = currentCellPtr();
	assert(p);
	p->setVisit(true);
	history.emplace_back(r, c);
}
