//=============================================
//
//2DTemplate[Screen.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "player.h"
#include "Screen.h"

//=============================================
//�}�N����`
//=============================================
#define NUM_SCREEN (1) //�w�i�̎��
#define PLUS_POINTER	(4) //�|�C���^��i�߂鐔
#define VERTEX	(4) //���_��
#define MOVE_V_TEXTURE1	(0.005f) //�ꖇ�ڂ̔w�i��U���W�X�V
#define MOVE_V_TEXTURE2	(0.007f) //�񖇖ڂ̔w�i��U���W�X�V
#define MOVE_V_TEXTURE3	(0.001f) //�O���ڂ̔w�i��U���W�X�V

//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3DTEXTURE9 g_apTextureScreen = NULL; //�e�N�X�`��(3��)�|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScreen = NULL; //���_�o�b�t�@�̃|�C���^
float g_aPosTexV; //�e�N�X�`�����W�̊J�n�ʒu(V�l)

//=============================================
//�|���S���̏���������
//=============================================
void InitScreen(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScreen;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\IMG_5603.JPG",
		&g_apTextureScreen
	);


	//�e�N�X�`�����W�̊J�n�ʒu(V�l)�̏�����

	g_aPosTexV = 0.0f;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SCREEN, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffScreen, NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffScreen->Lock(0, 0, (void**)&pVtx, 0);

	//for (nCntScreen = 0; nCntScreen < NUM_SCREEN; nCntScreen++)
	//{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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

		//�e�N�X�`���̍��W�w��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f ,1.0f);

		//pVtx += PLUS_POINTER; //���_�|�C���^��4�i�߂�

	//}
	g_pVtxBuffScreen->Unlock();
}

//=============================================
//�|���S���̏I������
//=============================================
void UninitScreen(void)
{
	//�e�N�X�`���̔j��

		
	if (g_apTextureScreen != NULL)
	{

		g_apTextureScreen->Release();
		g_apTextureScreen = NULL;
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScreen != NULL)
	{
		g_pVtxBuffScreen->Release();
		g_pVtxBuffScreen = NULL;
	}
}

//=============================================
//�|���S���̍X�V����
//=============================================
void UpdateScreen(void)
{
}

//=============================================
//�|���S���̕`�揈��
//=============================================
void DrawScreen(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScreen;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScreen, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureScreen);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			2);

}

//=============================================
//�e�N�X�`�����W�X�V
//=============================================
void ScreenTexMove(D3DXVECTOR2 tex)
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffScreen->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W�w��
	pVtx[0].tex += tex;
	pVtx[1].tex += tex;
	pVtx[2].tex += tex;
	pVtx[3].tex += tex;

	g_pVtxBuffScreen->Unlock();

}
