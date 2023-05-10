#pragma once
#include "Util.h"

enum class AppObjectType {
	NA = 0,
	AppObject = 1,
	Maze = 1,
};

class AppObject : NonCopyable {

public:
	using Type = AppObjectType;

protected:
	Type _type = Type::AppObject;

public:
	int id = 0;
	
	AppObject() { 
		static int next_id = 0;
		id = next_id;
		next_id++;
	}
	
	virtual ~AppObject() { }
	virtual void draw(HDC hdc_) const { }
	virtual bool onMouseEvent(const MouseEvent& e) { return false; }

	virtual void save(std::ofstream&) { }
	virtual void load(std::ifstream&) { }
	Type type() const { return _type; }
	
	const char* type_cstr() const;
	static const char* type_cstr(Type t) ;

};


