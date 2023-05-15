#include "Cell.h"

bool Cell::isState(State s) const { return (state & s) == s; }

void Cell::setState(State s, bool b) {
	if (b)
		state |= s;
	else
		state &= ~s;
}

bool Cell::isVisited() const {
	if (isState(State::Block)) return false;
	return isState(State::Visited);
}



bool Cell::isBlock() const { return isState(State::Block); }

COLORREF Cell::color() const {
	if (isBlock())
		return COLOR_BLACK;
	return isVisited() ? COLOR_GREY : COLOR_WHITE;
}

void Cell::drawAt(HDC hdc, POINT pos) const {
	drawAt(hdc, pos, color());
}


void Cell::drawAt(HDC hdc, POINT pos, COLORREF color_) const {
	auto oldBrush = SelectObject(hdc, GetStockObject(DC_BRUSH));
	auto oldColor = SetDCBrushColor(hdc, color_);
	::Rectangle(hdc, pos.x, pos.y, pos.x + size, pos.y + size);
	SetDCBrushColor(hdc, oldColor);
	SelectObject(hdc, oldBrush);
}
