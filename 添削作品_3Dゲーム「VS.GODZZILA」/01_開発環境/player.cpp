//----------------------------------------
//　プレイヤーの処理
//　Author：橋野幹生
//----------------------------------------
#include <stdio.h>
#include <string.h>
#include "player.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "wall.h"
#include "bullet.h"
#include "effect.h"
#include "bill.h"
#include "fade.h"
#include "collision.h"
#include "enemy.h"
#include "time.h"
#include "scoregage.h"
#include "sound.h"
#include "map.h"

//マクロ定義
#define MOTION_PAS			("data\\motion.txt")	//プレイヤーのモーションテキスト
#define PLAYER_JUMP			(5.0f)	//プレイヤーのジャンプ量
#define PLAYER_INERTIA		(0.1f)	//プレイヤーの慣性の量
#define PLAYER_LIFE			(100)	//プレイヤーの体力
#define PLAYER_SHADOW		(50.0f)	//プレイヤーの影の大きさ

//パーツセットの構造体
typedef struct
{
	int nIndex;			//自分の番号
	int nParent;		//親
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//角度
}PARTSSET;

//Keyの構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//角度
}Key;

//KeySetの構造体
typedef struct
{
	int nFrame;		//プレーム数
	Key Key[20];	//キー数
}KeySet;

//モーションセットの構造体
typedef struct
{
	int nLoop;				//ループするかどうか
	int nNumKey;			//最大キー数
	KeySet KeySet[20];		//設定してあるキー
}MOTIONSET;

//グローバル変数宣言
LPD3DXMESH g_pMeshPlayer = NULL;			//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatPlayer = NULL;		//マテリアル情報へのポインタ
DWORD g_nNumMatPlayer = 0;					//マテリアル情報の数
Player g_Player;							//プレイヤーの変数宣言
int nNowFrame = 0;		//現在のフレーム数
int nCntFrame = 0;		//総再生フレーム数
int nNowKeySet = 0;					//現在再生中のKeySet番号
int nNextKeySet = nNowKeySet + 1;	//次に再生するKeySet番号
int g_nPlayMotion = 0;	//現在再生中のモーション番号
SetPlayer g_SetPlayer;
int g_nSelectMotion;	//モーション選択用
D3DXMATERIAL * g_pMat;	//マテリアルデータへのポインタ

//モデル、モーションを読み込むときに使うグローバル変数
int g_nNumParts;			//パーツ数
PARTSSET PartsSet[20];		//読み込んだパーツの情報を入れる変数
MOTIONSET MotionSet[10];	//読み込んだモーション情報を入れる変数
char cModelPas[20][256];	//モデルのパスを読み込む用
D3DXVECTOR3 MotionDiff[20];

