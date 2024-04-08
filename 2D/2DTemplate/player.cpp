//=============================================
//
//2DTemplate[player.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "Screen.h"
#include "sound.h"

//=============================================
//�}�N����`
//=============================================
#define DEFAULT_SPEED	(1.0f) //�ʏ펞�̃X�s�[�h
#define DEFAULT_TURN	(0.1f) //�ʏ펞�̉�]�X�s�[�h
#define MAX_TURN	(0.15f) //�ʏ펞�̉�]�X�s�[�h
#define DAMPING_COEFFICIENT	(0.2f) //��R��
#define DAMPING_SLIP_COEFFICIENT	(0.1f) //�X�̒�R��
#define REPULSIVE_FORCE	(0.6f) //������
#define SPAWN_X	(100.0f) //�X�|�[������X���W
#define PLAYER_MOVE_HEIGHT	(590.0f) //�v���C���[�̈ړ��ł��鍂��
#define JUMP	(-22.0f) //�W�����v��
#define GRAVITY (0.8f) //�d�͂̒l
#define MAX_GRAVITY (20.0f) //�d�͂̍ő�l
#define DEFAULT_MAGNIFICATION	(1.0f) //�ʏ펞�̔{��
#define TEXTURE_MOVE (0.01f) //�e�N�X�`���[���[�u�l
//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL; //�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;
Player g_Player;
float g_fMagnification = DEFAULT_MAGNIFICATION;
float g_PlayerTexU; //�e�N�X�`���[��U���W
float g_PlayerTexV; //�e�N�X�`���[��V���W
int g_nPressCnt = 0;
int g_nJumpCnt;
int g_nBlizzardCnt; //�X���[����
int g_nLavaCnt; //�R�Ď���
int g_nFlyCnt; //���V����
bool g_bJump; //�W�����v���Ă邩�ǂ����̔���
bool g_bIslanding; //���n���Ă邩
bool g_bFly; //���V

//=============================================
//�|���S���̏���������
//=============================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;


	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Player.fLength = sqrtf(PLAYER_WIDE / 2.0f * PLAYER_WIDE / 2.0f + PLAYER_HEIGHT *2.0f * PLAYER_HEIGHT );
	g_Player.fAngle = atan2f(PLAYER_WIDE, PLAYER_HEIGHT);
	g_Player.Size = D3DXVECTOR2(PLAYER_WIDE/ 2.0f, PLAYER_HEIGHT);
	g_Player.oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�v���C���[�̑O�̈ʒu
	g_Player.pos = D3DXVECTOR3(SPAWN_X,1350.0f, 0.0f); //�v���C���[�̏����ʒu
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̈ړ����x
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̌���
	g_Player.bDirection = true;
	g_Player.State = PLAYERSTATE_NORMAL;
	g_Player.oldState = PLAYERSTATE_NORMAL;
	g_Player.bUse = true;
	g_Player.nAnimCnt = 0.0f;
	g_nJumpCnt = 0;
	g_nBlizzardCnt = 0;
	g_nLavaCnt = 0;
	g_nFlyCnt = 0;
	g_bJump = false;
	g_bIslanding = true;
	g_bFly = false;
	g_PlayerTexU = 0.0f;
	g_PlayerTexV = 0.0f;
	//g_bDirection = true; //�����̔���

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\mymelo.jpg",
		&g_pTexturePlayer
	);


	int nCntState = 0; //�_���[�W�^�C��

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)* 4, D3DUSAGE_WRITEONLY, 4, D3DPOOL_MANAGED, &g_pVtxBuffPlayer, NULL);

	D3DXVECTOR3 Vtx = ScreenConversion(g_Player.pos);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0,(void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_Player.pos.x - g_Player.Size.x;
	pVtx[0].pos.y = g_Player.pos.y - g_Player.Size.y;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Player.pos.x + g_Player.Size.x;
	pVtx[1].pos.y = g_Player.pos.y - g_Player.Size.y;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Player.pos.x - g_Player.Size.x;
	pVtx[2].pos.y = g_Player.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Player.pos.x + g_Player.Size.x;
	pVtx[3].pos.y = g_Player.pos.y;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f,1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f,1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f,1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f,1.0f, 1.0f);

	//�e�N�X�`���̍��W�w��
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffPlayer->Unlock();
	
}

//=============================================
//�|���S���̏I������
//=============================================
void UninitPlayer(void)
{
	if (g_Player.bUse == false)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturePlayer != NULL)
		{
			g_pTexturePlayer->Release();
			g_pTexturePlayer = NULL;
		}

		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffPlayer != NULL)
		{
			g_pVtxBuffPlayer->Release();
			g_pVtxBuffPlayer = NULL;
		}
	}
}

