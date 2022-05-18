//----------------------------------------
//　メインの処理
//　Author：橋野幹生
//----------------------------------------
#include "main.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "score.h"
#include "ranking.h"
#include "resultscore.h"
#include "mouse.h"
#include "rule.h"

//マクロ定義
#define CLASS_NAME			"WindowsClass"		//ウィンドウクラスの名前
#define WINDOW_NAME			"VS.GODZZILA"		//ウィンドウの名前(キャプションに表示)

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Updata(void);
void Draw(void);
void DrawFPS(void);

//グローバル変数宣言
LPDIRECT3D9 g_pD3D = NULL;						//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//Direct3Dデバイスへのポインタ
LPD3DXFONT g_pFont = NULL;
int g_nCntFPS = 0;
bool g_Meshfield = false;
MODE g_mode = MODE_TITLE;

//----------------------------------------
//　メイン関数
//----------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),							//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,									//ウィンドウのスタイル
		WindowProc,									//ウィンドウプロシージャ
		0,											//0にする（通常は使用しない）
		0,
		hInstance,									//インスタンスハンドル
		LoadIcon(NULL, IDI_APPLICATION),			//タスクバーのアイコン
		LoadCursor(NULL, IDC_ARROW),				//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),					//クライアント領域の背景色
		NULL,										//メニューバー
		CLASS_NAME,									//ウィンドウクラスの名前
		LoadIcon(NULL, IDI_APPLICATION)				//ファイルのアイコン
	};

	MSG msg;		//メッセージを格納する変数
	HWND hWnd;		//ウィンドウハンドル(識別子)
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };	//画面サイズの構造体
	
	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,		//拡張ウィンドウスタイル
		CLASS_NAME,					//ウィンドウクラスの名前
		WINDOW_NAME,				//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,		//ウィンドウスタイル
		CW_USEDEFAULT,				//ウィンドウの左上Ｘ座標
		CW_USEDEFAULT,			//ウィンドウの左上Ｙ座標
		(rect.right - rect.left),	//ウィンドウの幅
		(rect.bottom - rect.top),	//ウィンドウの高さ
		NULL,						//親ウィンドウのハンドル
		NULL,						//メニューハンドルまたは、子ウィンドウID
		hInstance,					//インスタンスハンドル
		NULL);						//ウィンドウ作成データ

	DWORD dwCurrentTime;				//現在時刻
	DWORD dwExecLastTime;				//最後に処理した時刻
	DWORD dwFrameCount;					//フレームカウント
	DWORD dwFPSLastTime;				//最後に計測した時刻

	//初期化設定
	if (FAILED(Init(hInstance, hWnd, true)))	// falseで全画面表示
	{//初期化が失敗した場合
		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);

	dwCurrentTime = 0;					//初期化する
	dwExecLastTime = timeGetTime();		//現在時刻を取得(保存)
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);			//ウィンドウの表示状態を設定
	UpdateWindow(hWnd);					//クライアント領域を更新

	//メッセージをループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windowの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);		//仮想キーメッセージ文字メッセージへ変換
				DispatchMessage(&msg);		//ウィンドウプロシージャメッセージを創出
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();	//現在時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
			 //FPSを計測
				g_nCntFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;			//FPSを計測した時刻を保存
				dwFrameCount = 0;						//フレームカウントクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;

				//更新処理
				Updata();

				//描画処理
				Draw();

				dwFrameCount++;				//フレームカウント加算
			}
		}
	}

	//終了処理
	Uninit();

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//----------------------------------------
//　ウィンドウプロシージャ
//----------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;		//返り値を格納
	//HDC hDC;		//デバイスコンテキスト(GDIオブジェクト)のハンドル

	switch (uMsg)
	{
	case WM_DESTROY:	//ウィンドウ破棄のメッセージ
		//WM_QUITメッセージを送る
		PostQuitMessage(0);

		break;

	case WM_KEYDOWN:	//キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:		//【ESC】キーが押されたとき
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{
				//ウィンドウを破棄する(WM_DESTROY メッセージを送る)
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	
	case WM_CLOSE:		//閉じるボタン押下のメッセージ
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{
			//ウィンドウを破棄する(WM_DESTROY メッセージを送る)
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;	//０を返さないと終了する
		}

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//既定の処理を繰り返す
}

//----------------------------------------
//  初期化処理
//----------------------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;				//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;		//プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));			//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;		//ゲーム画面のサイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		//ゲーム画面のサイズ(幅)
	d3dpp.BackBufferFormat = d3ddm.Format;		//バックバッファの形式
	d3dpp.BackBufferCount = 1;					//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;		//デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;					//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//インターバル

	//Direct3Dデバイスの生成(描画処理と頂点処理をハードウェアで行う)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3Dデバイスの生成(描画処理をハードウェア、頂点処理はCPUで行う)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3Dデバイスの生成(描画処理と頂点処理をCPUで行う)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//カリングモードを決めている	(カリングについての設定, どのモードにするか)だと？認識
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//α値(透明度)についての設定
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//αを乗算
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//αを反転したものを乗算

	
	g_pD3DDevice->Clear(
		0,
		nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f,
		0);

	//カメラから見て、(Zバッファ値が小さい)部分を上書き。(TRUEの時)
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);

	// Zバッファの値に関わらず、必ず上書きする。

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//デバック表示用フォントの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	InitMouse(hInstance, hWnd);

	InitMouse(hWnd);

	//ランキングの初期化
	ResetRanking();

	//サウンドの初期化
	InitSound(hWnd);

	//フェードの設定
	InitFade(g_mode);

	return S_OK;
}

