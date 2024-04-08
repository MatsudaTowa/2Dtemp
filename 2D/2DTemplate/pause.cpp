//=============================================
//
//2DTemplate[Pause.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "pause.h"
#include "result.h"
#include "input.h"
#include "sound.h"

//=============================================
//�}�N����`
//=============================================
#define NUM_PAUSE (5) //���j���[�̎��
#define PLUS_POINTER	(4) //�|�C���^��i�߂鐔
#define VERTEX	(4) //���_��
#define START_FONT_POS	(1000.0f) //�X�R�A��10���ڂ̃|�W�V����
#define START_PLUS_POS	(20.0f) //�X�R�A��10���ڂ̃|�W�V�����ɑ����l
#define START_NUMBER	(0.0f) //�e�N�X�`���̉摜�̍��W�̃X�^�[�g�l
//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3DTEXTURE9 g_apTexturePause[NUM_PAUSE] = {}; //�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL; //���_�o�b�t�@�̃|�C���^
int g_nPauseSelect = 0;
//=============================================
//���j���[��ʂ̏���������
//=============================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntPause;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\PAUSE.png",
		&g_apTexturePause[1]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Continue.png",
		&g_apTexturePause[2]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RETRY.png",
		&g_apTexturePause[3]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\QUIT.png",
		&g_apTexturePause[4]
	);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PAUSE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPause, NULL);

	VERTEX_2D* pVtx;
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	g_nPauseSelect = 0;

	for (int nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		if (nCntPause == 0)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}
		else if (nCntPause == 1)
		{
			pVtx[0].pos = D3DXVECTOR3(120.0f, 80.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1120.0f, 80.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(120.0f, 580.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1120.0f, 580.0f, 0.0f);
		}
		else if (nCntPause == 2)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(475.0f, 170.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(740.0f, 170.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(475.0f, 320.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(740.0f, 320.0f, 0.0f);
		}
		else if (nCntPause == 3)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(475.0f, 270.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(740.0f, 270.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(475.0f, 420.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(740.0f, 420.0f, 0.0f);
		}
		else if (nCntPause == 4)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(475.0f, 370.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(740.0f, 370.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(475.0f, 520.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(740.0f, 520.0f, 0.0f);
		}
	
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`���̍��W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += PLUS_POINTER; //���_�|�C���^��4�i�߂�
	}
	g_pVtxBuffPause->Unlock();
	//PlaySound(SOUND_LABEL_BGM000);
}

//=============================================
//���j���[��ʂ̏I������
//=============================================
void UninitPause(void)
{
	//�T�E���h�̒�~
	//StopSound();

	for (int nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{

		if (g_apTexturePause[nCntPause] != NULL)
		{
			g_apTexturePause[nCntPause]->Release();
			g_apTexturePause[nCntPause] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//=============================================
//���j���[��ʂ̍X�V����
//=============================================
void UpdatePause(void)
{
	VERTEX_2D* pVtx;

	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	

	if (GetKeyboardTrigger(DIK_DOWN) == true|| GetJoypadTrigger(JOYKEY_DOWN) == true)
	{//���L�[�������ꂽ
		g_nPauseSelect++;
		if (g_nPauseSelect > 2)
		{
			g_nPauseSelect = 0;
		}

	}
	if (GetKeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP) == true)
	{//���L�[�������ꂽ
		g_nPauseSelect--;
		if (g_nPauseSelect < 0)
		{
			g_nPauseSelect = 2;
		}

	}

	for (int nCnt = 0; nCnt < NUM_PAUSE; nCnt++)
	{
		if (g_nPauseSelect == 0)
		{
			if (nCnt == 0)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 150);
				pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 150);
				pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 150);
				pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 150);
			}
			else if (nCnt == 1)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			else if (nCnt == 2)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(150, 150, 250, 255);
				pVtx[1].col = D3DCOLOR_RGBA(150, 150, 250, 255);
				pVtx[2].col = D3DCOLOR_RGBA(150, 150, 250, 255);
				pVtx[3].col = D3DCOLOR_RGBA(150, 150, 250, 255);
			}
			else if (nCnt == 3)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			}
			else if (nCnt == 4)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
		}
		else if (g_nPauseSelect == 1)
		{
			if (nCnt == 0)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 150);
				pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 150);
				pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 150);
				pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 150);
			}
			else if (nCnt == 1)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			else if (nCnt == 2)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			}
			else if (nCnt == 3)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(150, 150, 250, 255);
				pVtx[1].col = D3DCOLOR_RGBA(150, 150, 250, 255);
				pVtx[2].col = D3DCOLOR_RGBA(150, 150, 250, 255);
				pVtx[3].col = D3DCOLOR_RGBA(150, 150, 250, 255);

			}
			else if (nCnt == 4)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}

		}
		else if (g_nPauseSelect == 2)
		{
			//���_�J���[�̐ݒ�
			if (nCnt == 0)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 150);
				pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 150);
				pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 150);
				pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 150);
			}
			else if (nCnt == 1)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			else if (nCnt == 2)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			}
			else if (nCnt == 3)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			}
			else if (nCnt == 4)
			{

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(150, 150, 250, 255);
				pVtx[1].col = D3DCOLOR_RGBA(150, 150, 250, 255);
				pVtx[2].col = D3DCOLOR_RGBA(150, 150, 250, 255);
				pVtx[3].col = D3DCOLOR_RGBA(150, 150, 250, 255);
			}
		}		

		pVtx += VERTEX;
	}
	g_pVtxBuffPause->Unlock();
}

//=============================================
//���j���[��ʂ̕`�揈��
//=============================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScreen;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturePause[nCntPause]);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			VERTEX * nCntPause,
			2);
	}
}


//=============================================
//���I������Ă�I�����̎擾
//=============================================
int GetNumPause(void)
{
	return g_nPauseSelect;
}