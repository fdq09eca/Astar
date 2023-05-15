#pragma once
#include <vector>
#include <memory>
#include "AppObject.h"
#include "Menu.h"
#include "Maze.h"
#include "MazeBuilder.h"
#include "AgentAstar.h"


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
	AgentAstar agent;
	
	

	
	std::vector<std::unique_ptr<AppObject>> objList;
	std::unique_ptr<AppObject> tmpObj;
	AppObject* captureObj = nullptr;
	

	
	App() = default;
	
	static App* Instance() { return _instance; }
	
	~App() { destroy(); }

	void init();
	void destroy();
	
	void initTimer(int fps = 10);
	void initMenu(); 
	void update() { 
		/*agent.update();*/
		
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