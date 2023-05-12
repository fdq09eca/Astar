#pragma once
#include <stdio.h>
#include <Windows.h>
#include "windowsx.h"
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <fstream>


#define COLOR_WHITE		RGB(255,255,255)
#define COLOR_RED		RGB(255,0  ,0  )
#define COLOR_GREEN		RGB(0  ,255,0  )
#define COLOR_BLUE		RGB(0  ,  0,255)
#define COLOR_BLACK		RGB(0  ,0  ,0  )
#define COLOR_GREY		RGB(128,128,128)
#define COLOR_YELLOW	RGB(255,234,0  )



class NonCopyable {

private:
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;

public:
	NonCopyable() = default;
	~NonCopyable() = default;
};

enum class MouseButton {
	NA = 0,
	Left = 1 << 0,    // 1, 0001
	Middle = 1 << 1,  // 2, 0010 
	Right = 1 << 2,   // 4, 0100
};

inline constexpr MouseButton operator& (MouseButton x, MouseButton y) {
	return static_cast<MouseButton>(static_cast<int>(x) & static_cast<int>(y));
}

inline constexpr MouseButton operator| (MouseButton x, MouseButton y) {
	return static_cast<MouseButton>(static_cast<int>(x) | static_cast<int>(y));
}

inline constexpr MouseButton operator^(MouseButton x, MouseButton y) {
	return static_cast<MouseButton> (static_cast<int>(x) ^ static_cast<int>(y));
}

inline constexpr MouseButton operator~(MouseButton x) {
	return static_cast<MouseButton>(~static_cast<int>(x));
}

inline MouseButton& operator&=(MouseButton& x, MouseButton y) {
	x = x & y;
	return x;
}

inline MouseButton& operator|=(MouseButton& x, MouseButton y) {
	x = x | y;
	return x;
}

inline MouseButton& operator^=(MouseButton& x, MouseButton y) {
	x = x ^ y;
	return x;
}


enum class MouseEventType {
	None = 0,
	Up,
	Down,
	Move,
};



class MouseEvent {
public:
	using Type = MouseEventType;
	using Button = MouseButton;
	POINT pos{0,0};
	Type eventType = Type::None;
	Button button = Button::NA;
	Button buttonState = Button::NA;

	bool isUp()	  const { return eventType == Type::Up; }
	bool isDown() const { return eventType == Type::Down; }
	bool isMove() const { return eventType == Type::Move; }

	bool isLButton() const { return button == Button::Left; }
	bool isMButton() const { return button == Button::Middle; }
	bool isRButton() const { return button == Button::Right; }
};

class BackBuffer : NonCopyable {
	HBITMAP _bitmap;
	HBRUSH _bgColor = NULL;
	HDC _dc = NULL;
	int _w = 0;
	int _h = 0;

public:

	~BackBuffer() { destroy(); }

	void create(HWND hWnd_) {
		destroy();
		HDC wndDC = GetDC(hWnd_);
		_dc = CreateCompatibleDC(wndDC);

		RECT rc;
		GetClientRect(hWnd_, &rc);
		_h = rc.bottom - rc.top;
		_w = rc.right - rc.left;
		_bitmap = CreateCompatibleBitmap(wndDC, _w, _h); //https://stackoverflow.com/questions/7134465/the-result-of-createcompatibledc-only-has-two-colors
		SelectObject(_dc, _bitmap);
		_bgColor = (HBRUSH)GetStockObject(WHITE_BRUSH);

		ReleaseDC(hWnd_, wndDC);
	}

	HDC dc() const { return _dc; }

	void destroy() {
		if (_dc) {
			DeleteDC(_dc);
			_dc = NULL;
		}

		if (_bitmap) {
			DeleteObject(_bitmap);
			_bitmap = NULL;
		}
	}

	void clear() {
		RECT rc{ 0, 0, _w, _h };
		FillRect(_dc, &rc, _bgColor);
	}

	void draw(HDC hdc, int x = 0, int y = 0) {
		BitBlt(hdc, x, y, _w, _h, _dc, 0, 0, SRCCOPY);
	}
};