//---------------------------------------------------
//	モデルをファイルから読み込み
//---------------------------------------------------
void LoadModel(void)
{
	FILE * pFile;

	char cData[256];	//文字を読み込む用
	int nData;			//整数を読み込む用

	int nCntParts;		//パーツ数保存用

	int nCntMotion = 0;		//モーション数をカウントする
	int nCntKey = 0;		//キー数をカウントする
	int nCntKeyParts = 0;	//キーパーツ数をカウントする

	pFile = fopen(MOTION_PAS, "r");

	// strncmp : 指定した文字数比較する
	// sscanf : 指定した所を変数に入れる
	// fgetc : 一行を読み込み

	if (pFile != NULL)
	{//ファイルを開けたら
		do
		{//"SCRIPT"と一致するまで回す
			fscanf(pFile, "%s", &cData[0]);
		} while (strcmp(&cData[0], "SCRIPT") != 0);

		do
		{//"END_SCRIPT"と一致するまで回す
			fscanf(pFile, "%s", &cData[0]);

			//モデルのファイルパスを読み込む
			if (strcmp(&cData[0], "NUM_MODEL") == 0)
			{
				fscanf(pFile, "%s", &cData[0]);
				fscanf(pFile, "%d", &nCntParts);

				for (int i = 0, nCntModel = 0; i < nCntParts; i++, nCntModel++)
				{//モデルパーツ数分回す
					do
					{//"MODEL_FILENAME"と一致するまで回す
						fscanf(pFile, "%s", &cData[0]);
					} while (strcmp(&cData[0], "MODEL_FILENAME") != 0);

					if (strcmp(&cData[0], "MODEL_FILENAME") == 0)
					{
						fscanf(pFile, "%s", &cData[0]);		// "＝"飛ばし用
						fscanf(pFile, "%s", &cModelPas[nCntModel][0]);
					}
				}
			}

			//キャラクター情報を読み込む
			if (strcmp(&cData[0], "CHARACTERSET") == 0)
			{
				do
				{//"END_CHARACTERSET"と一致するまで回す
					fscanf(pFile, "%s", &cData[0]);

					if (strcmp(&cData[0], "NUM_PARTS") == 0)
					{
						fscanf(pFile, "%s", &cData[0]);
						fscanf(pFile, "%d", &nData);
						g_nNumParts = nData;	//パーツ数を保存

						for (int i = 0, nCntParts = 0; i < g_nNumParts; i++, nCntParts++)
						{
							do
							{//"PARTSSET"と一致するまで回す
								fscanf(pFile, "%s", &cData[0]);
							} while (strcmp(&cData[0], "PARTSSET") != 0);

							if (strcmp(&cData[0], "PARTSSET") == 0)
							{
								do
								{//"END_PARTSSET"と一致するまで回す
									fscanf(pFile, "%s", &cData[0]);

									if (strcmp(&cData[0], "INDEX") == 0)
									{
										fscanf(pFile, "%s", &cData[0]);
										fscanf(pFile, "%d", &PartsSet[nCntParts].nIndex);
									}
									if (strcmp(&cData[0], "PARENT") == 0)
									{
										fscanf(pFile, "%s", &cData[0]);
										fscanf(pFile, "%d", &PartsSet[nCntParts].nParent);
									}
									if (strcmp(&cData[0], "POS") == 0)
									{
										fscanf(pFile, "%s", &cData[0]);
										fscanf(pFile, "%f", &PartsSet[nCntParts].pos.x);
										fscanf(pFile, "%f", &PartsSet[nCntParts].pos.y);
										fscanf(pFile, "%f", &PartsSet[nCntParts].pos.z);
									}
									if (strcmp(&cData[0], "ROT") == 0)
									{
										fscanf(pFile, "%s", &cData[0]);
										fscanf(pFile, "%f", &PartsSet[nCntParts].rot.x);
										fscanf(pFile, "%f", &PartsSet[nCntParts].rot.y);
										fscanf(pFile, "%f", &PartsSet[nCntParts].rot.z);
									}
								} while (strcmp(&cData[0], "END_PARTSSET") != 0);
							}
						}
					}
				} while (strcmp(&cData[0], "END_CHARACTERSET") != 0);
			}

			//モーションの読み込み
			if (strcmp(&cData[0], "MOTIONSET") == 0)
			{
				do
				{//"END_MOTIONSET"と一致するまで回す
					fscanf(pFile, "%s", &cData[0]);

					if (strcmp(&cData[0], "LOOP") == 0)
					{// "LOOP"と一致したとき
						fscanf(pFile, "%s", &cData[0]);		// "="
						fscanf(pFile, "%d", &MotionSet[nCntMotion].nLoop);	//ループ
					}
					if (strcmp(&cData[0], "NUM_KEY") == 0)
					{// "NUM_KEY"と一致したとき
						fscanf(pFile, "%s", &cData[0]);		// "="
						fscanf(pFile, "%d", &MotionSet[nCntMotion].nNumKey);		//キー数
					}
					if (strcmp(&cData[0], "KEYSET") == 0)
					{// "KEYSET"と一致したとき
						do
						{//"END_KEYSET"と一致するまで回す
							fscanf(pFile, "%s", &cData[0]);

							if (strcmp(&cData[0], "FRAME") == 0)
							{// "FRAME"と一致したとき
								fscanf(pFile, "%s", &cData[0]);		// "="
								fscanf(pFile, "%d", &MotionSet[nCntMotion].KeySet[nCntKey].nFrame);		//フレーム数
							}
							if (strcmp(&cData[0], "KEY") == 0)
							{// "KEY"と一致したとき
								do
								{//"END_KEY"と一致するまで回す
									fscanf(pFile, "%s", &cData[0]);

									if (strcmp(&cData[0], "POS") == 0)
									{// "POS"と一致したとき
										fscanf(pFile, "%s", &cData[0]);		// "="
										fscanf(pFile, "%f", &MotionSet[nCntMotion].KeySet[nCntKey].Key[nCntKeyParts].pos.x);	// x座標
										fscanf(pFile, "%f", &MotionSet[nCntMotion].KeySet[nCntKey].Key[nCntKeyParts].pos.y);	// y座標
										fscanf(pFile, "%f", &MotionSet[nCntMotion].KeySet[nCntKey].Key[nCntKeyParts].pos.z);	// z座標
									}
									if (strcmp(&cData[0], "ROT") == 0)
									{// "ROT"と一致したとき
										fscanf(pFile, "%s", &cData[0]);		// "="
										fscanf(pFile, "%f", &MotionSet[nCntMotion].KeySet[nCntKey].Key[nCntKeyParts].rot.x);	// x軸
										fscanf(pFile, "%f", &MotionSet[nCntMotion].KeySet[nCntKey].Key[nCntKeyParts].rot.y);	// y軸
										fscanf(pFile, "%f", &MotionSet[nCntMotion].KeySet[nCntKey].Key[nCntKeyParts].rot.z);	// z軸
									}
								} while (strcmp(&cData[0], "END_KEY") != 0);

								nCntKeyParts++;	//キーパーツ数に+1する
							}
						} while (strcmp(&cData[0], "END_KEYSET") != 0);

						nCntKey++;	//キー数に+1する
						nCntKeyParts = 0;	//キーパーツ数のカウントを0にする
					}
				} while (strcmp(&cData[0], "END_MOTIONSET") != 0);

				nCntMotion++;	//モーション数に+1する
				nCntKey = 0;	//キー数のカウントを0にする
			}
		} while (strcmp(&cData[0], "END_SCRIPT") != 0);

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("\n***　ファイルが開けませんでした　***\n");
	}
}

