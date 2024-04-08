//=============================================
//
//2DTemplate[camera.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _CAMERA_H
#define _CAMERA_H

#include "main.h"

//プロトタイプ宣言
void InitCamera(void);
D3DXVECTOR3 ScreenConversion(D3DXVECTOR3 pos);
void UninitCamera(void);
void UpdateCamera(D3DXVECTOR3 pos);
//FADE GetFadecamera(void);
#endif // !_CAMERA_H