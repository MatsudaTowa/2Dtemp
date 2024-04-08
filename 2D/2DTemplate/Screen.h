//=============================================
//
//2DTemplate[Screen.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _SCREEN_H_ //定義されてなかったら
#define _SCREEN_H_ //２種インクルード防止

void InitScreen(void);
void UninitScreen(void);
void UpdateScreen(void);
void DrawScreen(void);
void ScreenTexMove(D3DXVECTOR2 tex);

#endif // _SCREEN_H_ //定義されてなかったら
