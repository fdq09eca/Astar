#include "AppObject.h"

const char* AppObject::type_cstr() const {
	return type_cstr(_type);
}

const char* AppObject::type_cstr(Type t)
{
	switch (t)
	{
		case Type::NA: { return "NA"; }
		case Type::AppObject: { return "AppObject"; }
		default: break;
	}
	assert(false);
	return "[ERR] Unknown Type";
}