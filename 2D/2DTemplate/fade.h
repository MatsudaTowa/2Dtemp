#ifndef  _FADE_H_
#define _FADE_H_

#include "main.h"

//フェードの状態
typedef enum
{
	FADE_NONE = 0, //何もしていない状態
	FADE_IN, //フェードイン
	FADE_OUT, //フェードアウト
	FADE_MAX,
}FADE;

//プロトタイプ宣言
void InitFade(void);
void UninitFade(void);
void UpdateFade();
void DrawFade(void);
void SetFade(MODE modeNext);

FADE GetFade(void);
float FadeColor(void);
//float GetColorFade(void);
#endif // ! _Fade_H_

