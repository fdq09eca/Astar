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

// win32 
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

	void create(HWND hWnd_);

	HDC dc() const { return _dc; }

	void destroy();

	void clear();

	void draw(HDC hdc, int x = 0, int y = 0);
};


class Vector2D {

public:
	double x = 0;
	double y = 0;

	Vector2D(double _x = 0, double _y = 0);
	Vector2D(const Vector2D& v);

	~Vector2D() { x = 0; y = 0; }

	double distance(const Vector2D& p) const;

	double length() const;

	Vector2D unitVector() const;

	double dotProduct(const Vector2D& p) const;

	Vector2D project(const Vector2D& v) const;

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



template<class T>
inline void my_bzero(T& s) { memset(&s, 0, sizeof(s));}

template<class T>
inline bool contains(const std::vector<T>& vec, T val) {
	for (const auto& v : vec) {
		if (v == val)
			return true;
	}
	return false;
}

enum class MyDirection { NA, North, East, South, West };
MyDirection opposite(MyDirection d);


// Helpers
int getRandIntInRange(int min_, int max_);
int getRandInt(int max_ = RAND_MAX);
std::wstring my_getCurrentDirectory(); // win32

// Serialisation
void writeInt(std::ofstream& f, int v); // worst implementation, problem: alignment; different cpu archi i.e. little/big endian?
void writeString(std::ofstream& f, const char* str);

void readString(std::ifstream& f, char* buff, int nChar);
void readInt(std::ifstream& f, int& v);