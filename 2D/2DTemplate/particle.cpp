//=============================================
//
//2DTemplate[Particle.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "particle.h"
#include "input.h"
#include "camera.h"

//=============================================
//マクロ定義
//=============================================
#define MAX_PARTICLE (10000) //エフェクトの最大数
#define PARTICLE_LIFE	(1000000) //エフェクトの寿命
#define MINUS_LIFESPAN	(1) //ライフの減る数
#define VERTEX	(4) //頂点数

//パーティクル構造体
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXVECTOR3 move; //移動量
	D3DXCOLOR col; //色
	float fRadius; //半径
	int nLife; //ライフ
	bool bUse; //使用されているかの確認
}Particle;

//=============================================
//グローバル変数
//=============================================
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL; //頂点バッファへのポインタ
Particle g_aParticle[MAX_PARTICLE]; //エフェクトの情報

//=============================================
//エフェクトの初期化処理
//=============================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntParticle;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect.png",
		&g_pTextureParticle
	);

	//エフェクトの初期化
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].move = D3DXVECTOR3(10.0f,10.0f, 0.0f); //移動量
		g_aParticle[nCntParticle].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].fRadius = 0.0f;
		g_aParticle[nCntParticle].nLife = 0.0f;
		g_aParticle[nCntParticle].bUse = false; //使用してない状態
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PARTICLE, D3DUSAGE_WRITEONLY, 4, D3DPOOL_MANAGED, &g_pVtxBuffParticle, NULL);

	VERTEX_2D* pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = g_aParticle[nCntParticle].col;
		pVtx[1].col = g_aParticle[nCntParticle].col;
		pVtx[2].col = g_aParticle[nCntParticle].col;
		pVtx[3].col = g_aParticle[nCntParticle].col;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += VERTEX; //頂点ポインタを4つ進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffParticle->Unlock();
}

//=============================================
//エフェクトの終了処理
//=============================================
void UninitParticle(void)
{
	//テクスチャの破棄
	if (g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}

//=============================================
//エフェクトの更新処理
//=============================================
void UpdateParticle(void)
{
	VERTEX_2D* pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得pp
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);
	int nCntParticle;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{

			if (g_aParticle[nCntParticle].nLife <= 0)
			{
				g_aParticle[nCntParticle].bUse = false;
			}

			D3DXVECTOR3 Vtx = ScreenConversion(g_aParticle[nCntParticle].pos);

			Vtx += g_aParticle[nCntParticle].move;

			pVtx[0].pos += g_aParticle[nCntParticle].move;
			pVtx[1].pos += g_aParticle[nCntParticle].move;
			pVtx[2].pos += g_aParticle[nCntParticle].move;
			pVtx[3].pos += g_aParticle[nCntParticle].move;

		}

		D3DXVECTOR3 Vtx = ScreenConversion(g_aParticle[nCntParticle].pos);

		//if (Vtx.x < 0
		//	|| Vtx.x >= SCREEN_WIDTH
		//	|| Vtx.y >= SCREEN_HEIGHT)
		//{
		//	g_aParticle[nCntParticle].bUse = false;
		//}
		pVtx += 4;
	}



	g_pVtxBuffParticle->Unlock();
}

//=============================================
//エフェクトの描画処理
//=============================================
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntParticle;

	//デバイスの取得
	pDevice = GetDevice();

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureParticle);
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{//エフェクトが使用されていた時
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				VERTEX * nCntParticle,
				2);
		}
	}

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================
//エフェクトの設定処理
//=============================================
void SetParticle(D3DXVECTOR3 pos,float fRadius, D3DXCOLOR col)
{
	int nCntParticle;
	float fVertex;
	float fMove;
	VERTEX_2D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	fVertex = (float)(rand() % 629 - 314) / 100.0f;
	fMove = (float)(rand() % 120) / 20.0f + 10;


	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{//エフェクトが使用されてないとき
			pVtx += (nCntParticle * VERTEX);
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].move.x = sinf(fVertex) * fMove;
			g_aParticle[nCntParticle].move.y = cosf(fVertex) * fMove;
			g_aParticle[nCntParticle].nLife = 20;
			g_aParticle[nCntParticle].fRadius = fRadius;
			g_aParticle[nCntParticle].col = col;
			g_aParticle[nCntParticle].bUse = true;

			//頂点カラーの設定
			pVtx[0].col = g_aParticle[nCntParticle].col;
			pVtx[1].col = g_aParticle[nCntParticle].col;
			pVtx[2].col = g_aParticle[nCntParticle].col;
			pVtx[3].col = g_aParticle[nCntParticle].col;

			//頂点座標の設定
			pVtx[0].pos.x = g_aParticle[nCntParticle].pos.x - g_aParticle[nCntParticle].fRadius;
			pVtx[0].pos.y = g_aParticle[nCntParticle].pos.y - g_aParticle[nCntParticle].fRadius;
			pVtx[1].pos.x = g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fRadius;
			pVtx[1].pos.y = g_aParticle[nCntParticle].pos.y - g_aParticle[nCntParticle].fRadius;
			pVtx[2].pos.x = g_aParticle[nCntParticle].pos.x - g_aParticle[nCntParticle].fRadius;
			pVtx[2].pos.y = g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fRadius;
			pVtx[3].pos.x = g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fRadius;
			pVtx[3].pos.y = g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fRadius;

			break; //forを抜ける
		}
	}
	
	g_pVtxBuffParticle->Unlock();
}