inline void writeInt(std::ofstream& f, int v) { f.write((char*)&v, sizeof(v)); } // worst implementation, problem: alignment; different cpu archi i.e. little/big endian?
inline void writeString(std::ofstream& f, const char* str) { f.write(str, strlen(str)); }

inline void readString(std::ifstream& f, char* buff, int nChar) {
	assert(!f.eof());
	f.read(buff, nChar);
}

inline void readInt(std::ifstream& f, int& v) {
	assert(!f.eof());
	f.read((char*)&v, sizeof(v));

}

class Vector2D {

public:
	double x = 0;
	double y = 0;

	Vector2D(double _x = 0, double _y = 0) : x(_x), y(_y) { }
	Vector2D(const Vector2D& v) { //copy
		x = v.x;
		y = v.y;
	}

	~Vector2D() { x = 0; y = 0; }

	double distance(const Vector2D& p) const {
		return (p - *this).length();
	}

	double length() const {
		return sqrt(x * x + y * y);
	}

	Vector2D unitVector() const {
		return *this / length();
	}

	double dotProduct(const Vector2D& p) const {
		return x * p.x + y * p.y;
	}

	Vector2D project(const Vector2D& v) const {
		Vector2D u = v.unitVector();
		double projectLen = dotProduct(u);
		return u * projectLen;
	}

	inline void operator=(const Vector2D& p) { *this = Vector2D(p); } //recursive here!!


	inline Vector2D operator+(const Vector2D& v) const { return Vector2D(x + v.x, y + v.y); }
	inline Vector2D operator-(const Vector2D& v) const { return Vector2D(x - v.x, y - v.y); }
	inline Vector2D operator*(const Vector2D& v) const { return Vector2D(x * v.x, y * v.y); }
	inline Vector2D operator/(const Vector2D& v) const { return Vector2D(x / v.x, y / v.y); }

	inline void operator+=(const Vector2D& v) { x += v.x; y += v.y; }
	inline void operator-=(const Vector2D& v) { x -= v.x; y -= v.y; }
	inline void operator*=(const Vector2D& v) { x *= v.x; y *= v.y; }
	inline void operator/=(const Vector2D& v) { x /= v.x; y /= v.y; }

	inline Vector2D operator*(int val) const { return Vector2D(x * val, y * val); }
	inline Vector2D operator/(int val) const { return Vector2D(x / val, y / val); }

	inline void operator*=(int val) { x *= val; y *= val; }
	inline void operator/=(int val) { x /= val; y /= val; }

	inline Vector2D operator*(float val) const { return Vector2D(x * val, y * val); }
	inline Vector2D operator/(float val) const { return Vector2D(x / val, y / val); }

	inline Vector2D operator*(double val) const { return Vector2D(x * val, y * val); }
	inline Vector2D operator/(double val) const { return Vector2D(x / val, y / val); }

	inline bool operator!=(const Vector2D& v) const { return v.x != x || v.y != y; }
	inline bool operator==(const Vector2D& v) const { return !operator!=(v); }


};

inline std::wstring my_getCurrentDirectory() {
	wchar_t buff[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, buff);
	std::wstring r = buff;
	return r;
};

template<class T>
inline void my_bzero(T& s) {
	memset(&s, 0, sizeof(s));
}



inline int getRandIntInRange(int min_, int max_) { 
	
	/*
	* // exclusive
	* // not uniformly distributed.
	* v1 = rand() % 100;         // v1 in the range 0 to 99
	* v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
	* v3 = rand() % 30 + 1985;   // v3 in the range 1985-2014 
	*/

	assert(min_ < max_);
	int range = max_ - min_;
	if (!range) return min_;
	int num = rand() % range + min_;
	return num;
}

inline int getRandInt(int max_ = RAND_MAX) {
	return getRandIntInRange(0, max_);
}


inline bool hasValue(const std::vector<int>& vec, int val) {
	for (const auto& v : vec) {
		if (v == val)
			return true;
	}
	return false;
}

enum class MyDirection { NA, North, East, South, West };

inline MyDirection opposite(MyDirection d) {
	using D = MyDirection;
	switch (d)
	{
	case D::North: return D::South;
	case D::East:  return D::West;
	case D::South: return D::North;
	case D::West:  return D::East;
	default: 
		assert(false);
	}
	return D::NA;
}