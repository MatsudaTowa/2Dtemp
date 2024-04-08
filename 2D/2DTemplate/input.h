//=============================================
//
//2DTemplate[input.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _INPUT_H_ //定義されてなかったら
#define _INPUT_H_ //２種インクルード防止
#include "main.h"

//マクロ定義
#define JOYPAD_ZONE (1)
#define JOYPAD_SPEED (15)

//キーの種類
typedef enum
{
    JOYKEY_UP = 0,
    JOYKEY_DOWN,
    JOYKEY_LEFT,
    JOYKEY_RIGHT,
    JOYKEY_START,
    JOYKEY_BACK,
    JOYKEY_L3,
    JOYKEY_R3,
    JOYKEY_LB,
    JOYKEY_RB,
    JOYKEY_LT,
    JOYKEY_RT,
    JOYKEY_A,
    JOYKEY_B,
    JOYKEY_X,
    JOYKEY_Y,
    JOYKEY_MAX
}JOYKEY;

//スティックの番号
typedef enum
{
    STICKTYPE_LEFT = 0, // 左スティック
    STICKTYPE_RIGHT, // 右スティック
    STICKTYPE_MAX
}STICKTYPE;

//スティックの方向
typedef enum
{
    STICKANGLE_UP = 0, // 上
    STICKANGLE_DOWN,   // 下
    STICKANGLE_LEFT,   // 左
    STICKANGLE_RIGHT,  // 右
    STICKANGLE_MAX,
}STICKANGLE;

//スティックの入力情報
typedef struct
{
    float afTplDiameter[STICKTYPE_MAX];                      // スティックの倒し具合
    float afAngle[STICKTYPE_MAX];                            // スティックの角度
    bool abAnglePress[STICKTYPE_MAX][STICKANGLE_MAX];        // スティックの方向プレス情報
    bool abAngleTrigger[STICKTYPE_MAX][STICKANGLE_MAX];      // スティックの方向トリガー情報
    bool abAngleRepeat[STICKTYPE_MAX][STICKANGLE_MAX];       // スティックの方向リピート情報
    bool abAngleRelease[STICKTYPE_MAX][STICKANGLE_MAX];      // スティックの方向リリース情報
}STICKINPUT;


HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);

HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);
void UninitMouse(void);
void UpdateMouse(void);
bool GetMousePress(int nKey);
bool GetMouseTrigger(int nKey);
D3DXVECTOR3 GetMouseMove(void);
//void GetMouseState(HWND hWnd);


HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadTrigger(JOYKEY key);
bool GetJoypadPress(JOYKEY key);
bool GetJoypadRepeat(JOYKEY key);
XINPUT_STATE* GetXInputState(void);
void UpdateStick(void);
STICKINPUT GetStick(void);
float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos);
WORD GetJoypadStick(SHORT sThumbx, SHORT sThumby, SHORT sDeaZone);
#endif // _INPUT_H_ //定義されてなかったら

