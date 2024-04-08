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
//�\�z�̂̒�`
//=============================================
typedef struct
{
	int nType; //���
	D3DXVECTOR3 pos; //���S
	int nSpawn; //�X�|�[������t���[��
	bool bUse; //�g�p����Ă��邩
}EnemyInfo;

typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	int nType; //���
	bool bUse; //�g�p���Ă邩�ǂ���
}BlockInfo;

//�v���g�^�C�v�錾
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void LoadEnemy(void);
void LoadBlock(void);
bool GetEdit(void);
#endif // !_GAME_H

