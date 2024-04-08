//=============================================
//
//2DTemplate[pause.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PAUSE_H
#define _PAUSE_H

#include "main.h"
//�|�[�Y���j���[
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,
	PAUSE_MENU_RETRY,
	PAUSE_MENU_QUIT,
	PAUSE_MENU_MAX,
}PAUSEMENU;

//�v���g�^�C�v�錾
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
int GetNumPause(void);
#endif // !_PAUSE_H
