#include "Maze.h"

void Maze::init(int nRow_, int nCol_) {
	nRow = nRow_;
	nCol = nCol_;
	_type = Type::Maze;
	cells.resize(nCells());
	gen();
}

const Cell* Maze::cellPtr(int r, int c) const {
	if (r >= 0 && r < nRow && c >= 0 && c < nCol)
		return &cells[r * nCol + c];
	return nullptr;
}

Cell* Maze::cellPtr(int r, int c) {
	if (r >= 0 && r < nRow && c >= 0 && c < nCol)
		return &cells[r * nCol + c];
	return nullptr;
}

const Cell& Maze::cell(int r, int c) const {
	auto p = cellPtr(r, c);
	assert(p);
	return *p;
}

const Cell& Maze::cell(POINT p) const {
	int r = p.y / Cell::size;
	int c = p.x / Cell::size;
	return cell(r, c);
}



void Maze::gen(int nb) {
	reset();
	std::set<int> vals;
	int i;
	for (int n = 0; n < nb; n++) {
		Cell* p = nullptr;
		while (true) {
			i = getRandInt(nRow * nCol - 1);
			if (auto b = vals.find(i) != vals.end()) {
				continue;
			};
			break;
		}
		vals.insert(i);
		cells[i].setBlock(true);
	}

}



void Maze::draw(HDC hdc) const {

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
