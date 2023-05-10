#pragma once
#include "AppObject.h"

class Cell
{
public:
	static const int size = 20;
	
	inline void drawAt(HDC hdc, POINT pos) const { Rectangle(hdc, pos.x, pos.y, pos.x + size, pos.y + size); };

};

