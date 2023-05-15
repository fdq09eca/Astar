#include "Maze.h"
#include "MazeBuilder.h"

void Maze::init(int nRow_, int nCol_) {
	nRow = nRow_;
	nCol = nCol_;
	cells.resize(nCells());
	genDefault();
	MazeBuilder::build();
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



void Maze::genRandom(int nb) {
	// https://www.youtube.com/watch?v=Y37-gB83HKE&t=514s
	reset();
	std::set<int> vals;
	int i;
	for (int n = 0; n < nb; n++) {
		Cell* p = nullptr;
		while (true) {
			i = getRandInt(nRow * nCol - 1);
			if (auto b = vals.find(i) != vals.end()) { continue; };
			break;
		}
		vals.insert(i);
		cells[i].setBlock(true);
	}
}

void Maze::genDefault() {
	reset();
	assert(nCol % 2 && nRow % 2); // for now.
	for (int c = 0; c < nCol; c++) {
		for (int r = 0; r < nRow; r++) {
			if (!(r % 2) || !(c % 2)) {
				auto p = cellPtr(r, c);
				assert(p);
				p->setBlock(true);
			}
		}
	}
}

POINT Maze::cellPos(int r, int c)  const {
	POINT pos;
	pos.x = r * Cell::size + xOffset;
	pos.y = c * Cell::size + yOffset;
	return pos;
}

void Maze::draw(HDC hdc) const {
	for (int c = 0; c < nCol; c++) {
		for (int r = 0; r < nRow; r++) {
			auto p = cellPtr(r, c);
			assert(p);
			POINT pos = cellPos(r, c);
			p->drawAt(hdc, pos);

		}
	}
}
