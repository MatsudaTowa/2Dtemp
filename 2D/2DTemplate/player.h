//=============================================
//
//2DTemplate[player.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_H_ //定義されてなかったら
#define _PLAYER_H_ //２種インクルード防止

//マクロ
#define PLAYER_WIDE	(50.0f) //プレイヤーの横幅
#define PLAYER_HEIGHT	(50.0f) //プレイヤーの高さ

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_NORMAL = 0, //通常状態
	PLAYERSTATE_DAMAGE,	//ダメージ状態
	PLAYERSTATE_JUMP, //ジャンプ状態
	PLAYERSTATE_SWORD, //攻撃（剣）
	PLAYERSTATE_FIRE, //炎
	PLAYERSTATE_WING, //羽
	PLAYERSTATE_INVINCIBLE, //無敵タイム
	PLAYERSTATE_MAX
}PLAYERSTATE;

//プレイヤー構造体の定義
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXVECTOR3 oldpos; //前回の位置
	D3DXVECTOR3 rot; //向き
	D3DXVECTOR3 move; //移動量
	D3DXVECTOR3 moveTurn; //回転量
	D3DXVECTOR2 Size; 
	PLAYERSTATE  State; //状態
	PLAYERSTATE  oldState; //状態
	float fLength; //対角線の長さ
	float fAngle; //対角線の角度
	int nAnimCnt; //アニメーションカウント
	bool bDirection; //向き(true:右,false:左)
	int nLife; //HP	
	bool bUse; //使われているか
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void DebugPlayerPos(void);
void HitPlayer(int nDamage);
LPDIRECT3DDEVICE9 GetDevice(void);
Player* GetPlayer(void);


#endif // _POLYGON_H_ //定義されてなかったら

