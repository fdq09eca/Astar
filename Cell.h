#pragma once
#include "AppObject.h"



enum class CellState {
	Unknown = 0,
	Visited = 1 << 1,
	Block = 2 << 2,
};

class Cell
{
	using State = CellState;
	
	bool isState(State s) const { return (state & s) == s; }
	void setState(State s, bool b) {
		if (b)  
			state |= s; 
		else 
			state &= ~s; 
	}

public:
	static const int size = 20;
	State state = State::Unknown;

	Cell()
	{
		setBlock(false);
		setVisit(false);
	}


	
	void setBlock(bool b) { setState(State::Block, b); }
	void setVisit(bool b) { setState(State::Visited, b); }

	bool isVisited() const {
		if (isState(State::Block)) return false;
		return isState(State::Visited); 
	}
	
	bool isBlock() const { return isState(State::Block); }

	COLORREF Color() {
		if (isBlock()) return RGB(0, 0, 0);
		return isVisited() ? RGB(128, 128, 128) : RGB(255, 255, 255);
	}

	

	inline void drawAt(HDC hdc, POINT pos) const { Rectangle(hdc, pos.x, pos.y, pos.x + size, pos.y + size); };


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