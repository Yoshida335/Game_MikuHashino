//----------------------------------------
//　入力情報
//　Author：橋野幹生
//----------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

//キー種類(マウス)
typedef enum
{
	MOUSE_INPUT_LEFT,			//マウス左ボタン
	MOUSE_INPUT_RIGHT,			//マウス右ボタン
	MOUSE_INPUT_MIDDLE,			//マウス中央ボタン
	MOUSE_INPUT_4,				//マウスボタン4
	MOUSE_INPUT_5,				//マウスボタン5
	MOUSE_INPUT_6,				//マウスボタン6
	MOUSE_INPUT_7,				//マウスボタン7
	MOUSE_INPUT_8,				//マウスボタン8
}MOUSE;

#include "main.h"

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//キーボードの初期化
void UninitKeyboard(void);				//キーボードの終了
void UpdateKeyboard(void);				//キーボードの更新
bool GetKeyboardPress(int nKey);		//キーボードのプレス情報
bool GetKeyboardTrigger(int nKey);		//キーボードのトリガー情報

HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);		//マウスの初期化
void UninitInputMouse(void);		//マウスの終了処理
void UpdateInputMouse(void);		//マウスの更新処理
bool GetMousePress(MOUSE mouse);	//マウスのプレス情報
bool GetMouseTrigger(MOUSE mouse);	//マウスのトリガー情報

#endif