//----------------------------------------
//  終了処理
//----------------------------------------
void Uninit(void)
{
	//タイトル画面の終了処理
	UninitTitle();

	//タイトル画面の終了処理
	UninitMouse();

	//ゲーム画面の終了処理
	UninitGame();

	//リザルト画面の終了処理
	UninitResult();

	//スコアの終了処理
	UninitScore();

	//スコアの終了処理
	UninitResultScore();

	//キーボードの終了処理
	UninitKeyboard();

	//サウンドの終了設定
	UninitSound();

	//フェードの終了処理
	UninitFade();

	//キーボードの終了処理
	UninitKeyboard();

	//マウスの終了処理
	UninitInputMouse();

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	//デバック表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//----------------------------------------
//  更新処理
//----------------------------------------
void Updata(void)
{
	//ワイヤーフレームについて
	if (GetKeyboardTrigger(DIK_F2) == true)
	{
		g_Meshfield = g_Meshfield ? false : true;
	}

	if (g_Meshfield == true)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else if (g_Meshfield != true)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	g_pD3DDevice->Clear(
		0,
		nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f,
		0);

	//キーボードの更新処理
	UpdateKeyboard();

	//マウスの更新処理
	UpdateInputMouse();

	//マウスの更新処理
	if (g_mode != MODE_GAME)
	{
		UpdateMouse();
	}

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;

	case MODE_RULE:
		UpdateRule();
		break;

	case MODE_GAME:
		UpdateGame();
		break;

	case MODE_RANKING:
		UpdateRanking();
		break;

	case MODE_RESULT:
		UpdateScore();
		UpdateResultScore();
		UpdateResult();
		break;
	}

	//フェードの更新処理
	UpdateFade();
}

//----------------------------------------
//  描画処理
//----------------------------------------
void Draw(void)
{
	//画面クリア
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合
		switch (g_mode)
		{
		case MODE_TITLE:	//タイトル画面
			DrawTitle();
			break;

		case MODE_RULE:		//ルール画面
			DrawRule();
			break;

		case MODE_GAME:		//ゲーム画面
			DrawGame();
			break;

		case MODE_RESULT:	//リザルト画面
			DrawResult();
			DrawScore();
			DrawResultScore();
			break;

		case MODE_RANKING:	//ランキング画面
			DrawRanking();
			break;
		}

		//フェードの描画処理
		DrawFade();

		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//----------------------------------------
//	デバイスの取得
//----------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//----------------------------------------
//	モード選択
//----------------------------------------
void SetMode(MODE mode)
{
	//現在の画面(モード)の終了処理
	switch (g_mode)
	{
	case MODE_TITLE:	//タイトル画面
		UninitTitle();
		break;

	case MODE_RULE:		//ルール画面
		UninitRule();
		break;

	case MODE_GAME:		//ゲーム画面
		UninitGame();
		break;

	case MODE_RESULT:	//リザルト画面
		UninitScore();
		UninitResultScore();
		UninitResult();
		break;

	case MODE_RANKING:	//ランキング画面
		UninitRanking();
		break;
	}

	//新しい画面(モード)の初期化処理
	switch (mode)
	{
	case MODE_TITLE:	//タイトル画面
		InitTitle();
		break;

	case MODE_RULE:		//ルール画面
		InitRule();
		break;

	case MODE_GAME:		//ゲーム画面
		InitGame();
		break;

	case MODE_RESULT:	//リザルト画面
		InitScore();
		InitResultScore();
		InitResult();
		break;

	case MODE_RANKING:	//ランキング画面
		InitRanking();
		break;
	}

	g_mode = mode;
}

//----------------------------------------
//	モードの情報
//----------------------------------------
MODE GetMode(void)
{
	return g_mode;
}

//----------------------------------------
//	FPSの表示
//----------------------------------------
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	wsprintf(&aStr[0], "FPS:%d\n", g_nCntFPS);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}