//---------------------------------------------------
//	プレイヤーの初期化処理
//---------------------------------------------------
void InitPlayer(void)
{
	LoadModel();	//モデルのデータを読み込み

	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイス情報を取得

	//パーツの各値の初期化
	for (int nCntParts = 0; nCntParts < g_nNumParts; nCntParts++)
	{//	パーツ数分回す
		g_Player.aModel[nCntParts].pos = PartsSet[nCntParts].pos;	//位置
		g_Player.aModel[nCntParts].rot = PartsSet[nCntParts].rot;	//角度
		g_Player.aModel[nCntParts].nIdxModelParent = PartsSet[nCntParts].nParent;	//親パーツ設定
	}

	//プレイヤーの各値の初期化
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//現在の位置
	g_Player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前回の位置
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	g_Player.diff = 0.0f;								//差分計算用
	g_Player.rotDest = 0.0f;							//目的の角度
	g_Player.vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点の最小値を取得用
	g_Player.vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点の最大値を取得用
	g_Player.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//サイズ保存用
	g_Player.bIsJumping = false;	//ジャンプしているかどうか
	g_Player.nLife = PLAYER_LIFE;	//体力
	g_nSelectMotion = 1;			//モーション番号設定

	g_SetPlayer.pos = D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 50.0f, g_Player.pos.z);
	g_SetPlayer.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_SetPlayer.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//影を設定
	g_Player.IdxShadow = SetShadow(D3DXVECTOR3(g_Player.pos.x, 0.1f, g_Player.pos.z), g_Player.rot, PLAYER_SHADOW);

	//Ⅹファイルの読み込み
	for (int nCntParts = 0; nCntParts < g_nNumParts; nCntParts++)
	{
		D3DXLoadMeshFromX(&cModelPas[nCntParts][0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player.aModel[nCntParts].pBuffMat,
			NULL,
			&g_Player.aModel[nCntParts].nNumMat,
			&g_Player.aModel[nCntParts].pMesh);

		//マテリアルデータへのポインタを取得
		g_pMat = (D3DXMATERIAL*)g_Player.aModel[nCntParts].pBuffMat->GetBufferPointer();

		//テクスチャの読み込み
		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntParts].nNumMat; nCntMat++)
		{
			D3DXCreateTextureFromFile(
				pDevice,
				g_pMat[nCntMat].pTextureFilename,
				&g_Player.aModel[nCntParts].pTexturePlayer[nCntMat]);
		}
	}

	//プレイヤーの頂点の最小値、最大値設定
	g_Player.vtxMin = D3DXVECTOR3(-20.0f, 0.0f, -20.0f);
	g_Player.vtxMax = D3DXVECTOR3(20.0f, 110.0f, 20.0f);

	//プレイヤーのサイズ設定
	g_Player.size.x = g_Player.vtxMax.x - g_Player.vtxMin.x;
	g_Player.size.y = g_Player.vtxMax.y - g_Player.vtxMin.y;
	g_Player.size.z = g_Player.vtxMax.z - g_Player.vtxMin.z;

	//プレイヤーの体力を元にゲージを設定
	SetScoreGage(D3DXVECTOR3(650.0f, SCREEN_HEIGHT - (200.0f / 2.0f), 0.0f), g_Player.nLife);
}

