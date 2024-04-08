//=============================================
//
//2DTemplate[Fade.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
//#include "menu.h"
//#include "tutorial.h"
#include "title.h"
#include "player.h"
#include "fade.h"
#include "input.h"


//=============================================
//マクロ定義
//=============================================
#define PLUS_POINTER	(4) //ポインタを進める数
#define VERTEX	(4) //頂点数
#define FADEVALUE	(0.1f) //フェード値

//=============================================
//グローバル変数
//=============================================
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL; //テクスチャ(3枚)ポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL; //頂点バッファのポインタ
FADE g_fade;
MODE g_fademode;
float g_colorFade = 0.0f;

//=============================================
//フェードの初期化処理
//=============================================
void InitFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Fade.png",
		&g_pTextureFade
	);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffFade, NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade);

	//テクスチャの座標指定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffFade->Unlock();
}

//=============================================
//フェードの終了処理
//=============================================
void UninitFade(void)
{
	//テクスチャの破棄
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//=============================================
//フェードの更新処理
//=============================================
void UpdateFade(void)
{
	VERTEX_2D* pVtx;
	
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//フェードイン状態
			g_colorFade -= FADEVALUE;
			if (g_colorFade <= 0.0f)
			{
				g_colorFade = 0.0f;
				g_fade = FADE_NONE; //何もしてない状態に
			}
		}
		else if (g_fade == FADE_OUT)
		{//フェードアウト状態
			g_colorFade += FADEVALUE;
			if (g_colorFade >= 1.0f)
			{
				g_colorFade = 1.0f;
				g_fade = FADE_IN; //フェードイン状態に
				SetMode(g_fademode);
			}           
		}
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade);
	}
	g_pVtxBuffFade->Unlock();
}

//=============================================
//フェードの描画処理
//=============================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureFade);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//=============================================
//敵の設定処理
//=============================================
void SetFade(MODE modeNext)
{
	g_fademode = modeNext;
	g_fade = FADE_OUT;
}

//=============================================
//フェードの取得
//=============================================
FADE GetFade(void)
{
	return g_fade;
}

float FadeColor(void)
{
	return g_colorFade;
}