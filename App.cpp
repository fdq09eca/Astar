#include "App.h"
#define APP_TIMER  512
App* App::_instance = nullptr;

void App::destroy()
{
	if (captureObj) { captureObj = nullptr; }
	DeleteObject(dashRedPen);
	DeleteObject(solidBlackPen);
	DeleteObject(solidRedBrush);
	if (APP_TIMER) KillTimer(_hWnd, APP_TIMER);
}

void App::initTimer(int fps) {
	assert(_hWnd != NULL);
	SetTimer(_hWnd, APP_TIMER, (int) (1000 / fps), (TIMERPROC) NULL);     
}

void App::init() {
	assert(_instance == nullptr);
	_instance = this;
	
	// create pen and brush..
	solidBlackPen = ::CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // black solid pen
	
	dashRedPen = ::CreatePen(PS_DOT, 1, RGB(255, 0, 0)); // red dash pen
	solidRedPen = ::CreatePen(PS_SOLID, 5, RGB(255, 0, 0)); // red solid pen
	solidRedBrush = ::CreateSolidBrush(RGB(255, 0, 0)); // red solid brush

	// try
	//auto m = std::make_unique<Maze>();
	//m->init(10, 10);
	//objList.emplace_back(std::move(m));

	maze.init(10, 10);

}

void App::setHwnd(HWND hWnd_) {
	_hWnd = hWnd_;
	backBuffer.create(_hWnd);
}

void App::draw(HDC hdc_)  {
	backBuffer.clear();
	
	maze.draw(backBuffer.dc());
	
	for (const auto& p : objList) {
		p->draw(backBuffer.dc());
	}
	
	if (tmpObj) {
		tmpObj->draw(backBuffer.dc());
	}
	
	backBuffer.draw(hdc_);
}


void App::onMouseEvent(const MouseEvent& ev) {

	if (captureObj) {
		captureObj->onMouseEvent(ev);
		return;
	}


	for (auto& p : objList) {
		if (p->onMouseEvent(ev)) {
			return;
		}
	}

}


void App::_onWin32MouseEvent(UINT msg, WPARAM wp, LPARAM lp) {

	MouseEvent ev;
	ev.pos = POINT{ GET_X_LPARAM(lp) , GET_Y_LPARAM(lp) };

	switch (msg)
	{
		using B = MouseButton;
		using T = MouseEventType;

	case WM_LBUTTONDOWN: { ev.eventType = T::Down;  ev.button = B::Left;   _mouseButtonState |=  B::Left;	} break;
	case WM_MBUTTONDOWN: { ev.eventType = T::Down;  ev.button = B::Middle; _mouseButtonState |=  B::Middle;	} break;
	case WM_RBUTTONDOWN: { ev.eventType = T::Down;  ev.button = B::Right;  _mouseButtonState |=  B::Right;	} break;
	
	case WM_LBUTTONUP:	 { ev.eventType = T::Up;	ev.button = B::Left;   _mouseButtonState &= ~B::Left;	} break;
	case WM_MBUTTONUP:	 { ev.eventType = T::Up;	ev.button = B::Middle; _mouseButtonState &= ~B::Middle;	} break;
	case WM_RBUTTONUP:	 { ev.eventType = T::Up;	ev.button = B::Right;  _mouseButtonState &= ~B::Right;	} break;

	case WM_MOUSEMOVE: { ev.eventType = T::Move; } break;
	
	default: { assert(false); return; } break;
	}
	//ev.btnState // do it later


	onMouseEvent(ev);
	InvalidateRect(_hWnd, nullptr, false);

}

void App::setCaptureObject(AppObject* obj) {
	assert(captureObj == nullptr);
	captureObj = obj;
	printf("[set] captureObj [%s id: %d]\n", obj->type_cstr(), obj->id);
}

void App::clearCaptureObject() {
	assert(captureObj != nullptr);
	printf("[clear] captureObj [%s id: %d]\n", captureObj->type_cstr(), captureObj->id);
	captureObj = nullptr;
}


void App::initMenu() {
	assert(_hWnd);
	Menu fileDropDownMenu;
	fileDropDownMenu.addItem(L"Open", -1, MCMD_FILE_OPEN);
	fileDropDownMenu.addItem(L"Save", -1, MCMD_FILE_SAVE);
	fileDropDownMenu.addItem(L"Exit", -1, MCMD_FILE_EXIT);
	menu.addItem(L"File", -1, MCMD_FILE, &fileDropDownMenu);
	menu.addItem(L"About", -1, MCMD_FILE_ABOUT);
	SetMenu(_hWnd, menu.hMenu);
	fileDropDownMenu.hMenu = nullptr;
}