//---------------------------------------------------
//	プレイヤーの終了処理
//---------------------------------------------------
void UninitPlayer(void)
{
	//プレイヤーのメッシュ破棄
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		//モデルのメッシュ破棄
		if (g_Player.aModel[nCntParts].pMesh != NULL)
		{
			g_Player.aModel[nCntParts].pMesh->Release();
			g_Player.aModel[nCntParts].pMesh = NULL;
		}

		//テクスチャ破棄
		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntParts].nNumMat; nCntMat++)
		{
			if (g_Player.aModel[nCntParts].pTexturePlayer[nCntMat] != NULL)
			{
				g_Player.aModel[nCntParts].pTexturePlayer[nCntMat]->Release();
				g_Player.aModel[nCntParts].pTexturePlayer[nCntMat] = NULL;
			}
		}
	}

	//プレイヤーのマテリアル破棄
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}

	//モデルのマテリアル破棄
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		if (g_Player.aModel[nCntParts].pBuffMat != NULL)
		{
			g_Player.aModel[nCntParts].pBuffMat->Release();
			g_Player.aModel[nCntParts].pBuffMat = NULL;
		}
	}
}

//---------------------------------------------------
//	プレイヤーの更新処理
//---------------------------------------------------
void UpdatePlayer(void)
{
	//重力
	g_Player.move.y -= 0.3f;

	//プレイヤーの現在の位置を保存
	g_Player.posOld = g_Player.pos;

	//パーツの現在の位置を保存
	g_SetPlayer.posOld = g_SetPlayer.pos;

	//パーツの現在の位置を保存
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		g_Player.aModel[nCntParts].posOld = g_Player.aModel[nCntParts].pos;
	}

	//プレイヤーの操作
	ControlPlayer();

	//パーツの移動
	g_SetPlayer.pos = D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 50.0f, g_Player.pos.z - g_Player.vtxMax.z - 20.0f);

	//重力を加算
	g_Player.pos.y += g_Player.move.y;

	//プレイヤーとモデルの当たり判定
	CollisionModel(&g_Player.pos, &g_Player.posOld, g_Player.size, &g_Player.move);

	//敵が攻撃してきた弾の当たり判定
	CollisionBullet(&g_Player.pos, &g_Player.posOld, g_Player.size);

	//ジャンプの可否
	g_Player.bIsJumping = !CollisionModel(&g_Player.pos, &g_Player.posOld, g_Player.size, &g_Player.move);

	if (g_Player.pos.y <= 0.0f)
	{//床にいるとき
		g_Player.pos.y = 0.0f;			//位置
		g_Player.move.y = 0.0f;			//移動量
		g_Player.bIsJumping = false;	//ジャンプしているかどうか
	}

	//移動範囲の設定
	if ((g_Player.pos.x + (g_Player.size.x / 2.0f)) >= (FIELD_SIZE / 2.0f))
	{//ｘ軸
		g_Player.pos.x = (FIELD_SIZE / 2.0f) - (g_Player.size.x / 2.0f);
	}
	else if ((g_Player.pos.x - (g_Player.size.x / 2.0f)) <= -(FIELD_SIZE / 2.0f))
	{
		g_Player.pos.x = -(FIELD_SIZE / 2.0f) + (g_Player.size.x / 2.0f);
	}
	if ((g_Player.pos.z + (g_Player.size.z / 2.0f)) >= (FIELD_SIZE / 2.0f))
	{//ｚ軸
		g_Player.pos.z = (FIELD_SIZE / 2.0f) - (g_Player.size.z / 2.0f);
	}
	else if ((g_Player.pos.z - (g_Player.size.z / 2.0f)) <= -(FIELD_SIZE / 2.0f))
	{
		g_Player.pos.z = -(FIELD_SIZE / 2.0f) + (g_Player.size.z / 2.0f);
	}

	if (g_Player.pos != g_Player.posOld)
	{//プレイヤーが移動している場合、エフェクトを付与
		SetEffect(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, g_Player.pos.z),	//位置
			g_Player.rot,						//角度
			D3DXCOLOR(0.0f, 0.5f, 0.5f, 1.0f),	//カラー
			40,									//寿命
			D3DXVECTOR3(3.0f, 3.0f, 0.0f));		//サイズ
	}

	//影の位置を更新
	SetPositionShadow(0, D3DXVECTOR3(g_Player.pos.x, 0.1f, g_Player.pos.z));

	MotionPlayer(g_nSelectMotion);		//モーション設定

	g_SetPlayer.rot = g_Player.rot;
	g_SetPlayer.pos.x = sinf(g_SetPlayer.rot.y) * -50.0f;
	g_SetPlayer.pos.z = cosf(g_SetPlayer.rot.y) * -50.0f;

	//歩いてる時のモーションの設定
	if (g_nSelectMotion != 0)
	{
		if ((g_Player.pos.x != g_Player.posOld.x || g_Player.pos.z != g_Player.posOld.z) && g_nSelectMotion != 2)
		{//プレイヤーが動いている時
			SetMotion(2);
		}
		else if (g_Player.pos == g_Player.posOld && g_nSelectMotion == 2)
		{
			SetMotion(1);
		}
	}
}

