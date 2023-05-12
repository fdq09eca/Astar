#pragma once
#include "AppObject.h"


enum class CellState {
	Unknown = 0,
	Visited = 1 << 1,
	Block = 2 << 2,
};

inline constexpr CellState operator& (CellState x, CellState y) {
	return static_cast<CellState>(static_cast<int>(x) & static_cast<int>(y));
}

inline constexpr CellState operator| (CellState x, CellState y) {
	return static_cast<CellState>(static_cast<int>(x) | static_cast<int>(y));
}

inline constexpr CellState operator^(CellState x, CellState y) {
	return static_cast<CellState> (static_cast<int>(x) ^ static_cast<int>(y));
}

inline constexpr CellState operator~(CellState x) {
	return static_cast<CellState>(~static_cast<int>(x));
}

inline CellState& operator&=(CellState& x, CellState y) {
	x = x & y;
	return x;
}

inline CellState& operator|=(CellState& x, CellState y) {
	x = x | y;
	return x;
}

inline CellState& operator^=(CellState& x, CellState y) {
	x = x ^ y;
	return x;
}


class Cell
{
	using State = CellState;
	
	bool isState(State s) const;
	void setState(State s, bool b);

	State state = State::Unknown;

public:
	static const int size = 20;

	Cell(){ init(); }
	inline void reset()				{ init(); }
	inline void init()				{ setBlock(false); setVisit(false); }
	inline void setBlock(bool b)	{ setState(State::Block, b); }
	inline void setVisit(bool b)	{ setState(State::Visited, b); }

	bool isVisited() const;	
	bool isBlock() const;

	COLORREF color() const;

	void drawAt(HDC hdc, POINT pos) const;


};


