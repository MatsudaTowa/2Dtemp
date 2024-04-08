//=============================================
//
//2DTemplate[Tutorial.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "player.h"
#include "tutorial.h"
#include "input.h"
#include "sound.h"
#include "fade.h"

//=============================================
//マクロ定義
//=============================================
#define PLUS_POINTER	(4) //ポインタを進める数
#define VERTEX	(4) //頂点数

//=============================================
//グローバル変数
//=============================================
LPDIRECT3DTEXTURE9 g_pTextureTutorial = NULL; //テクスチャ(3枚)ポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL; //頂点バッファのポインタ
int g_nCntTutorialTime;
//=============================================
//チュートリアルの初期化処理
//=============================================
void InitTutorial(void)
{
	g_nCntTutorialTime = 0;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Tutorial.png",
		&g_pTextureTutorial
	);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 , D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTutorial, NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);


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
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffTutorial->Unlock();

}

//=============================================
//チュートリアルの終了処理
//=============================================
void UninitTutorial(void)
{
	//テクスチャの破棄
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

}

//=============================================
//チュートリアルの更新処理
//=============================================
void UpdateTutorial(void)
{
	float fGetColorFade = FadeColor();
	g_nCntTutorialTime++;
	if ((GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true) && fGetColorFade <= 0.0f)
	{//決定キーが押された
		//メニューに移行
		SetFade(MODE_GAME);
	}

}

//=============================================
//チュートリアルの描画処理
//=============================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTutorial);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			2);
}