//=============================================
//
//2DTemplate[main.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MAIN_H_ //これが定義されてないとき

#define _MAIN_H_
//ライブラリのリンク
#pragma comment(lib,"d3d9.lib") //描画処理に必要
#pragma comment(lib,"d3dx9.lib") //↑の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")
#pragma	comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")

//マクロ定義
#define SCREEN_WIDTH	(1280) //ウィンドウの幅
#define SCREEN_HEIGHT	(720) //ウィンドウの高さ
#define VERTEX	(4) //頂点数
#define NUM_TYPE_ENEMY (4) //敵の種類
#define WORLD_WIDTH	(111280) //ウィンドウの幅
#define WORLD_HEIGHT	(1440) //ウィンドウの高さ
#define MAX_ENEMY	(128) //敵の最大数
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE |D3DFVF_TEX1) //座標とカラーとテクスチャ
#define FILE_NAME	"data\\enemydata.bin" //ファイル名
#define EFFECT_TIME	(10) //エフェクトの持続時間
#define TIME	(60) //制限時間


//頂点情報(2D)の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos; //頂点座標
	float rhw; //座標変換用係数（1.0f）
	D3DCOLOR col; //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ
}VERTEX_2D;

//画面モードの種類
typedef enum
{
	MODE_TITLE = 0, //タイトル画面
	MODE_MENU, //メニュー画面
	MODE_TUTORIAL, //チュートリアル画面
	MODE_GAME, //ゲーム画面
	MODE_PICK, //ピック画面
	MODE_RESULT, //リザルト画面
	MODE_MAX,
}MODE;

//=============================================
//プロトタイプ宣言
//=============================================
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
LPD3DXFONT GetFont(void);
#endif // !_MAIN_H_ //これが定義されてないときx