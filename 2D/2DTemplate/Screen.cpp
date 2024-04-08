//=============================================
//
//2DTemplate[Screen.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "player.h"
#include "Screen.h"

//=============================================
//マクロ定義
//=============================================
#define NUM_SCREEN (1) //背景の種類
#define PLUS_POINTER	(4) //ポインタを進める数
#define VERTEX	(4) //頂点数
#define MOVE_V_TEXTURE1	(0.005f) //一枚目の背景のU座標更新
#define MOVE_V_TEXTURE2	(0.007f) //二枚目の背景のU座標更新
#define MOVE_V_TEXTURE3	(0.001f) //三枚目の背景のU座標更新

//=============================================
//グローバル変数
//=============================================
LPDIRECT3DTEXTURE9 g_apTextureScreen = NULL; //テクスチャ(3枚)ポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScreen = NULL; //頂点バッファのポインタ
float g_aPosTexV; //テクスチャ座標の開始位置(V値)

//=============================================
//ポリゴンの初期化処理
//=============================================
void InitScreen(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScreen;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\IMG_5603.JPG",
		&g_apTextureScreen
	);


	//テクスチャ座標の開始位置(V値)の初期化

	g_aPosTexV = 0.0f;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SCREEN, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffScreen, NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffScreen->Lock(0, 0, (void**)&pVtx, 0);

	//for (nCntScreen = 0; nCntScreen < NUM_SCREEN; nCntScreen++)
	//{
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
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャの座標指定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f ,1.0f);

		//pVtx += PLUS_POINTER; //頂点ポインタを4つ進める

	//}
	g_pVtxBuffScreen->Unlock();
}

//=============================================
//ポリゴンの終了処理
//=============================================
void UninitScreen(void)
{
	//テクスチャの破棄

		
	if (g_apTextureScreen != NULL)
	{

		g_apTextureScreen->Release();
		g_apTextureScreen = NULL;
	}


	//頂点バッファの破棄
	if (g_pVtxBuffScreen != NULL)
	{
		g_pVtxBuffScreen->Release();
		g_pVtxBuffScreen = NULL;
	}
}

//=============================================
//ポリゴンの更新処理
//=============================================
void UpdateScreen(void)
{
}

//=============================================
//ポリゴンの描画処理
//=============================================
void DrawScreen(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScreen;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScreen, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureScreen);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			2);

}

//=============================================
//テクスチャ座標更新
//=============================================
void ScreenTexMove(D3DXVECTOR2 tex)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffScreen->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの座標指定
	pVtx[0].tex += tex;
	pVtx[1].tex += tex;
	pVtx[2].tex += tex;
	pVtx[3].tex += tex;

	g_pVtxBuffScreen->Unlock();

}