//=============================================
//�|���S���̍X�V����
//=============================================
void UpdatePlayer(void)
{
	D3DXVECTOR3 Vtx = ScreenConversion(g_Player.pos);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	 
	if (g_Player.bUse == true)
	{
		D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);
		if (GetKeyboardPress(DIK_W) || GetJoypadPress(JOYKEY_UP))
		{ // ��B
			vecDirection.y -= 1.0f;
			ScreenTexMove(D3DXVECTOR2(0.0f,-0.01f));
		}
		if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_LEFT))
		{
			vecDirection.x -= 1.0f;
			ScreenTexMove(D3DXVECTOR2(-0.01f, 0.0f));

		}
		if (GetKeyboardPress(DIK_D) || GetJoypadPress(JOYKEY_RIGHT))
		{
			vecDirection.x += 1.0f;
			ScreenTexMove(D3DXVECTOR2(0.01f, 0.0f));
		}
		if (GetKeyboardPress(DIK_S) || GetJoypadPress(JOYKEY_DOWN))
		{
			vecDirection.y += 1.0f;
			ScreenTexMove(D3DXVECTOR2(0.0f, 0.01f));

		}

		if (vecDirection.x == 0.0f && vecDirection.y == 0.0f)
		{ // �����ĂȂ��B
			g_Player.move.x = 0.0f;
			g_Player.move.y = 0.0f;
		}
		else
		{
			float rotMoveY = atan2f(vecDirection.x, vecDirection.y);

			g_Player.move.x += sinf(rotMoveY) * DEFAULT_SPEED;
			g_Player.move.y += cosf(rotMoveY) * DEFAULT_SPEED;
			g_Player.rot.x = rotMoveY + D3DX_PI;
			//if (g_Player.rot.y <= -D3DX_PI)
			//{
			//	g_Player.rot.y = D3DX_PI;
			//}
		
		}

		g_Player.oldpos = g_Player.pos;

		g_Player.pos += g_Player.move;

		//�ړ��ʂ��X�V(�����j

		g_Player.move *= 1.0f - DAMPING_COEFFICIENT;

		D3DXVECTOR3 Vtx = ScreenConversion(g_Player.pos);


		pVtx[0].pos.x = Vtx.x - g_Player.Size.x;
		pVtx[0].pos.y = Vtx.y - g_Player.Size.y;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = Vtx.x + g_Player.Size.x;
		pVtx[1].pos.y = Vtx.y - g_Player.Size.y;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = Vtx.x - g_Player.Size.x;
		pVtx[2].pos.y = Vtx.y;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = Vtx.x + g_Player.Size.x;
		pVtx[3].pos.y = Vtx.y;
		pVtx[3].pos.z = 0.0f;

		//�e�N�X�`���̍��W�w��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);		
		
	}
	g_pVtxBuffPlayer->Unlock();
}

//=============================================
//�|���S���̕`�揈��
//=============================================
void DrawPlayer(void)
{
	if (g_Player.bUse == true)
	{
		LPDIRECT3DDEVICE9 pDevice;

		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);

		//�e�N�X�`���g�厞�ɐF���ߎ��l�ɂ���
		pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//�e�N�X�`���g�厞�̐F����`���
		pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	}
	DebugPlayerPos();
}

void DebugPlayerPos(void)
{
	LPD3DXFONT pFont = GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];


	//������ɑ��
	sprintf
	(&aStr[0],
		"\n\n\n\n\nPlayer pos[%.1f,%.1f,%.1f]\n"
		, g_Player.pos.x,g_Player.pos.y,g_Player.pos.z);

	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=============================================
//�v���C���[�̃q�b�g����
//=============================================
void HitPlayer(int nDamage)
{
	//if (g_Player.State != PLAYERSTATE_DAMAGE)
	//{

	//	g_Player.oldState = g_Player.State;
	//	VERTEX_2D* pVtx;
	//	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	//	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//	g_Player.nLife -= nDamage;
	//	if (g_Player.nLife <= 0)
	//	{
	//		//g_nScoreCnt++;
	//		//SetExplosion(g_Player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EXPLSIONTYPE_NORMAL);
	//		g_Player.bUse = false;
	//	}
	//	else
	//	{
	//		g_Player.State = PLAYERSTATE_DAMAGE;
	//		g_Player.nCntState = DAMAGE_TIME;
	//		//���_�J���[�̐ݒ�
	//		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	//		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	//		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	//		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	//	}
	//	g_pVtxBuffPlayer->Unlock();
	//}
	//PlaySound(SOUND_LABEL_SE_DAMAGE);
}

//=============================================
//�v���C���[�̎擾
//=============================================
Player* GetPlayer(void)
{
	return &g_Player;
}

//bool GetBarrierUsed(void)
//{
//	return g_bBarrierUsed;
//}