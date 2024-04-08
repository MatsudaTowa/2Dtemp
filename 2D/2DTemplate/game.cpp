//=============================================
//
//2DTemplate[game.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "particle.h"
#include "pause.h"
#include "Screen.h"
#include "game.h"
#include "time.h"
#include "fade.h"
#include "time.h"

#include "sound.h"

//=============================================
//マクロ定義
//=============================================
#define TXT_MAX	(256) //文字の最大数
#define SPAWN_ENEMY	(3) //スポーン数
#define WAVE	(6) //ウェーブ数

//グローバル変数
bool g_bPause = false; //ポーズかどうか
bool g_bEdit = false; //エディットモードかどうか
int g_nUseEnemy = 0; //敵の使用数
int g_nUseBlock = 0; //ブロックの使用数
int g_MaxReadNum = 0;
int g_nWave = 0;
int nFrame = 0;
int g_FinishCnt;
int g_Spawn = TIME;
EnemyInfo g_EnemyInfo[MAX_ENEMY];
Player* pPlayer = GetPlayer();

//=============================================
//ゲームの初期化処理
//=============================================
void InitGame(void)
{
	g_nWave = 0;
	g_nUseEnemy = 0;
	g_FinishCnt = 0;
	//カメラの初期化
	InitCamera();
	
	//スクリーンの初期化処理
	InitScreen();

	////パーティクルの初期化処理
	//InitParticle();

	//ポリゴンの初期化処理
	InitPlayer();

	InitParticle();


	g_bPause = false; //ポーズ解除
	g_bEdit = false;

	//if (g_bPause == true)
	//{//ポーズしてたら
		InitPause();
	//}



}

//=============================================
//ゲームの終了処理
//=============================================
void UninitGame(void)
{
	//スクリーンの終了処理
	UninitScreen();

	//パーティクルの終了処理
	UninitParticle();

	//ポリゴンの終了処理
	UninitPlayer();

	////UI背景の終了処理
	//UninitUIzone();


	if (g_bPause == true)
	{//ポーズしてたら
	//ポーズの終了
	UninitPause();
	}

	//カメラの終了処理
	UninitCamera();

	StopSound();
}

//=============================================
//ゲームの更新処理
//=============================================
void UpdateGame(void)
{
	float fGetColorFade = FadeColor();
	int nGetNumPause = GetNumPause();
	//int nGetNumEnemy = GetNumEnemy();
	//Enemy* pEnemy = GetEnemy();
	//D3DXVECTOR3 EditCameraPos = GetEditCameraPos();

	if ((GetKeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true) && pPlayer->bUse ==true)
	{//ポーズが押された
		if (g_bPause == false)
		{
			//PlaySound(SOUND_LABEL_SE_PAUSE);
		}
		g_bPause = g_bPause ? false : true;
	}
	if (g_bPause == true)
	{
		UpdatePause();
		if ((GetKeyboardTrigger(DIK_RETURN) == true 
			|| GetJoypadTrigger(JOYKEY_A) == true) 
			&& nGetNumPause == 0 
			&& fGetColorFade <= 0.0f)
		{//決定キーが押された
			g_bPause = false;
		}
		if ((GetKeyboardTrigger(DIK_RETURN) == true 
			|| GetJoypadTrigger(JOYKEY_A) == true) 
			&& nGetNumPause == 1
			&&  fGetColorFade <= 0.0f)
		{//決定キーが押された
			SetFade(MODE_GAME);
		}
		else if ((GetKeyboardTrigger(DIK_RETURN) == true 
			|| GetJoypadTrigger(JOYKEY_A) == true) 
			&& nGetNumPause == 2 
			&& fGetColorFade <= 0.0f)
		{//決定キーが押された
			SetFade(MODE_TITLE);
		}
	}


	if (g_bPause == false)
	{
		#ifdef _DEBUG
		if (GetKeyboardTrigger(DIK_F1) == true)
		{
			g_bEdit = g_bEdit ? false : true;
		}
		if (GetKeyboardTrigger(DIK_F2) == true)
		{
			g_bEdit = g_bEdit ? false : true;
		}
		#endif

		if (g_bEdit == true)
		{
			//UpdateCamera(pEditBlockInfo->pos);
		}
	}


	if (g_bPause == false && g_bEdit == false)
	{//ポーズしてなかったら
		//スクリーンの更新処理
		UpdateScreen();


		UpdateCamera(pPlayer->pos);

		//パーティクルの更新処理
		UpdateParticle();


		////ホーミングの更新処理
		//UpdateHoming();

		////ランチャーの更新処理
		//Updatelauncher();

		//プレイヤーの更新処理
		UpdatePlayer();

		////バリアの更新処理
		//UpdateBarrier();

		////バフの更新処理
		//UpdateBuff();

		////オート更新処理
		//UpdateAuto();

		////タレット更新処理
		//UpdateTurret();

		////UI背景の更新処理
		//UpdateUIzone();

		//if (pPlayer->character == CHARACTER_1)
		//{
		//	//UIの更新処理
		//	UpdateUI();
		//	//UIの更新処理
		//	UpdateHomingUI();
		//}

		//else if (pPlayer->character == CHARACTER_2)
		//{
		//	//UIの更新処理
		//	UpdateBuffUI();
		//	//UIの更新処理
		//	UpdateLauncherUI();
		//}

		//else if (pPlayer->character == CHARACTER_3)
		//{
		//	//UIの更新処理
		//	UpdateTurretUI();
		//	//UIの更新処理
		//	UpdateAutoUI();
		//}

		//int nGetNumEnemy = GetNumEnemy();




	if (g_nWave >= WAVE || pPlayer->bUse == false)
	{
		g_FinishCnt++;
		if (g_FinishCnt >= 30)
		{
			//リザルトに移行
			SetFade(MODE_RESULT);
		}
	}
		#ifdef _DEBUG
			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{
				SetFade(MODE_RESULT);
			}
		#endif

	}
}

