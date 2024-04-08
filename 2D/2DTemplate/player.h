//=============================================
//
//2DTemplate[player.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_H_ //��`����ĂȂ�������
#define _PLAYER_H_ //�Q��C���N���[�h�h�~

//�}�N��
#define PLAYER_WIDE	(50.0f) //�v���C���[�̉���
#define PLAYER_HEIGHT	(50.0f) //�v���C���[�̍���

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_NORMAL = 0, //�ʏ���
	PLAYERSTATE_DAMAGE,	//�_���[�W���
	PLAYERSTATE_JUMP, //�W�����v���
	PLAYERSTATE_SWORD, //�U���i���j
	PLAYERSTATE_FIRE, //��
	PLAYERSTATE_WING, //�H
	PLAYERSTATE_INVINCIBLE, //���G�^�C��
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�v���C���[�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 oldpos; //�O��̈ʒu
	D3DXVECTOR3 rot; //����
	D3DXVECTOR3 move; //�ړ���
	D3DXVECTOR3 moveTurn; //��]��
	D3DXVECTOR2 Size; 
	PLAYERSTATE  State; //���
	PLAYERSTATE  oldState; //���
	float fLength; //�Ίp���̒���
	float fAngle; //�Ίp���̊p�x
	int nAnimCnt; //�A�j���[�V�����J�E���g
	bool bDirection; //����(true:�E,false:��)
	int nLife; //HP	
	bool bUse; //�g���Ă��邩
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void DebugPlayerPos(void);
void HitPlayer(int nDamage);
LPDIRECT3DDEVICE9 GetDevice(void);
Player* GetPlayer(void);


#endif // _POLYGON_H_ //��`����ĂȂ�������

