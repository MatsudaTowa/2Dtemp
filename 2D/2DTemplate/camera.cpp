//=============================================
//
//2DTemplate[camera.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "camera.h"
#include "input.h"
//#include "sound.h"
#include "fade.h"
//=============================================
//マクロ定義
//=============================================
#define PLUS_POINTER	(4) //ポインタを進める数
#define VERTEX	(4) //頂点数
#define START_NUMBER	(0.0f) //テクスチャの画像の座標のスタート値
#define DAMPING_COEFFICIENT	(0.2f) //抵抗力

//#define ANIMATION_PATTERN	(8) //アニメーションパターン数

//=============================================
//グローバル変数
//=============================================
LPDIRECT3DTEXTURE9 g_pTexturecamera = NULL; //テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffcamera = NULL; //頂点バッファのポインタ
//FADE fadecamera;
D3DXVECTOR3 g_CameraPos;
D3DXVECTOR3 g_CameraOldPos;

//=============================================
//カメラの初期化処理
//=============================================
void InitCamera(void)
{
	//LPDIRECT3DDEVICE9 pDevice;
	//int nCntcamera;
	////デバイスの取得
	//pDevice = GetDevice();

	g_CameraPos = D3DXVECTOR3(WORLD_WIDTH * 0.5f, WORLD_HEIGHT * 0.5f, 0.0f);
	g_CameraOldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//PlaySound(SOUND_LABEL_BGM000);
}

//=============================================
//スクリーン変換
//=============================================
D3DXVECTOR3 ScreenConversion(D3DXVECTOR3 pos)
{

	g_CameraOldPos = g_CameraPos;

	//カメラ座標をスクリーンの原点に変換
	D3DXVECTOR3 ScreenOriginPos = D3DXVECTOR3 (g_CameraOldPos.x - SCREEN_WIDTH / 2, g_CameraOldPos.y - SCREEN_HEIGHT / 2 , 1.0f);

	//ワールド座標から対象のばしょに変換する
	D3DXVECTOR3 ScreenPos = D3DXVECTOR3(pos.x - ScreenOriginPos.x, pos.y - ScreenOriginPos.y , 1.0f);

	return ScreenPos;
}

//=============================================
//カメラの終了処理
//=============================================
void UninitCamera(void)
{
	//サウンドの停止
	//StopSound();

	
	//頂点バッファの破棄
	if (g_pVtxBuffcamera != NULL)
	{
		g_pVtxBuffcamera->Release();
		g_pVtxBuffcamera = NULL;
	}
}

//=============================================
//カメラの更新処理
//=============================================
void UpdateCamera(D3DXVECTOR3 pos)
{

	g_CameraOldPos = g_CameraPos;

	g_CameraPos = pos;

	//X軸のステージの判定
	if (g_CameraOldPos.x - SCREEN_WIDTH * 0.5f <= 0.0f)
	{
		g_CameraPos.x = SCREEN_WIDTH * 0.5f;
	}
	if (g_CameraOldPos.x + SCREEN_WIDTH * 0.5f >= WORLD_WIDTH)
	{
		g_CameraPos.x = WORLD_WIDTH - SCREEN_WIDTH * 0.5f;
	}

	////Y軸のステージの判定
	//if (g_CameraPos.y - SCREEN_HEIGHT * 0.5f <= 0.0f)
	//{
	//	g_CameraPos.y = SCREEN_HEIGHT * 0.5f;
	//}
	if (g_CameraPos.y + SCREEN_HEIGHT * 0.5f >= WORLD_HEIGHT)
	{
		g_CameraPos.y = WORLD_HEIGHT - SCREEN_HEIGHT * 0.5f;
	}
}

////=============================================
////カメラの描画処理
////=============================================
//void DrawCamera(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//
//	//デバイスの取得
//	pDevice = GetDevice();
//
//	//頂点バッファをデータストリームに設定
//	pDevice->SetStreamSource(0, g_pVtxBuffcamera, 0, sizeof(VERTEX_2D));
//
//	//頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//ポリゴンの描画
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
//		0,
//		2);
//	
//}
