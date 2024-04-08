#ifndef  _FADE_H_
#define _FADE_H_

#include "main.h"

//�t�F�[�h�̏��
typedef enum
{
	FADE_NONE = 0, //�������Ă��Ȃ����
	FADE_IN, //�t�F�[�h�C��
	FADE_OUT, //�t�F�[�h�A�E�g
	FADE_MAX,
}FADE;

//�v���g�^�C�v�錾
void InitFade(void);
void UninitFade(void);
void UpdateFade();
void DrawFade(void);
void SetFade(MODE modeNext);

FADE GetFade(void);
float FadeColor(void);
//float GetColorFade(void);
#endif // ! _Fade_H_
