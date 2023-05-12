#pragma once
#include <vector>
#include <memory>
#include "AppObject.h"
#include "Menu.h"
#include "Maze.h"
#include "Agent.h"


class App : NonCopyable
{
private:
	static App* _instance;
	HWND _hWnd = NULL;
	BackBuffer backBuffer;
	MouseButton _mouseButtonState = MouseButton::NA;

public:
	HPEN dashRedPen = NULL;
	HPEN solidRedPen = NULL;
	HPEN solidBlackPen = NULL;
	HBRUSH solidRedBrush = NULL;
	Menu menu;
	Maze maze;
	Agent agent;

	
	std::vector<std::unique_ptr<AppObject>> objList;
	std::unique_ptr<AppObject> tmpObj;
	AppObject* captureObj = nullptr;
	

	
	App() = default;
	
	static App* Instance() { return _instance; }
	
	~App() { destroy(); }

	void init();
	void destroy();

	/*Maze& maze_() {
		for (auto& obj : objList) {
			if (obj->type() == AppObjectType::Maze) {
				auto m = (Maze) *obj ;
				return m;
			}
		}
	}*/
	
	void initTimer(int fps = 10);
	void initMenu(); 
	void update() { 
		
	};



	void setHwnd(HWND hWnd_);

	void draw(HDC hdc_) ;

	void onMouseEvent(const MouseEvent& ev);

	void _onWin32MouseEvent(UINT msg, WPARAM wp, LPARAM lp);

	void setCaptureObject(AppObject* obj);
	
	void clearCaptureObject();

	MouseButton mouseButtonState() const { return _mouseButtonState; }

	inline void save(const wchar_t* fpath) const { };
	inline void load(const wchar_t* fpath) { };
	
};

//extern App* g_internal_app_ptr;
//inline App* g_app() { return g_internal_app_ptr; };
//inline void g_set_app(App* p) { g_internal_app_ptr = p; };