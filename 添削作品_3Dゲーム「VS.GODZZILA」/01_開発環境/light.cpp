//----------------------------------------
//　ライトの処理
//　Author：橋野幹生
//----------------------------------------
#include "light.h"
#include "input.h"

//グローバル変数宣言
D3DLIGHT9 g_alight[MAX_LIGHT];

//---------------------------------------------------
//	ライトの初期化
//---------------------------------------------------
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 verDir;		//ライトの方向ベクトル

	//ライトをクリアする
	ZeroMemory(&g_alight[0], sizeof(g_alight));

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//ライトの種類を設定
		g_alight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;					//平行光源

		//ライトの拡散光を設定
		g_alight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//ライトの色
	}

	//ライト①の方向を設定--------------------------
	verDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);

	//正規化する
	D3DXVec3Normalize(&verDir, &verDir);
	g_alight[0].Direction = verDir;

	//ライトを設定する
	pDevice->SetLight(0, &g_alight[0]);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);

	//ライト②の方向を設定--------------------------
	verDir = D3DXVECTOR3(-1.0f, 1.2f, 0.4f);

	//正規化する
	D3DXVec3Normalize(&verDir, &verDir);
	g_alight[1].Direction = verDir;

	//ライトを設定する
	pDevice->SetLight(1, &g_alight[1]);

	//ライトを有効にする
	pDevice->LightEnable(1, TRUE);

	//ライト③の方向を設定--------------------------
	verDir = D3DXVECTOR3(0.8f, -0.8f, 1.0f);

	//正規化する
	D3DXVec3Normalize(&verDir, &verDir);
	g_alight[2].Direction = verDir;

	//ライトを設定する
	pDevice->SetLight(2, &g_alight[2]);

	//ライトを有効にする
	pDevice->LightEnable(2, TRUE);
}

//---------------------------------------------------
//	ライトの終了処理
//---------------------------------------------------
void UninitLight(void)
{
	
}

//---------------------------------------------------
//	ライトの更新処理
//---------------------------------------------------
void UpdateLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ライト①の色が変わる
	if (GetKeyboardPress(DIK_L) == true)
	{//↑キーが押された
		if (g_alight[0].Diffuse.r <= 1.0f)
		{
			g_alight[0].Diffuse.r += 0.01f;
		}
		else
		{
			g_alight[0].Diffuse.r = 0.0f;
		}
	}
	else if (GetKeyboardPress(DIK_P) == true)
	{//↑キーが押された
		if (g_alight[0].Diffuse.r >= 0.0f)
		{
			g_alight[0].Diffuse.r -= 0.01f;
		}
		else
		{
			g_alight[0].Diffuse.r = 1.0f;
		}
	}
	//ライトを設定する
	pDevice->SetLight(0, &g_alight[0]);
}

