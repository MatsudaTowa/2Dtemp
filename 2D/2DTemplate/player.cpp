//=============================================
//
//2DTemplate[player.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "Screen.h"
#include "sound.h"

//=============================================
//マクロ定義
//=============================================
#define DEFAULT_SPEED	(1.0f) //通常時のスピード
#define DEFAULT_TURN	(0.1f) //通常時の回転スピード
#define MAX_TURN	(0.15f) //通常時の回転スピード
#define DAMPING_COEFFICIENT	(0.2f) //抵抗力
#define DAMPING_SLIP_COEFFICIENT	(0.1f) //氷の抵抗力
#define REPULSIVE_FORCE	(0.6f) //反発力
#define SPAWN_X	(100.0f) //スポーンするX座標
#define PLAYER_MOVE_HEIGHT	(590.0f) //プレイヤーの移動できる高さ
#define JUMP	(-22.0f) //ジャンプ力
#define GRAVITY (0.8f) //重力の値
#define MAX_GRAVITY (20.0f) //重力の最大値
#define DEFAULT_MAGNIFICATION	(1.0f) //通常時の倍率
#define TEXTURE_MOVE (0.01f) //テクスチャームーブ値
//=============================================
//グローバル変数
//=============================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL; //テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;
Player g_Player;
float g_fMagnification = DEFAULT_MAGNIFICATION;
float g_PlayerTexU; //テクスチャーのU座標
float g_PlayerTexV; //テクスチャーのV座標
int g_nPressCnt = 0;
int g_nJumpCnt;
int g_nBlizzardCnt; //スロー時間
int g_nLavaCnt; //燃焼時間
int g_nFlyCnt; //浮遊時間
bool g_bJump; //ジャンプしてるかどうかの判定
bool g_bIslanding; //着地してるか
bool g_bFly; //浮遊

//=============================================
//ポリゴンの初期化処理
//=============================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;


	//デバイスの取得
	pDevice = GetDevice();

	g_Player.fLength = sqrtf(PLAYER_WIDE / 2.0f * PLAYER_WIDE / 2.0f + PLAYER_HEIGHT *2.0f * PLAYER_HEIGHT );
	g_Player.fAngle = atan2f(PLAYER_WIDE, PLAYER_HEIGHT);
	g_Player.Size = D3DXVECTOR2(PLAYER_WIDE/ 2.0f, PLAYER_HEIGHT);
	g_Player.oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //プレイヤーの前の位置
	g_Player.pos = D3DXVECTOR3(SPAWN_X,1350.0f, 0.0f); //プレイヤーの初期位置
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //初期の移動速度
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //初期の向き
	g_Player.bDirection = true;
	g_Player.State = PLAYERSTATE_NORMAL;
	g_Player.oldState = PLAYERSTATE_NORMAL;
	g_Player.bUse = true;
	g_Player.nAnimCnt = 0.0f;
	g_nJumpCnt = 0;
	g_nBlizzardCnt = 0;
	g_nLavaCnt = 0;
	g_nFlyCnt = 0;
	g_bJump = false;
	g_bIslanding = true;
	g_bFly = false;
	g_PlayerTexU = 0.0f;
	g_PlayerTexV = 0.0f;
	//g_bDirection = true; //方向の判定

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\mymelo.jpg",
		&g_pTexturePlayer
	);


	int nCntState = 0; //ダメージタイム

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)* 4, D3DUSAGE_WRITEONLY, 4, D3DPOOL_MANAGED, &g_pVtxBuffPlayer, NULL);

	D3DXVECTOR3 Vtx = ScreenConversion(g_Player.pos);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0,(void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = g_Player.pos.x - g_Player.Size.x;
	pVtx[0].pos.y = g_Player.pos.y - g_Player.Size.y;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Player.pos.x + g_Player.Size.x;
	pVtx[1].pos.y = g_Player.pos.y - g_Player.Size.y;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Player.pos.x - g_Player.Size.x;
	pVtx[2].pos.y = g_Player.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Player.pos.x + g_Player.Size.x;
	pVtx[3].pos.y = g_Player.pos.y;
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f,1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f,1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f,1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f,1.0f, 1.0f);

	//テクスチャの座標指定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffPlayer->Unlock();
	
}

//=============================================
//ポリゴンの終了処理
//=============================================
void UninitPlayer(void)
{
	if (g_Player.bUse == false)
	{
		//テクスチャの破棄
		if (g_pTexturePlayer != NULL)
		{
			g_pTexturePlayer->Release();
			g_pTexturePlayer = NULL;
		}

		//頂点バッファの破棄
		if (g_pVtxBuffPlayer != NULL)
		{
			g_pVtxBuffPlayer->Release();
			g_pVtxBuffPlayer = NULL;
		}
	}
}

