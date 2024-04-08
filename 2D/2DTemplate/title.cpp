//=============================================
//
//2DTemplate[title.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
//=============================================
//マクロ定義
//=============================================
#define NUM_TITLE (2) //タイトルの種類
#define PLUS_POINTER	(4) //ポインタを進める数
#define VERTEX	(4) //頂点数
#define START_FONT_POS	(1000.0f) //スコアの10桁目のポジション
#define START_PLUS_POS	(20.0f) //スコアの10桁目のポジションに足す値
#define START_NUMBER	(0.0f) //テクスチャの画像の座標のスタート値
#define Tutorial	(200)
#define ANIMATION_CNT	(10) //アニメーションカウント数
//#define ANIMATION_PATTERN	(8) //アニメーションパターン数

//=============================================
//グローバル変数
//=============================================
LPDIRECT3DTEXTURE9 g_apTextureTitle[NUM_TITLE] = {}; //テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL; //頂点バッファのポインタ
float g_fY = START_FONT_POS; //文字の表示するX座標
int nCntAnim = 0; //アニメーションカウント
int nPatternAnim = 0; //アニメーションパターン
//FADE fadetitle;
float g_fTitleFlash;
float g_fTitleAlpha; //α値
int g_nCntTime;
int g_TitleType;
//=============================================
//タイトル画面の初期化処理
//=============================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTitle;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title.png",
		&g_apTextureTitle[0]
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\start.png",
		&g_apTextureTitle[1]
	);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TITLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL);

	VERTEX_2D* pVtx;
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	g_fTitleAlpha = 0.2f;

	g_fTitleFlash = 0.02f;

	g_nCntTime = 0;

	g_TitleType = 0;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++,g_TitleType++)
	{
		if (g_TitleType == 0)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}
		else if (g_TitleType == 1)
		{
			pVtx[0].pos = D3DXVECTOR3(400.0f, 500.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(800.0f, 500.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(400.0f, 750.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(800.0f, 750.0f, 0.0f);
		}

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);

		//テクスチャの座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += PLUS_POINTER; //頂点ポインタを4つ進める
	}
	g_pVtxBuffTitle->Unlock();
	//PlaySound(SOUND_LABEL_BGM_TITLE);
}

//=============================================
//タイトル画面の終了処理
//=============================================
void UninitTitle(void)
{
	//サウンドの停止
	StopSound();

	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{

		if (g_apTextureTitle[nCntTitle] != NULL)
		{
			g_apTextureTitle[nCntTitle]->Release();
			g_apTextureTitle[nCntTitle] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//=============================================
//タイトル画面の更新処理
//=============================================
void UpdateTitle(void)
{
	g_TitleType = 0;
	float fGetColorFade = FadeColor();
	if ((GetKeyboardTrigger(DIK_RETURN) == true 
		|| GetJoypadTrigger(JOYKEY_START) == true
		|| GetJoypadTrigger(JOYKEY_A) == true)
		&& fGetColorFade <= 0.0f)
	{//決定キーが押された
	  //ゲームに移行
		SetFade(MODE_TUTORIAL);
	}

	VERTEX_2D* pVtx;
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
		
	if (g_fTitleAlpha >= 1.0f || g_fTitleAlpha <= 0.0f)
		{
			g_fTitleFlash *= -1.0f;
		}
	g_fTitleAlpha += g_fTitleFlash;

	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++, g_TitleType++)
	{

		if (g_TitleType == 1)
		{
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fTitleAlpha);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fTitleAlpha);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fTitleAlpha);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fTitleAlpha);
		}

		pVtx += PLUS_POINTER; //頂点ポインタを4つ進める
	}

	//int nAnswer = g_nCntTime / NEXT;

	//if (nAnswer == 1)
	//{
	//	SetMode(MODE_TUTORIAL);
	//}
}

//=============================================
//タイトル画面の描画処理
//=============================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureTitle[nCntTitle]);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			VERTEX * nCntTitle,
			2);
	}
}
