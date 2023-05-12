#include "Agent.h"
#include "App.h"

Maze& Agent::maze() { return App::Instance()->maze; }

Cell* Agent::currentCellPtr() { return maze().cellPtr(r, c); }

void Agent::move(D d, int stepSize) {

	history.emplace_back(r, c);

	switch (d)
	{
	case D::North: { r -= stepSize; } return;
	case D::East: { c -= stepSize; } return;
	case D::South: { r += stepSize; } return;
	case D::West: { c += stepSize; } return;
	default: { assert(false); } return;
	}

	// break wall
	Cell* p = peek(opposite(d), 1);
	if (p && p->isBlock()) p->setBlock(false);

	return;
}

Cell* Agent::peek(D d, int stepSize) {
	int pr = 0;
	int pc = 0;
	switch (d)
	{
	case D::North: { pr = r - stepSize; } break;
	case D::East: { pc = c - stepSize; } break;
	case D::South: { pr = r + stepSize; } break;
	case D::West: { pc = c + stepSize; } break;
	default: { assert(false); } break;
	}
	Cell* p = maze().cellPtr(pr, pc);
	return p;
}


D Agent::opposite(D d) {
	switch (d)
	{
	case D::North: return D::South;
	case D::East:  return D::West;
	case D::South: return D::North;
	case D::West:  return D::East;
	default: assert(false);
	}
	return D::NA;
}

Cell* Agent::unVisitedNeigbour(D& outD) {
	std::set<D> ds = { D::North, D::East, D::South, D::West };
	D d = D::NA;
	while (true) {
		int s = static_cast<int>(ds.size());
		if (!s) return nullptr;

		int v = getRandInt(s - 1) + 1;
		D d = static_cast<D>(v);

		assert(ds.find(d) != ds.end());  // must be found.

		ds.erase(d);
		Cell* c = peek(d, 2);

		if (!c || c->isVisited()) continue;

		assert(!c->isBlock());
		outD = d;
		return c;

	}
	return nullptr;
}

Cell* Agent::backTrackNeighbour() {

	while (true) {
		if (!history.size())
			return nullptr;

		Index h = history.back();
		history.pop_back();
		Cell* c = maze().cellPtr(h.r, h.c);
	}

}







void Agent::draw(HDC hdc) const {
	POINT pos{ 0, 0 };

	auto oldBrush = SelectObject(hdc, GetStockObject(DC_BRUSH));
	auto oldColor = SetDCBrushColor(hdc, COLOR_RED);
	::Rectangle(hdc, pos.x, pos.y, pos.x + Cell::size, pos.y + Cell::size);
	SetDCBrushColor(hdc, oldColor);
	SelectObject(hdc, oldBrush);
}