//---------------------------------------------------
//	プレイヤーの操作に関する処理
//---------------------------------------------------
void ControlPlayer(void)
{
	//プレイヤーの移動処理
	MovePlayer();

	//マウスの左ボタン、右ボタンを押したとき、
	if (GetMouseTrigger(MOUSE_INPUT_LEFT) || GetMouseTrigger(MOUSE_INPUT_RIGHT))
	{//攻撃したとき
		SetCollision(D3DXVECTOR3(g_Player.pos.x + g_SetPlayer.pos.x, g_SetPlayer.pos.y, g_Player.pos.z + g_SetPlayer.pos.z), D3DXVECTOR3(g_Player.posOld.x + g_SetPlayer.posOld.x, g_SetPlayer.posOld.y, g_Player.posOld.z + g_SetPlayer.posOld.z), g_SetPlayer.rot);
		SetMotion(0);
	}
}

//---------------------------------------------------
//	プレイヤーのモーション処理
//---------------------------------------------------
void MotionPlayer(int nPlayMotion)
{
	if (nNextKeySet >= MotionSet[nPlayMotion].nNumKey)
	{//キー数が終わったら
		if (MotionSet[nPlayMotion].nLoop != 1)
		{//ループしない設定なら、待機モーションを設定
			SetMotion(1);
		}
		return;
	}

	for (int i = 0; i < g_nNumParts; i++)
	{// パーツ数分回す
		//前回のキーとの角度の差を求める
		MotionDiff[i].x = (MotionSet[nPlayMotion].KeySet[nNextKeySet].Key[i].rot.x - MotionSet[nPlayMotion].KeySet[nNowKeySet].Key[i].rot.x) / MotionSet[nPlayMotion].KeySet[nNowKeySet].nFrame;
		MotionDiff[i].y = (MotionSet[nPlayMotion].KeySet[nNextKeySet].Key[i].rot.y - MotionSet[nPlayMotion].KeySet[nNowKeySet].Key[i].rot.y) / MotionSet[nPlayMotion].KeySet[nNowKeySet].nFrame;
		MotionDiff[i].z = (MotionSet[nPlayMotion].KeySet[nNextKeySet].Key[i].rot.z - MotionSet[nPlayMotion].KeySet[nNowKeySet].Key[i].rot.z) / MotionSet[nPlayMotion].KeySet[nNowKeySet].nFrame;
		//算出した差を計算
		g_Player.aModel[i].rot.x += MotionDiff[i].x;
		g_Player.aModel[i].rot.y += MotionDiff[i].y;
		g_Player.aModel[i].rot.z += MotionDiff[i].z;
	}

	if (nNowFrame >= MotionSet[nPlayMotion].KeySet[nNowKeySet].nFrame)
	{// Frame分回ったら
		nNowFrame = 0;		//フレーム数を0(初期値)に戻す
		nNowKeySet++;		//次のキーに進む
		nNextKeySet++;		//再生中のキーの次のキーに進む
	}

	if (MotionSet[nPlayMotion].nLoop == 1)
	{
		if (nNextKeySet >= MotionSet[nPlayMotion].nNumKey)
		{//次のキーセット数が最大キー数を超えていたら、0（最初のキー）にする
			nNextKeySet = 0;
		}
		if (nNowKeySet >= MotionSet[nPlayMotion].nNumKey)
		{//現在のキーが全部回ったら
			nNowKeySet = 0;	//最初のキーにする
			nNextKeySet = nNowKeySet + 1;	//最初のキーにする
		}
	}

	//フレーム数を1進める
	nNowFrame++;
	nCntFrame++;
}

