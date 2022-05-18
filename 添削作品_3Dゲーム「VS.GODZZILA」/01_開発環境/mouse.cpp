//----------------------------------------
//　マウスの処理
//　Author：橋野幹生
//----------------------------------------
#include "mouse.h"

//グローバル変数宣言
POINT g_mouse = {};
POINT g_mouseCenter = {};
HWND g_hWnd;

//---------------------------------------------------
//	マウスの初期化
//---------------------------------------------------
void InitMouse(HWND hWnd)
{
	ShowCursor(false);	// trueでカーソル表示、falseで非表示

	g_hWnd = hWnd;

	RECT rect;

	GetWindowRect(g_hWnd, &rect);

	SetCursorPos(rect.left + SCREEN_WIDTH / 2, rect.top + SCREEN_HEIGHT / 2);
}

//---------------------------------------------------
//	マウスの終了処理
//---------------------------------------------------
void UninitMouse(void)
{

}

//---------------------------------------------------
//	マウスの更新処理
//---------------------------------------------------
void UpdateMouse(void)
{
	RECT rect;

	GetWindowRect(g_hWnd, &rect);

	SetCursorPos(rect.left + SCREEN_WIDTH / 2, rect.top + SCREEN_HEIGHT / 2);
}

//---------------------------------------------------
//	マウスの描画処理
//---------------------------------------------------
void DrawMouse(void)
{

}
