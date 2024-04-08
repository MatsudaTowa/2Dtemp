//=============================================
//
//2DTemplate[game.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GAME_H
#define _GAME_H

#include "main.h"

//=============================================
//構想体の定義
//=============================================
typedef struct
{
	int nType; //種類
	D3DXVECTOR3 pos; //中心
	int nSpawn; //スポーンするフレーム
	bool bUse; //使用されているか
}EnemyInfo;

typedef struct
{
	D3DXVECTOR3 pos; //位置
	int nType; //種類
	bool bUse; //使用してるかどうか
}BlockInfo;

//プロトタイプ宣言
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void LoadEnemy(void);
void LoadBlock(void);
bool GetEdit(void);
#endif // !_GAME_H