//---------------------------------------------------
//	プレイヤーのモーション選択処理
//---------------------------------------------------
void SetMotion(int nSet)
{
	//モーション番号を代入
	g_nSelectMotion = nSet;

	for (int i = 0; i < g_nNumParts; i++)
	{// パーツ数分回す
		g_Player.aModel[i].rot.x = 0.0f;
		g_Player.aModel[i].rot.y = 0.0f;
		g_Player.aModel[i].rot.z = 0.0f;
	}

	nNowFrame = 0;		//フレーム数を0(初期値)に戻す
	nNowKeySet = 0;		//次のキーに進む
	nNextKeySet = nNowKeySet + 1;	//再生中のキーの次のキーに進む
}

//---------------------------------------------------
//	プレイヤーの移動処理
//---------------------------------------------------
void MovePlayer(void)
{
	CAMERA * pCamera = GetCamera();		//カメラの情報取得

	if (GetKeyboardPress(DIK_W))
	{//↑キーが押されたとき
		if (GetKeyboardPress(DIK_D))
		{//←キーと押されたとき(左斜め上方向)
			g_Player.pos.x += sinf(pCamera->rot.y + (D3DX_PI / 4)) * PLAYER_SPEED;	//プレイヤーの位置移動
			g_Player.pos.z += cosf(pCamera->rot.y + (D3DX_PI / 4)) * PLAYER_SPEED;
			//プレイヤーの目的の向きを設定
			g_Player.rotDest = pCamera->rot.y - (D3DX_PI / 4 * 3.0f);
		}
		else if (GetKeyboardPress(DIK_A))
		{//→キーと押されたとき(右斜め上方向)
			g_Player.pos.x += sinf(pCamera->rot.y - (D3DX_PI / 4)) * PLAYER_SPEED;	//プレイヤーの位置移動
			g_Player.pos.z += cosf(pCamera->rot.y - (D3DX_PI / 4)) * PLAYER_SPEED;
			//プレイヤーの目的の向きを設定
			g_Player.rotDest = pCamera->rot.y + (D3DX_PI / 4 * 3.0f);
		}
		else
		{//↑キーのみ(上方向へ移動)
			g_Player.pos.x += sinf(pCamera->rot.y) * PLAYER_SPEED;	//プレイヤーの位置移動
			g_Player.pos.z += cosf(pCamera->rot.y) * PLAYER_SPEED;
			//プレイヤーの目的の向きを設定
			g_Player.rotDest = pCamera->rot.y + D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_S))
	{//↓キーが押されたとき
		if (GetKeyboardPress(DIK_D))
		{//←キーと押されたとき(左斜め下方向)
			g_Player.pos.x += sinf(pCamera->rot.y + (D3DX_PI / 4 * 3.0f)) * PLAYER_SPEED;		//プレイヤーの位置移動
			g_Player.pos.z += cosf(pCamera->rot.y + (D3DX_PI / 4 * 3.0f)) * PLAYER_SPEED;
			//プレイヤーの目的の向きを設定
			g_Player.rotDest = pCamera->rot.y - (D3DX_PI / 4);
		}
		else if (GetKeyboardPress(DIK_A))
		{//→キーと押されたとき(右斜め下方向)
			g_Player.pos.x += sinf(pCamera->rot.y - (D3DX_PI / 4 * 3.0f)) * PLAYER_SPEED;		//プレイヤーの位置移動
			g_Player.pos.z += cosf(pCamera->rot.y - (D3DX_PI / 4 * 3.0f)) * PLAYER_SPEED;
			//プレイヤーの目的の向きを設定
			g_Player.rotDest = pCamera->rot.y + (D3DX_PI / 4);
		}
		else
		{//↓キーのみ(下方向へ移動)
			g_Player.pos.x += sinf(pCamera->rot.y + D3DX_PI) * PLAYER_SPEED;		//プレイヤーの位置移動
			g_Player.pos.z += cosf(pCamera->rot.y + D3DX_PI) * PLAYER_SPEED;
			//プレイヤーの目的の向きを設定
			g_Player.rotDest = pCamera->rot.y;
		}
	}
	else if (GetKeyboardPress(DIK_D))
	{//→キーが押されたとき(右方向へ移動)
		g_Player.pos.x += sinf(pCamera->rot.y + (D3DX_PI / 2)) * PLAYER_SPEED;	//プレイヤーの位置移動
		g_Player.pos.z += cosf(pCamera->rot.y + (D3DX_PI / 2)) * PLAYER_SPEED;
		//プレイヤーの目的の向きを設定
		g_Player.rotDest = pCamera->rot.y - (D3DX_PI / 2);
	}
	else if (GetKeyboardPress(DIK_A))
	{//←キーが押されたとき(左方向へ移動)
		g_Player.pos.x += sinf(pCamera->rot.y - (D3DX_PI / 2)) * PLAYER_SPEED;	//プレイヤーの位置移動
		g_Player.pos.z += cosf(pCamera->rot.y - (D3DX_PI / 2)) * PLAYER_SPEED;
		//プレイヤーの目的の向きを設定
		g_Player.rotDest = pCamera->rot.y + (D3DX_PI / 2);
	}

	//ジャンプ
	if (GetKeyboardTrigger(DIK_SPACE) && !g_Player.bIsJumping)
	{//エンターキーが押された
		g_Player.move.y += PLAYER_JUMP;
	}

	//角度の正規化
	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y -= D3DX_PI * 2;
	}
	else if (g_Player.rot.y < -D3DX_PI)
	{
		g_Player.rot.y += D3DX_PI * 2;
	}

	//差分の計算
	g_Player.diff = (g_Player.rotDest - g_Player.rot.y);

	//差分の正規化
	if (g_Player.diff > D3DX_PI)
	{
		g_Player.diff -= D3DX_PI * 2;
	}
	else if (g_Player.diff < -D3DX_PI)
	{
		g_Player.diff += D3DX_PI * 2;
	}

	//プレイヤーの移動慣性
	g_Player.rot.y += g_Player.diff * PLAYER_INERTIA;
}