//=============================================
//ゲームの描画処理
//=============================================
void DrawGame(void)
{
	//スクリーンの描画処理
	DrawScreen();

	////ホーミングの描画処理
	//DrawHoming();

	//プレイヤーの描画処理
	DrawPlayer();

	//パーティクルの描画処理
	DrawParticle();

	if (g_bPause == true)
	{//ポーズしてたら
	//ポーズの描画処理
		DrawPause();
	}
}

//=============================================
//敵のロード処理
//=============================================
void LoadEnemy(void)
{
	////ファイルの読み込み
	//FILE* pFile = fopen(FILE_ENEMY, "rb");

	//if (pFile != NULL)
	//{
	//	//敵の使用してる数の読み込み
	//	fread(&g_nUseEnemy, sizeof(int), 1, pFile);

	//	//敵の使用数分、敵の読み込み
	//	fread(&g_EnemyInfo[0], sizeof(EnemyInfo), g_nUseEnemy, pFile);

	//	//ファイルを閉じる
	//	fclose(pFile);

	//}

	//else
	//{
	//	return;
	//}


	//for (int nCnt = 0; nCnt < g_nUseEnemy; nCnt++)
	//{

	//	SetEnemy(g_EnemyInfo[nCnt].pos, g_EnemyInfo[nCnt].nType);

	//}

	
}

//=============================================
//ブロックのロード処理
//=============================================
void LoadBlock(void)
{
	////ファイルの読み込み
	//FILE* pFile = fopen(FILE_BLOCK, "rb");

	//if (pFile != NULL)
	//{
	//	//ブロックの使用してる数の読み込み
	//	fread(&g_nUseBlock, sizeof(int), 1, pFile);

	//	//ブロックの使用数分、ブロックの情報読み込み
	//	fread(&g_BlockInfo[0], sizeof(BlockInfo), g_nUseBlock, pFile);

	//	//ファイルを閉じる
	//	fclose(pFile);

	//}

	//else
	//{
	//	return;
	//}

	////nFrame++;
	////int nAnswer = nFrame / 60;
	////if (nAnswer == 1)
	////{
	//	for (int nCnt = 0; nCnt < g_nUseBlock; nCnt++)
	//	{
	//		Setblock(g_BlockInfo[nCnt].pos, g_BlockInfo[nCnt].nType);
	//	}
	////	nFrame = 0;
	////}
}

//エディットの取得
bool GetEdit(void)
{
	return g_bEdit;
}