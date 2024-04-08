//=============================================
//
//2DTemplate[result.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "result.h"
#include "input.h"
#include "player.h"
//#include "enemy.h"
#include "fade.h"
#include "sound.h"

//=============================================
//マクロ定義
//=============================================
#define NUM_RESULT (1) //リザルトの種類
#define PLUS_POINTER	(4) //ポインタを進める数
#define MAX_DIGIT	(6) //最大桁数
#define VERTEX	(4) //頂点数
//=============================================
//グローバル変数
//=============================================
LPDIRECT3DTEXTURE9 g_apTextureResult[NUM_RESULT] = {}; //テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL; //頂点バッファのポインタ
int g_Result; //0:BG,1:スコア
//=============================================
//リザルト画面の初期化処理
//=============================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	Player* pPlayer = GetPlayer();

	//デバイスの取得
	pDevice = GetDevice();

	if (pPlayer->bUse == false)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\GAMEOVER.png",
			&g_apTextureResult[0]
		);


		////テクスチャの読み込み
		//D3DXCreateTextureFromFile(pDevice,
		//	"data\\TEXTURE\\gameoverwhite.png",
		//	&g_apTextureResult[1]
		//);

	}

	else
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\result.png",
			&g_apTextureResult[0]
		);

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\Number.png",
			&g_apTextureResult[1]
		);


		////テクスチャの読み込み
		//D3DXCreateTextureFromFile(pDevice,
		//	"data\\TEXTURE\\GAMECLEAR.png",
		//	&g_apTextureResult[1]
		//);
	}







	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_RESULT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffResult, NULL);

	VERTEX_2D* pVtx;
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);


	////頂点座標の設定
	//pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	//pVtx[6].pos = D3DXVECTOR3(0.0f, 620.0f, 0.0f);
	//pVtx[7].pos = D3DXVECTOR3(1280.0f, 620.0f, 0.0f);

	for (int nCntResult = 0; nCntResult < NUM_RESULT; nCntResult++)
	{
		if (nCntResult == 0)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}
		if (nCntResult == 1)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(20.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 40.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(20.0f, 40.0f, 0.0f);
		}
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャの座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += PLUS_POINTER; //頂点ポインタを4つ進める
	}
	g_pVtxBuffResult->Unlock();
}

//=============================================
//リザルト画面の終了処理
//=============================================
void UninitResult(void)
{

	Player* pPlayer = GetPlayer();

	for (int nCntResult = 0; nCntResult < NUM_RESULT; nCntResult++)
	{

		if (g_apTextureResult[nCntResult] != NULL)
		{
			g_apTextureResult[nCntResult]->Release();
			g_apTextureResult[nCntResult] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
	StopSound();
}

//=============================================
//リザルト画面の更新処理
//=============================================
void UpdateResult(void)
{
	Player* pPlayer = GetPlayer();

	if (pPlayer->bUse == false)
	{
		float fGetColorFade = FadeColor();
		if ((GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true) && fGetColorFade <= 0.0f)
		{//決定キーが押された
			//メニューに移行
			//PlaySound(SOUND_LABEL_SE_DECISION);
			SetFade(MODE_TITLE);
		}
	}
	else
	{
		float fGetColorFade = FadeColor();

		if ((GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true) && fGetColorFade <= 0.0f)
		{//決定キーが押された
			//メニューに移行
			//PlaySound(SOUND_LABEL_SE_DECISION);
			SetFade(MODE_TITLE);
		}
	}
}

//=============================================
//リザルト画面の描画処理
//=============================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	Player* pPlayer = GetPlayer();

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntResult = 0; nCntResult < NUM_RESULT; nCntResult++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureResult[nCntResult]);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			VERTEX * nCntResult,
			2);
	}
}
