//----------------------------------------
//　キーボードの入力
//　Author：橋野幹生
//----------------------------------------
#include "input.h"

//マクロ定義
#define NUM_KEY_MAX		(256)	//キーの最大数
#define MOUSE_KEY_MAX	(8)		//キーの最大数（マウス）

//----------------------------------------
//	グローバル変数宣言
//----------------------------------------
//キーボード
LPDIRECTINPUT8 g_pInput = NULL;					//DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		//入力デバイス(キーボード)へのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];					//キーボードのプレス情報
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];			//キーボードのトリガー情報
//マウス
LPDIRECTINPUT8 g_pMouseInput = NULL;			//Directinutオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL;		//入力でパスへのポインタ
DIMOUSESTATE2 g_aKeyStateMouse;					//マウスのプレス処理
DIMOUSESTATE2 g_aKeyStatetriggerMouse;			//マウスのトリガー処理
POINT g_MousePos;								//マウスのカーソル用
HWND g_hMouseWnd;								//ウィンドウハンドル

//----------------------------------------
//　キーボードの初期化処理
//----------------------------------------
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス(キーボード)の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard,
		&g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//----------------------------------------
//　キーボードの終了処理
//----------------------------------------
void UninitKeyboard(void)
{
	//入力デバイスの破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//----------------------------------------
//　キーボードの更新処理
//----------------------------------------
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];		//キーボードの入力情報

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//キーボードのトリガー情報を保存
			g_aKeyStateTrigger[nCntKey] = (aKeyState[nCntKey] ^ g_aKeyState[nCntKey]) & aKeyState[nCntKey];
		
			//キーボードのプレス情報を保存
			g_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();		//キーボードへのアクセス権を獲得
	}
}

//----------------------------------------
//　キーボードのプレス情報を取得
//----------------------------------------
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}

//----------------------------------------
//　キーボードのトリガー情報を取得
//----------------------------------------
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//----------------------------------------
//	マウスの初期化
//----------------------------------------
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_pMouseInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス（マウス）の生成
	if (FAILED(g_pMouseInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//ウィンドウハンドルの保管
	g_hMouseWnd = hWnd;

	//キーボードへのアクセス権を獲得
	g_pDevMouse->Acquire();

	return S_OK;
}

//----------------------------------------
//	マウスの終了処理
//----------------------------------------
void UninitInputMouse(void)
{
	if (g_pDevMouse != NULL)
	{
		g_pDevMouse->Unacquire();
		g_pDevMouse = NULL;
	}
}

//----------------------------------------
//	マウスの更新処理
//----------------------------------------
void UpdateInputMouse(void)
{
	DIMOUSESTATE2 aKeyState;	//マウスの入力情報

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(aKeyState), &aKeyState)))
	{

		for (int nCntKey = 0; nCntKey < MOUSE_KEY_MAX; nCntKey++)
		{
			g_aKeyStatetriggerMouse.rgbButtons[nCntKey]
				= (g_aKeyStateMouse.rgbButtons[nCntKey]
					^ aKeyState.rgbButtons[nCntKey])
				& aKeyState.rgbButtons[nCntKey]; //キーボードのトリガー情報を保存
		}

		g_aKeyStateMouse = aKeyState;		//マウスのプレス情報を保存

	}
	else
	{
		g_pDevMouse->Acquire();			//キーボードへのアクセス権を獲得
	}
}

//----------------------------------------
//	マウスのプレス処理
//----------------------------------------
bool GetMousePress(MOUSE mouse)
{
	return (g_aKeyStateMouse.rgbButtons[mouse] & 0x80) ? true : false;
}

//----------------------------------------
//	マウスのトリガー処理
//----------------------------------------
bool GetMouseTrigger(MOUSE mouse)
{
	return (g_aKeyStatetriggerMouse.rgbButtons[mouse] & 0x80) ? true : false;
}
