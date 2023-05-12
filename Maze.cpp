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
	// https://www.youtube.com/watch?v=Y37-gB83HKE&t=514s
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

void Maze::gen() {
	reset();
	for (int c = 0; c < nCol; c++) {
		for (int r = 0; r < nRow; r++) {
			if (!(r % 2) || !(c % 2)) {
				auto p = cellPtr(r, c);
				assert(p);
				p->setBlock(true);
			}

			/*if (nCol % 2 == 0 && c == 0) {
				auto p = cellPtr(r, c);
				assert(p);
				p->setBlock(true);
			}*/
		}
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

/*
// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
struct TestVector {
	std::vector<int> vec{
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	};

	int nRow = 3;
	int nCol = 3;

	int& v(int r, int c) {
		int* p = (&vec.front() + r * nCol + c);
		return *p;
	}

	int* northNeighbour(int* p, int step = 1) {
		int* pv = (p - nCol * step);
		if (pv < &vec.front()) return nullptr;
		return pv;
	}
};



int main() {
	TestVector tv;
	int& v = tv.v(1, 1);
	printf("%d\n", v);
	printf("tv.northNeighbour: %d\n", *tv.northNeighbour(&v, 1));
	if (!tv.northNeighbour(&v, 2)) {
		printf("tv.northNeighbour(&v, 2) is null");
	}
	return 0;
}
*/