//---------------------------------------------------
//	プレイヤーの描画処理
//---------------------------------------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld,
		&g_Player.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		D3DXMATRIX mtxRotChild, mtxTransChild;	//計算用マトリックス

		D3DXMatrixIdentity(&g_Player.aModel[nCntParts].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRotChild,
			g_Player.aModel[nCntParts].rot.y, g_Player.aModel[nCntParts].rot.x, g_Player.aModel[nCntParts].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntParts].mtxWorld,
			&g_Player.aModel[nCntParts].mtxWorld, &mtxRotChild);

		//位置を反映
		D3DXMatrixTranslation(&mtxTransChild, g_Player.aModel[nCntParts].pos.x, g_Player.aModel[nCntParts].pos.y, g_Player.aModel[nCntParts].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntParts].mtxWorld, &g_Player.aModel[nCntParts].mtxWorld, &mtxTransChild);

		D3DXMATRIX mtxParent;	//親のマトリクス代入用

		if (g_Player.aModel[nCntParts].nIdxModelParent == -1)
		{
			//プレイヤーのマトリクス代入
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			//自分の親モデルのマトリクス代入
			mtxParent = g_Player.aModel[g_Player.aModel[nCntParts].nIdxModelParent].mtxWorld;
		}

		//自分の親モデルマトリクスとの掛算（自分のマトリクス * 親のマトリクス = 自分のワールドマトリクス）
		D3DXMatrixMultiply(&g_Player.aModel[nCntParts].mtxWorld,
			&g_Player.aModel[nCntParts].mtxWorld,		//自分のマトリクス
			&mtxParent);								//親のマトリクス

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntParts].mtxWorld);

		//現在のマテリアル保持
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得
		g_pMat = (D3DXMATERIAL*)g_Player.aModel[nCntParts].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntParts].nNumMat; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&g_pMat[nCntMat].MatD3D);

			//テクスチャ設定
			pDevice->SetTexture(0, g_Player.aModel[nCntParts].pTexturePlayer[nCntMat]);

			//Xファイルの描画
			g_Player.aModel[nCntParts].pMesh->DrawSubset(nCntMat);

			//テクスチャの設定
			pDevice->SetTexture(0, g_Player.aModel[nCntParts].pTexturePlayer[nCntMat]);
		}

		//保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//---------------------------------------------------
