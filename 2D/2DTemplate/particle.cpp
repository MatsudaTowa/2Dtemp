//=============================================
//
//2DTemplate[Particle.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "particle.h"
#include "input.h"
#include "camera.h"

//=============================================
//�}�N����`
//=============================================
#define MAX_PARTICLE (10000) //�G�t�F�N�g�̍ő吔
#define PARTICLE_LIFE	(1000000) //�G�t�F�N�g�̎���
#define MINUS_LIFESPAN	(1) //���C�t�̌��鐔
#define VERTEX	(4) //���_��

//�p�[�e�B�N���\����
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 move; //�ړ���
	D3DXCOLOR col; //�F
	float fRadius; //���a
	int nLife; //���C�t
	bool bUse; //�g�p����Ă��邩�̊m�F
}Particle;

//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL; //���_�o�b�t�@�ւ̃|�C���^
Particle g_aParticle[MAX_PARTICLE]; //�G�t�F�N�g�̏��

//=============================================
//�G�t�F�N�g�̏���������
//=============================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntParticle;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect.png",
		&g_pTextureParticle
	);

	//�G�t�F�N�g�̏�����
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].move = D3DXVECTOR3(10.0f,10.0f, 0.0f); //�ړ���
		g_aParticle[nCntParticle].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].fRadius = 0.0f;
		g_aParticle[nCntParticle].nLife = 0.0f;
		g_aParticle[nCntParticle].bUse = false; //�g�p���ĂȂ����
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PARTICLE, D3DUSAGE_WRITEONLY, 4, D3DPOOL_MANAGED, &g_pVtxBuffParticle, NULL);

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_aParticle[nCntParticle].col;
		pVtx[1].col = g_aParticle[nCntParticle].col;
		pVtx[2].col = g_aParticle[nCntParticle].col;
		pVtx[3].col = g_aParticle[nCntParticle].col;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += VERTEX; //���_�|�C���^��4�i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffParticle->Unlock();
}

//=============================================
//�G�t�F�N�g�̏I������
//=============================================
void UninitParticle(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}

//=============================================
//�G�t�F�N�g�̍X�V����
//=============================================
void UpdateParticle(void)
{
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾pp
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);
	int nCntParticle;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{

			if (g_aParticle[nCntParticle].nLife <= 0)
			{
				g_aParticle[nCntParticle].bUse = false;
			}

			D3DXVECTOR3 Vtx = ScreenConversion(g_aParticle[nCntParticle].pos);

			Vtx += g_aParticle[nCntParticle].move;

			pVtx[0].pos += g_aParticle[nCntParticle].move;
			pVtx[1].pos += g_aParticle[nCntParticle].move;
			pVtx[2].pos += g_aParticle[nCntParticle].move;
			pVtx[3].pos += g_aParticle[nCntParticle].move;

		}

		D3DXVECTOR3 Vtx = ScreenConversion(g_aParticle[nCntParticle].pos);

		//if (Vtx.x < 0
		//	|| Vtx.x >= SCREEN_WIDTH
		//	|| Vtx.y >= SCREEN_HEIGHT)
		//{
		//	g_aParticle[nCntParticle].bUse = false;
		//}
		pVtx += 4;
	}



	g_pVtxBuffParticle->Unlock();
}

//=============================================
//�G�t�F�N�g�̕`�揈��
//=============================================
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntParticle;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureParticle);
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{//�G�t�F�N�g���g�p����Ă�����
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				VERTEX * nCntParticle,
				2);
		}
	}

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================
//�G�t�F�N�g�̐ݒ菈��
//=============================================
void SetParticle(D3DXVECTOR3 pos,float fRadius, D3DXCOLOR col)
{
	int nCntParticle;
	float fVertex;
	float fMove;
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	fVertex = (float)(rand() % 629 - 314) / 100.0f;
	fMove = (float)(rand() % 120) / 20.0f + 10;


	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{//�G�t�F�N�g���g�p����ĂȂ��Ƃ�
			pVtx += (nCntParticle * VERTEX);
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].move.x = sinf(fVertex) * fMove;
			g_aParticle[nCntParticle].move.y = cosf(fVertex) * fMove;
			g_aParticle[nCntParticle].nLife = 20;
			g_aParticle[nCntParticle].fRadius = fRadius;
			g_aParticle[nCntParticle].col = col;
			g_aParticle[nCntParticle].bUse = true;

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aParticle[nCntParticle].col;
			pVtx[1].col = g_aParticle[nCntParticle].col;
			pVtx[2].col = g_aParticle[nCntParticle].col;
			pVtx[3].col = g_aParticle[nCntParticle].col;

			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aParticle[nCntParticle].pos.x - g_aParticle[nCntParticle].fRadius;
			pVtx[0].pos.y = g_aParticle[nCntParticle].pos.y - g_aParticle[nCntParticle].fRadius;
			pVtx[1].pos.x = g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fRadius;
			pVtx[1].pos.y = g_aParticle[nCntParticle].pos.y - g_aParticle[nCntParticle].fRadius;
			pVtx[2].pos.x = g_aParticle[nCntParticle].pos.x - g_aParticle[nCntParticle].fRadius;
			pVtx[2].pos.y = g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fRadius;
			pVtx[3].pos.x = g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fRadius;
			pVtx[3].pos.y = g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fRadius;

			break; //for�𔲂���
		}
	}
	
	g_pVtxBuffParticle->Unlock();
}
