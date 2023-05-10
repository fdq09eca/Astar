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
	
	bool isState(State s) const { return (state & s) == s; }
	void setState(State s, bool b) {
		if (b)  
			state |= s; 
		else 
			state &= ~s; 
	}

	State state = State::Unknown;

public:
	static const int size = 20;

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

	COLORREF color() const {
		if (isBlock()) 
			return COLOR_BLACK;
		return isVisited() ? COLOR_GREY : COLOR_WHITE;
	}

	inline void drawAt(HDC hdc, POINT pos) const { 
		auto oldBrush = SelectObject(hdc, GetStockObject(DC_BRUSH));
		auto oldColor = SetDCBrushColor(hdc, color());
		::Rectangle(hdc, pos.x, pos.y, pos.x + size, pos.y + size); 
		SetDCBrushColor(hdc, oldColor);
		SelectObject(hdc, oldBrush);
	};


};

