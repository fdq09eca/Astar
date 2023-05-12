#pragma once
#include "Cell.h"
#include "App.h"

struct PathHistory { int r = 0; int c = 0; };

class Agent //mazeBuilder
{
	using H = PathHistory;
	using D = MyDirection;
private:
	int r = 1;
	int c = 1;
	std::vector<H> history;


public:
	Maze& maze() { return App::Instance()->maze; }

	Cell* currentCellPtr() { maze().cell(r, c); }

	void move(D d, int stepSize = 2) {
		switch (d)
		{
			case D::North: { r -= stepSize; } return;
			case D::East: { c -= stepSize; } return;
			case D::South: { r += stepSize; } return;
			case D::West: { c += stepSize; } return;
			default: { assert(false); } return;
		}
		return;
	}

	Cell* peek(D d, int stepSize = 2)  {
		int pr = 0;
		int pc = 0;
		switch (d)
		{
			case D::North:	{ pr = r - stepSize; } break;
			case D::East:	{ pc = c - stepSize; } break;
			case D::South:	{ pr = r + stepSize; } break;
			case D::West:	{ pc = c + stepSize; } break;
			default: { assert(false); } break;
		}
		Cell* p = maze().cellPtr(pr, pc);
		return p;
	}

	D opposite(D d) {
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

	Cell* unVisitedNeigbour() {
		std::set<D> ds = { D::North, D::East, D::South, D::West };
		D d;
		while (true) {
			if (!ds.size()) return nullptr;
			int v = getRandInt(ds.size() - 1) + 1;
			D d = static_cast<D>(v);
			if (ds.find(d) == ds.end())
				continue;
			ds.erase(d);
			Cell* c = peek(d);
			assert(!c->isBlock());
			if (c->isVisited()) {
				continue;
			} else {
				return c;
			}
		}
		return nullptr;
	}

	Cell* backTrackNeighbour() {
		while (true) {
			if (!history.size()) 
				return nullptr;
			
			H h = history.back();
			history.pop_back();
			Cell* c = maze().cellPtr(h.r, h.c);
		}
	}

	


	void drawAt(HDC hdc, POINT pos) const {
		auto oldBrush = SelectObject(hdc, GetStockObject(DC_BRUSH));
		auto oldColor = SetDCBrushColor(hdc, COLOR_RED);
		::Rectangle(hdc, pos.x, pos.y, pos.x + Cell::size, pos.y + Cell::size);
		SetDCBrushColor(hdc, oldColor);
		SelectObject(hdc, oldBrush);
	}
};

