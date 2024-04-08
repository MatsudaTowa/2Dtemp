//=============================================
//
//2DTemplate[Pause.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "pause.h"
#include "result.h"
#include "input.h"
#include "sound.h"

//=============================================
//マクロ定義
//=============================================
#define NUM_PAUSE (5) //メニューの種類
#define PLUS_POINTER	(4) //ポインタを進める数
#define VERTEX	(4) //頂点数
#define START_FONT_POS	(1000.0f) //スコアの10桁目のポジション
#define START_PLUS_POS	(20.0f) //スコアの10桁目のポジションに足す値
#define START_NUMBER	(0.0f) //テクスチャの画像の座標のスタート値
//=============================================
//グローバル変数
//=============================================
LPDIRECT3DTEXTURE9 g_apTexturePause[NUM_PAUSE] = {}; //テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL; //頂点バッファのポインタ
int g_nPauseSelect = 0;
//=============================================
//メニュー画面の初期化処理
//=============================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntPause;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\PAUSE.png",
		&g_apTexturePause[1]
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Continue.png",
		&g_apTexturePause[2]
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RETRY.png",
		&g_apTexturePause[3]
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\QUIT.png",
		&g_apTexturePause[4]
	);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PAUSE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPause, NULL);

	VERTEX_2D* pVtx;
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	g_nPauseSelect = 0;

	for (int nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		if (nCntPause == 0)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}
		else if (nCntPause == 1)
		{
			pVtx[0].pos = D3DXVECTOR3(120.0f, 80.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1120.0f, 80.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(120.0f, 580.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1120.0f, 580.0f, 0.0f);
		}
		else if (nCntPause == 2)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(475.0f, 170.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(740.0f, 170.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(475.0f, 320.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(740.0f, 320.0f, 0.0f);
		}
		else if (nCntPause == 3)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(475.0f, 270.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(740.0f, 270.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(475.0f, 420.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(740.0f, 420.0f, 0.0f);
		}
		else if (nCntPause == 4)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(475.0f, 370.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(740.0f, 370.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(475.0f, 520.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(740.0f, 520.0f, 0.0f);
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
	g_pVtxBuffPause->Unlock();
	//PlaySound(SOUND_LABEL_BGM000);
}

//=============================================
//メニュー画面の終了処理
//=============================================
void UninitPause(void)
{
	//サウンドの停止
	//StopSound();

	for (int nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{

		if (g_apTexturePause[nCntPause] != NULL)
		{
			g_apTexturePause[nCntPause]->Release();
			g_apTexturePause[nCntPause] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//=============================================
//メニュー画面の更新処理
//=============================================
void UpdatePause(void)
{
	VERTEX_2D* pVtx;

	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	

	if (GetKeyboardTrigger(DIK_DOWN) == true|| GetJoypadTrigger(JOYKEY_DOWN) == true)
	{//↓キーが押された
		g_nPauseSelect++;
		if (g_nPauseSelect > 2)
		{
			g_nPauseSelect = 0;
		}

	}
	if (GetKeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP) == true)
	{//↑キーが押された
		g_nPauseSelect--;
		if (g_nPauseSelect < 0)
		{
			g_nPauseSelect = 2;
		}

	}

	for (int nCnt = 0; nCnt < NUM_PAUSE; nCnt++)
	{
		if (g_nPauseSelect == 0)
		{
			if (nCnt == 0)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 150);
				pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 150);
				pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 150);
				pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 150);
			}
			else if (nCnt == 1)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			else if (nCnt == 2)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(150, 150, 250, 255);
				pVtx[1].col = D3DCOLOR_RGBA(150, 150, 250, 255);
				pVtx[2].col = D3DCOLOR_RGBA(150, 150, 250, 255);
				pVtx[3].col = D3DCOLOR_RGBA(150, 150, 250, 255);
			}
			else if (nCnt == 3)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			}
			else if (nCnt == 4)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
		}
		else if (g_nPauseSelect == 1)
		{
			if (nCnt == 0)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 150);
				pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 150);
				pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 150);
				pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 150);
			}
			else if (nCnt == 1)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			else if (nCnt == 2)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			}
			else if (nCnt == 3)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(150, 150, 250, 255);
				pVtx[1].col = D3DCOLOR_RGBA(150, 150, 250, 255);
				pVtx[2].col = D3DCOLOR_RGBA(150, 150, 250, 255);
				pVtx[3].col = D3DCOLOR_RGBA(150, 150, 250, 255);

			}
			else if (nCnt == 4)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}

		}
		else if (g_nPauseSelect == 2)
		{
			//頂点カラーの設定
			if (nCnt == 0)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 150);
				pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 150);
				pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 150);
				pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 150);
			}
			else if (nCnt == 1)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			else if (nCnt == 2)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			}
			else if (nCnt == 3)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			}
			else if (nCnt == 4)
			{

				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(150, 150, 250, 255);
				pVtx[1].col = D3DCOLOR_RGBA(150, 150, 250, 255);
				pVtx[2].col = D3DCOLOR_RGBA(150, 150, 250, 255);
				pVtx[3].col = D3DCOLOR_RGBA(150, 150, 250, 255);
			}
		}		

		pVtx += VERTEX;
	}
	g_pVtxBuffPause->Unlock();
}

//=============================================
//メニュー画面の描画処理
//=============================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScreen;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTexturePause[nCntPause]);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			VERTEX * nCntPause,
			2);
	}
}


//=============================================
//今選択されてる選択肢の取得
//=============================================
int GetNumPause(void)
{
	return g_nPauseSelect;
}