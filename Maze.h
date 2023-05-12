#pragma once
#include "AppObject.h"
#include "Cell.h"
#include "Agent.h"

class Maze
{
public:
	std::vector<Cell> cells;
	int nRow = 0;
	int nCol = 0;
	int yOffset = 0; 
	int xOffset = 0;
	Agent agent;
	
	void init(int nRow_ = 10, int nCol_ = 10);

	const Cell* cellPtr(int r, int c) const;

	Cell* cellPtr(int r, int c);
	
	const Cell& cell(int r, int c) const;
	
	const Cell& cell(POINT p) const;

	inline int width() const { return nCol * Cell::size; }
	inline int height() const { return nRow * Cell::size; }

	inline int nCells() const { return nRow * nCol; }
	inline void reset() { for (auto& c : cells) { c.init(); } }
	
	void gen(int nb);

	void gen();

	POINT cellPos(int r, int c) const ;

	void draw(HDC hdc) const;

	
};

