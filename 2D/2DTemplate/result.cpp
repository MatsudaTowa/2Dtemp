//=============================================
//
//2DTemplate[result.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "result.h"
#include "input.h"
#include "player.h"
//#include "enemy.h"
#include "fade.h"
#include "sound.h"

//=============================================
//�}�N����`
//=============================================
#define NUM_RESULT (1) //���U���g�̎��
#define PLUS_POINTER	(4) //�|�C���^��i�߂鐔
#define MAX_DIGIT	(6) //�ő包��
#define VERTEX	(4) //���_��
//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3DTEXTURE9 g_apTextureResult[NUM_RESULT] = {}; //�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL; //���_�o�b�t�@�̃|�C���^
int g_Result; //0:BG,1:�X�R�A
//=============================================
//���U���g��ʂ̏���������
//=============================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	Player* pPlayer = GetPlayer();

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	if (pPlayer->bUse == false)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\GAMEOVER.png",
			&g_apTextureResult[0]
		);


		////�e�N�X�`���̓ǂݍ���
		//D3DXCreateTextureFromFile(pDevice,
		//	"data\\TEXTURE\\gameoverwhite.png",
		//	&g_apTextureResult[1]
		//);

	}

	else
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\result.png",
			&g_apTextureResult[0]
		);

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\Number.png",
			&g_apTextureResult[1]
		);


		////�e�N�X�`���̓ǂݍ���
		//D3DXCreateTextureFromFile(pDevice,
		//	"data\\TEXTURE\\GAMECLEAR.png",
		//	&g_apTextureResult[1]
		//);
	}







	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_RESULT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffResult, NULL);

	VERTEX_2D* pVtx;
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);


	////���_���W�̐ݒ�
	//pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	//pVtx[6].pos = D3DXVECTOR3(0.0f, 620.0f, 0.0f);
	//pVtx[7].pos = D3DXVECTOR3(1280.0f, 620.0f, 0.0f);

	for (int nCntResult = 0; nCntResult < NUM_RESULT; nCntResult++)
	{
		if (nCntResult == 0)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}
		if (nCntResult == 1)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(20.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 40.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(20.0f, 40.0f, 0.0f);
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
	g_pVtxBuffResult->Unlock();
}

//=============================================
//���U���g��ʂ̏I������
//=============================================
void UninitResult(void)
{

	Player* pPlayer = GetPlayer();

	for (int nCntResult = 0; nCntResult < NUM_RESULT; nCntResult++)
	{

		if (g_apTextureResult[nCntResult] != NULL)
		{
			g_apTextureResult[nCntResult]->Release();
			g_apTextureResult[nCntResult] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
	StopSound();
}

//=============================================
//���U���g��ʂ̍X�V����
//=============================================
void UpdateResult(void)
{
	Player* pPlayer = GetPlayer();

	if (pPlayer->bUse == false)
	{
		float fGetColorFade = FadeColor();
		if ((GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true) && fGetColorFade <= 0.0f)
		{//����L�[�������ꂽ
			//���j���[�Ɉڍs
			//PlaySound(SOUND_LABEL_SE_DECISION);
			SetFade(MODE_TITLE);
		}
	}
	else
	{
		float fGetColorFade = FadeColor();

		if ((GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true) && fGetColorFade <= 0.0f)
		{//����L�[�������ꂽ
			//���j���[�Ɉڍs
			//PlaySound(SOUND_LABEL_SE_DECISION);
			SetFade(MODE_TITLE);
		}
	}
}

//=============================================
//���U���g��ʂ̕`�揈��
//=============================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	Player* pPlayer = GetPlayer();

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntResult = 0; nCntResult < NUM_RESULT; nCntResult++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureResult[nCntResult]);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			VERTEX * nCntResult,
			2);
	}
}
