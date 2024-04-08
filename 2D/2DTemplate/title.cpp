//=============================================
//
//2DTemplate[title.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
//=============================================
//�}�N����`
//=============================================
#define NUM_TITLE (2) //�^�C�g���̎��
#define PLUS_POINTER	(4) //�|�C���^��i�߂鐔
#define VERTEX	(4) //���_��
#define START_FONT_POS	(1000.0f) //�X�R�A��10���ڂ̃|�W�V����
#define START_PLUS_POS	(20.0f) //�X�R�A��10���ڂ̃|�W�V�����ɑ����l
#define START_NUMBER	(0.0f) //�e�N�X�`���̉摜�̍��W�̃X�^�[�g�l
#define Tutorial	(200)
#define ANIMATION_CNT	(10) //�A�j���[�V�����J�E���g��
//#define ANIMATION_PATTERN	(8) //�A�j���[�V�����p�^�[����

//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3DTEXTURE9 g_apTextureTitle[NUM_TITLE] = {}; //�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL; //���_�o�b�t�@�̃|�C���^
float g_fY = START_FONT_POS; //�����̕\������X���W
int nCntAnim = 0; //�A�j���[�V�����J�E���g
int nPatternAnim = 0; //�A�j���[�V�����p�^�[��
//FADE fadetitle;
float g_fTitleFlash;
float g_fTitleAlpha; //���l
int g_nCntTime;
int g_TitleType;
//=============================================
//�^�C�g����ʂ̏���������
//=============================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTitle;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title.png",
		&g_apTextureTitle[0]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\start.png",
		&g_apTextureTitle[1]
	);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TITLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL);

	VERTEX_2D* pVtx;
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	g_fTitleAlpha = 0.2f;

	g_fTitleFlash = 0.02f;

	g_nCntTime = 0;

	g_TitleType = 0;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++,g_TitleType++)
	{
		if (g_TitleType == 0)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}
		else if (g_TitleType == 1)
		{
			pVtx[0].pos = D3DXVECTOR3(400.0f, 500.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(800.0f, 500.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(400.0f, 750.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(800.0f, 750.0f, 0.0f);
		}

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);

		//�e�N�X�`���̍��W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += PLUS_POINTER; //���_�|�C���^��4�i�߂�
	}
	g_pVtxBuffTitle->Unlock();
	//PlaySound(SOUND_LABEL_BGM_TITLE);
}

//=============================================
//�^�C�g����ʂ̏I������
//=============================================
void UninitTitle(void)
{
	//�T�E���h�̒�~
	StopSound();

	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{

		if (g_apTextureTitle[nCntTitle] != NULL)
		{
			g_apTextureTitle[nCntTitle]->Release();
			g_apTextureTitle[nCntTitle] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//=============================================
//�^�C�g����ʂ̍X�V����
//=============================================
void UpdateTitle(void)
{
	g_TitleType = 0;
	float fGetColorFade = FadeColor();
	if ((GetKeyboardTrigger(DIK_RETURN) == true 
		|| GetJoypadTrigger(JOYKEY_START) == true
		|| GetJoypadTrigger(JOYKEY_A) == true)
		&& fGetColorFade <= 0.0f)
	{//����L�[�������ꂽ
	  //�Q�[���Ɉڍs
		SetFade(MODE_TUTORIAL);
	}

	VERTEX_2D* pVtx;
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
		
	if (g_fTitleAlpha >= 1.0f || g_fTitleAlpha <= 0.0f)
		{
			g_fTitleFlash *= -1.0f;
		}
	g_fTitleAlpha += g_fTitleFlash;

	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++, g_TitleType++)
	{

		if (g_TitleType == 1)
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fTitleAlpha);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fTitleAlpha);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fTitleAlpha);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fTitleAlpha);
		}

		pVtx += PLUS_POINTER; //���_�|�C���^��4�i�߂�
	}

	//int nAnswer = g_nCntTime / NEXT;

	//if (nAnswer == 1)
	//{
	//	SetMode(MODE_TUTORIAL);
	//}
}

//=============================================
//�^�C�g����ʂ̕`�揈��
//=============================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureTitle[nCntTitle]);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			VERTEX * nCntTitle,
			2);
	}
}
