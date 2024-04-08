//=============================================
//
//2DTemplate[camera.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "camera.h"
#include "input.h"
//#include "sound.h"
#include "fade.h"
//=============================================
//�}�N����`
//=============================================
#define PLUS_POINTER	(4) //�|�C���^��i�߂鐔
#define VERTEX	(4) //���_��
#define START_NUMBER	(0.0f) //�e�N�X�`���̉摜�̍��W�̃X�^�[�g�l
#define DAMPING_COEFFICIENT	(0.2f) //��R��

//#define ANIMATION_PATTERN	(8) //�A�j���[�V�����p�^�[����

//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3DTEXTURE9 g_pTexturecamera = NULL; //�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffcamera = NULL; //���_�o�b�t�@�̃|�C���^
//FADE fadecamera;
D3DXVECTOR3 g_CameraPos;
D3DXVECTOR3 g_CameraOldPos;

//=============================================
//�J�����̏���������
//=============================================
void InitCamera(void)
{
	//LPDIRECT3DDEVICE9 pDevice;
	//int nCntcamera;
	////�f�o�C�X�̎擾
	//pDevice = GetDevice();

	g_CameraPos = D3DXVECTOR3(WORLD_WIDTH * 0.5f, WORLD_HEIGHT * 0.5f, 0.0f);
	g_CameraOldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//PlaySound(SOUND_LABEL_BGM000);
}

//=============================================
//�X�N���[���ϊ�
//=============================================
D3DXVECTOR3 ScreenConversion(D3DXVECTOR3 pos)
{

	g_CameraOldPos = g_CameraPos;

	//�J�������W���X�N���[���̌��_�ɕϊ�
	D3DXVECTOR3 ScreenOriginPos = D3DXVECTOR3 (g_CameraOldPos.x - SCREEN_WIDTH / 2, g_CameraOldPos.y - SCREEN_HEIGHT / 2 , 1.0f);

	//���[���h���W����Ώۂ̂΂���ɕϊ�����
	D3DXVECTOR3 ScreenPos = D3DXVECTOR3(pos.x - ScreenOriginPos.x, pos.y - ScreenOriginPos.y , 1.0f);

	return ScreenPos;
}

//=============================================
//�J�����̏I������
//=============================================
void UninitCamera(void)
{
	//�T�E���h�̒�~
	//StopSound();

	
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffcamera != NULL)
	{
		g_pVtxBuffcamera->Release();
		g_pVtxBuffcamera = NULL;
	}
}

//=============================================
//�J�����̍X�V����
//=============================================
void UpdateCamera(D3DXVECTOR3 pos)
{

	g_CameraOldPos = g_CameraPos;

	g_CameraPos = pos;

	//X���̃X�e�[�W�̔���
	if (g_CameraOldPos.x - SCREEN_WIDTH * 0.5f <= 0.0f)
	{
		g_CameraPos.x = SCREEN_WIDTH * 0.5f;
	}
	if (g_CameraOldPos.x + SCREEN_WIDTH * 0.5f >= WORLD_WIDTH)
	{
		g_CameraPos.x = WORLD_WIDTH - SCREEN_WIDTH * 0.5f;
	}

	////Y���̃X�e�[�W�̔���
	//if (g_CameraPos.y - SCREEN_HEIGHT * 0.5f <= 0.0f)
	//{
	//	g_CameraPos.y = SCREEN_HEIGHT * 0.5f;
	//}
	if (g_CameraPos.y + SCREEN_HEIGHT * 0.5f >= WORLD_HEIGHT)
	{
		g_CameraPos.y = WORLD_HEIGHT - SCREEN_HEIGHT * 0.5f;
	}
}

////=============================================
////�J�����̕`�揈��
////=============================================
//void DrawCamera(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	pDevice->SetStreamSource(0, g_pVtxBuffcamera, 0, sizeof(VERTEX_2D));
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//�|���S���̕`��
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
//		0,
//		2);
//	
//}