//	プレイヤーの情報
//---------------------------------------------------
Player * GetPlayer(void)
{//プレイヤーの情報を送る
	return &g_Player;
}

//---------------------------------------------------
//	ダメージ判定処理
//---------------------------------------------------
void HitModel(int nDamage)
{
	//体力を減らす
	g_Player.nLife -= nDamage;

	HitScoreGage(0, nDamage);

	//サウンドの再生
	PlaySound(SOUND_LABEL_SE_K);

	//タイムの情報を入手
	int * pTime = GetTime();

	if (g_Player.nLife <= 0)
	{//体力が０以下になったら
		*pTime = 0;
	}
}

//---------------------------------------------------
//	プレイヤーの当たり判定
//---------------------------------------------------
bool CollisionPlayer(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size)
{
	bool bAttack = false;

	for (int nCntModel = 0; nCntModel < MAX_ENEMY; nCntModel++)
	{//最大モデル数分確認
		if (pos->z - (size.z / 2) < g_Player.pos.z + g_Player.vtxMax.z &&
			pos->z + (size.z / 2) > g_Player.pos.z + g_Player.vtxMin.z)
		{// *posのz座標がモデルに重なっている時
			if (posOld->x + (size.x / 2) <= g_Player.pos.x + g_Player.vtxMin.x &&
				pos->x + (size.x / 2) >= g_Player.pos.x + g_Player.vtxMin.x)
			{//左側からモデルにめり込んだ時
			 //*pos.xにモデルのpos.x(左側)を設定
				pos->x = g_Player.pos.x + g_Player.vtxMin.x - (size.x / 2);
				bAttack = true;
			}
			else if (posOld->x - (size.x / 2) >= g_Player.pos.x + g_Player.vtxMax.x &&
				pos->x - (size.x / 2) <= g_Player.pos.x + g_Player.vtxMax.x)
			{//右側からモデルにめり込んだ時
			 //*pos.xにモデルのpos.x(右側)を設定
				pos->x = g_Player.pos.x + g_Player.vtxMax.x + (size.x / 2);
				bAttack = true;
			}
		}
		if (pos->x - (size.x / 2) < g_Player.pos.x + g_Player.vtxMax.x &&
			pos->x + (size.x / 2) > g_Player.pos.x + g_Player.vtxMin.x)
		{// *posのx座標がモデルに重なっている時
			if (posOld->z - (size.z / 2) <= g_Player.pos.z + g_Player.vtxMin.z &&
				pos->z + (size.z / 2) > g_Player.pos.z + g_Player.vtxMin.z)
			{//モデルの手前側からめり込んだ時
			 //*pos.zにモデルのpos.z(手前側)を設定
				pos->z = g_Player.pos.z + g_Player.vtxMin.z - (size.z / 2);
				bAttack = true;
			}
			else if (posOld->z + (size.z / 2) >= g_Player.pos.z + g_Player.vtxMax.z &&
				pos->z - (size.z / 2) < g_Player.pos.z + g_Player.vtxMax.z)
			{//モデルの奥側からめり込んだ時
			 //*pos.zにモデルのpos.z(奥側)を設定
				pos->z = g_Player.pos.z + g_Player.vtxMax.z + (size.z / 2);
				bAttack = true;
			}
		}
		else
		{
			bAttack = false;
		}
	}

	return bAttack;
}
