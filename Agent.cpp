#include "Agent.h"
#include "App.h"

Maze& Agent::maze() { return App::Instance()->maze; }


Cell* Agent::currentCellPtr() { return maze().cellPtr(r, c); }

void Agent::move(D d) {	
	
	switch (d)
	{
		case D::North: { r -= stepSize; } return;
		case D::East: { c -= stepSize; } return;
		case D::South: { r += stepSize; } return;
		case D::West: { c += stepSize; } return;
		default: { assert(false); } return;
	}
	
	Cell* p = currentCellPtr();
	assert(p);

	p->setVisit(true);
	history.emplace_back(r, c);

	return;
}

void Agent::update() {
	D nd = nextDirection();
	
	if (nd == D::NA)
		nd = backtrack();
	
	if (nd == D::NA) 
		return;

	move(nd);
	
	//if (AgentType::MazeBuilder) {
	Cell* p = peek(opposite(nd), 1);
	if (p && p->isBlock()) 
		p->setBlock(false);
	//}
}

Cell* Agent::peek(D d) { return peek(d, stepSize); }

Cell* Agent::peek(D d, int peekSize) {
	int pr = 0;
	int pc = 0;
	switch (d)
	{
		case D::North: { pr = r - peekSize; } break;
		case D::East: { pc = c - peekSize; } break;
		case D::South: { pr = r + peekSize; } break;
		case D::West: { pc = c + peekSize; } break;
		default: { assert(false); } break;
	}
	Cell* p = maze().cellPtr(pr, pc);
	return p;
}


const std::vector<D> Agent::unVisitedNeigbourDirections()
{
	std::vector<D> dirs;
	D ds[] = {D::North, D::East, D::South, D::West};
	for (D d : ds) {
		auto p = peek(d); 
		if (!p)					continue;
		if (!p->isBlock())		continue;
		if (!p->isVisited())	continue;
		dirs.emplace_back(d);
	}
	return dirs;
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

void Agent::draw(HDC hdc) {
	POINT pos = maze().cellPos(r, c);
	auto oldBrush = SelectObject(hdc, GetStockObject(DC_BRUSH));
	auto oldColor = SetDCBrushColor(hdc, COLOR_RED);
	::Rectangle(hdc, pos.x, pos.y, pos.x + Cell::size, pos.y + Cell::size);
	SetDCBrushColor(hdc, oldColor);
	SelectObject(hdc, oldBrush);
}