//=============================================
//ポリゴンの更新処理
//=============================================
void UpdatePlayer(void)
{
	D3DXVECTOR3 Vtx = ScreenConversion(g_Player.pos);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	 
	if (g_Player.bUse == true)
	{
		D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);
		if (GetKeyboardPress(DIK_W) || GetJoypadPress(JOYKEY_UP))
		{ // 上。
			vecDirection.y -= 1.0f;
			ScreenTexMove(D3DXVECTOR2(0.0f,-0.01f));
		}
		if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_LEFT))
		{
			vecDirection.x -= 1.0f;
			ScreenTexMove(D3DXVECTOR2(-0.01f, 0.0f));

		}
		if (GetKeyboardPress(DIK_D) || GetJoypadPress(JOYKEY_RIGHT))
		{
			vecDirection.x += 1.0f;
			ScreenTexMove(D3DXVECTOR2(0.01f, 0.0f));
		}
		if (GetKeyboardPress(DIK_S) || GetJoypadPress(JOYKEY_DOWN))
		{
			vecDirection.y += 1.0f;
			ScreenTexMove(D3DXVECTOR2(0.0f, 0.01f));

		}

		if (vecDirection.x == 0.0f && vecDirection.y == 0.0f)
		{ // 動いてない。
			g_Player.move.x = 0.0f;
			g_Player.move.y = 0.0f;
		}
		else
		{
			float rotMoveY = atan2f(vecDirection.x, vecDirection.y);

			g_Player.move.x += sinf(rotMoveY) * DEFAULT_SPEED;
			g_Player.move.y += cosf(rotMoveY) * DEFAULT_SPEED;
			g_Player.rot.x = rotMoveY + D3DX_PI;
			//if (g_Player.rot.y <= -D3DX_PI)
			//{
			//	g_Player.rot.y = D3DX_PI;
			//}
		
		}

		g_Player.oldpos = g_Player.pos;

		g_Player.pos += g_Player.move;

		//移動量を更新(減速）

		g_Player.move *= 1.0f - DAMPING_COEFFICIENT;

		D3DXVECTOR3 Vtx = ScreenConversion(g_Player.pos);


		pVtx[0].pos.x = Vtx.x - g_Player.Size.x;
		pVtx[0].pos.y = Vtx.y - g_Player.Size.y;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = Vtx.x + g_Player.Size.x;
		pVtx[1].pos.y = Vtx.y - g_Player.Size.y;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = Vtx.x - g_Player.Size.x;
		pVtx[2].pos.y = Vtx.y;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = Vtx.x + g_Player.Size.x;
		pVtx[3].pos.y = Vtx.y;
		pVtx[3].pos.z = 0.0f;

		//テクスチャの座標指定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);		
		
	}
	g_pVtxBuffPlayer->Unlock();
}

//=============================================
//ポリゴンの描画処理
//=============================================
void DrawPlayer(void)
{
	if (g_Player.bUse == true)
	{
		LPDIRECT3DDEVICE9 pDevice;

		//デバイスの取得
		pDevice = GetDevice();

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);

		//テクスチャ拡大時に色を近似値にする
		pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//テクスチャ拡大時の色を線形補間
		pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	}
	DebugPlayerPos();
}

void DebugPlayerPos(void)
{
	LPD3DXFONT pFont = GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];


	//文字列に代入
	sprintf
	(&aStr[0],
		"\n\n\n\n\nPlayer pos[%.1f,%.1f,%.1f]\n"
		, g_Player.pos.x,g_Player.pos.y,g_Player.pos.z);

	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=============================================
//プレイヤーのヒット処理
//=============================================
void HitPlayer(int nDamage)
{
	//if (g_Player.State != PLAYERSTATE_DAMAGE)
	//{

	//	g_Player.oldState = g_Player.State;
	//	VERTEX_2D* pVtx;
	//	//頂点バッファをロックし頂点情報へのポインタを取得
	//	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//	g_Player.nLife -= nDamage;
	//	if (g_Player.nLife <= 0)
	//	{
	//		//g_nScoreCnt++;
	//		//SetExplosion(g_Player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EXPLSIONTYPE_NORMAL);
	//		g_Player.bUse = false;
	//	}
	//	else
	//	{
	//		g_Player.State = PLAYERSTATE_DAMAGE;
	//		g_Player.nCntState = DAMAGE_TIME;
	//		//頂点カラーの設定
	//		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	//		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	//		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	//		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	//	}
	//	g_pVtxBuffPlayer->Unlock();
	//}
	//PlaySound(SOUND_LABEL_SE_DAMAGE);
}

//=============================================
//プレイヤーの取得
//=============================================
Player* GetPlayer(void)
{
	return &g_Player;
}

//bool GetBarrierUsed(void)
//{
//	return g_bBarrierUsed;
//}