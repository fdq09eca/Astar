#pragma once
#include "AppObject.h"
#include "Cell.h"

class Maze : public AppObject
{
public:
	std::vector<Cell> cells;
	int nRow = 0;
	int nCol = 0;
	int yOffset = 0; 
	int xOffset = 0;
	
	void init(int nRow_ = 10, int nCol_ = 10) {
		nRow = nRow_;
		nCol = nCol_;
		_type = Type::Maze;
		int nCells = nRow_ * nCol_;
		cells.resize(nCells);
	}

	const Cell& cell(int r, int c) {

		return cells[r * nRow + c];
	}

	const Cell& cell(POINT p) {
		int r = p.y / Cell::size;
		int c = p.x / Cell::size;
		return cell(r, c);

	}

	int width() const { return nCol * Cell::size; }
	int height() const { return nRow * Cell::size; }

	void draw(HDC hdc) const {
		
		POINT pos{ xOffset, yOffset };
		int w = width();
		for (const auto& c : cells) {
			c.drawAt(hdc, pos);
			pos.y += Cell::size;
			if (pos.y >= w) {
				pos.x += Cell::size;
				pos.y = yOffset;
			}
		}
	}

	
};

