//=============================================
//
//2DTemplate[game.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "particle.h"
#include "pause.h"
#include "Screen.h"
#include "game.h"
#include "time.h"
#include "fade.h"
#include "time.h"

#include "sound.h"

//=============================================
//�}�N����`
//=============================================
#define TXT_MAX	(256) //�����̍ő吔
#define SPAWN_ENEMY	(3) //�X�|�[����
#define WAVE	(6) //�E�F�[�u��

//�O���[�o���ϐ�
bool g_bPause = false; //�|�[�Y���ǂ���
bool g_bEdit = false; //�G�f�B�b�g���[�h���ǂ���
int g_nUseEnemy = 0; //�G�̎g�p��
int g_nUseBlock = 0; //�u���b�N�̎g�p��
int g_MaxReadNum = 0;
int g_nWave = 0;
int nFrame = 0;
int g_FinishCnt;
int g_Spawn = TIME;
EnemyInfo g_EnemyInfo[MAX_ENEMY];
Player* pPlayer = GetPlayer();

//=============================================
//�Q�[���̏���������
//=============================================
void InitGame(void)
{
	g_nWave = 0;
	g_nUseEnemy = 0;
	g_FinishCnt = 0;
	//�J�����̏�����
	InitCamera();
	
	//�X�N���[���̏���������
	InitScreen();

	////�p�[�e�B�N���̏���������
	//InitParticle();

	//�|���S���̏���������
	InitPlayer();

	InitParticle();


	g_bPause = false; //�|�[�Y����
	g_bEdit = false;

	//if (g_bPause == true)
	//{//�|�[�Y���Ă���
		InitPause();
	//}



}

//=============================================
//�Q�[���̏I������
//=============================================
void UninitGame(void)
{
	//�X�N���[���̏I������
	UninitScreen();

	//�p�[�e�B�N���̏I������
	UninitParticle();

	//�|���S���̏I������
	UninitPlayer();

	////UI�w�i�̏I������
	//UninitUIzone();


	if (g_bPause == true)
	{//�|�[�Y���Ă���
	//�|�[�Y�̏I��
	UninitPause();
	}

	//�J�����̏I������
	UninitCamera();

	StopSound();
}

//=============================================
//�Q�[���̍X�V����
//=============================================
void UpdateGame(void)
{
	float fGetColorFade = FadeColor();
	int nGetNumPause = GetNumPause();
	//int nGetNumEnemy = GetNumEnemy();
	//Enemy* pEnemy = GetEnemy();
	//D3DXVECTOR3 EditCameraPos = GetEditCameraPos();

	if ((GetKeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true) && pPlayer->bUse ==true)
	{//�|�[�Y�������ꂽ
		if (g_bPause == false)
		{
			//PlaySound(SOUND_LABEL_SE_PAUSE);
		}
		g_bPause = g_bPause ? false : true;
	}
	if (g_bPause == true)
	{
		UpdatePause();
		if ((GetKeyboardTrigger(DIK_RETURN) == true 
			|| GetJoypadTrigger(JOYKEY_A) == true) 
			&& nGetNumPause == 0 
			&& fGetColorFade <= 0.0f)
		{//����L�[�������ꂽ
			g_bPause = false;
		}
		if ((GetKeyboardTrigger(DIK_RETURN) == true 
			|| GetJoypadTrigger(JOYKEY_A) == true) 
			&& nGetNumPause == 1
			&&  fGetColorFade <= 0.0f)
		{//����L�[�������ꂽ
			SetFade(MODE_GAME);
		}
		else if ((GetKeyboardTrigger(DIK_RETURN) == true 
			|| GetJoypadTrigger(JOYKEY_A) == true) 
			&& nGetNumPause == 2 
			&& fGetColorFade <= 0.0f)
		{//����L�[�������ꂽ
			SetFade(MODE_TITLE);
		}
	}


	if (g_bPause == false)
	{
		#ifdef _DEBUG
		if (GetKeyboardTrigger(DIK_F1) == true)
		{
			g_bEdit = g_bEdit ? false : true;
		}
		if (GetKeyboardTrigger(DIK_F2) == true)
		{
			g_bEdit = g_bEdit ? false : true;
		}
		#endif

		if (g_bEdit == true)
		{
			//UpdateCamera(pEditBlockInfo->pos);
		}
	}


	if (g_bPause == false && g_bEdit == false)
	{//�|�[�Y���ĂȂ�������
		//�X�N���[���̍X�V����
		UpdateScreen();


		UpdateCamera(pPlayer->pos);

		//�p�[�e�B�N���̍X�V����
		UpdateParticle();


		////�z�[�~���O�̍X�V����
		//UpdateHoming();

		////�����`���[�̍X�V����
		//Updatelauncher();

		//�v���C���[�̍X�V����
		UpdatePlayer();

		////�o���A�̍X�V����
		//UpdateBarrier();

		////�o�t�̍X�V����
		//UpdateBuff();

		////�I�[�g�X�V����
		//UpdateAuto();

		////�^���b�g�X�V����
		//UpdateTurret();

		////UI�w�i�̍X�V����
		//UpdateUIzone();

		//if (pPlayer->character == CHARACTER_1)
		//{
		//	//UI�̍X�V����
		//	UpdateUI();
		//	//UI�̍X�V����
		//	UpdateHomingUI();
		//}

		//else if (pPlayer->character == CHARACTER_2)
		//{
		//	//UI�̍X�V����
		//	UpdateBuffUI();
		//	//UI�̍X�V����
		//	UpdateLauncherUI();
		//}

		//else if (pPlayer->character == CHARACTER_3)
		//{
		//	//UI�̍X�V����
		//	UpdateTurretUI();
		//	//UI�̍X�V����
		//	UpdateAutoUI();
		//}

		//int nGetNumEnemy = GetNumEnemy();




	if (g_nWave >= WAVE || pPlayer->bUse == false)
	{
		g_FinishCnt++;
		if (g_FinishCnt >= 30)
		{
			//���U���g�Ɉڍs
			SetFade(MODE_RESULT);
		}
	}
		#ifdef _DEBUG
			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{
				SetFade(MODE_RESULT);
			}
		#endif

	}
}

//=============================================
//�Q�[���̕`�揈��
//=============================================
void DrawGame(void)
{
	//�X�N���[���̕`�揈��
	DrawScreen();

	////�z�[�~���O�̕`�揈��
	//DrawHoming();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�p�[�e�B�N���̕`�揈��
	DrawParticle();

	if (g_bPause == true)
	{//�|�[�Y���Ă���
	//�|�[�Y�̕`�揈��
		DrawPause();
	}
}

//=============================================
//�G�̃��[�h����
//=============================================
void LoadEnemy(void)
{
	////�t�@�C���̓ǂݍ���
	//FILE* pFile = fopen(FILE_ENEMY, "rb");

	//if (pFile != NULL)
	//{
	//	//�G�̎g�p���Ă鐔�̓ǂݍ���
	//	fread(&g_nUseEnemy, sizeof(int), 1, pFile);

	//	//�G�̎g�p�����A�G�̓ǂݍ���
	//	fread(&g_EnemyInfo[0], sizeof(EnemyInfo), g_nUseEnemy, pFile);

	//	//�t�@�C�������
	//	fclose(pFile);

	//}

	//else
	//{
	//	return;
	//}


	//for (int nCnt = 0; nCnt < g_nUseEnemy; nCnt++)
	//{

	//	SetEnemy(g_EnemyInfo[nCnt].pos, g_EnemyInfo[nCnt].nType);

	//}

	
}

//=============================================
//�u���b�N�̃��[�h����
//=============================================
void LoadBlock(void)
{
	////�t�@�C���̓ǂݍ���
	//FILE* pFile = fopen(FILE_BLOCK, "rb");

	//if (pFile != NULL)
	//{
	//	//�u���b�N�̎g�p���Ă鐔�̓ǂݍ���
	//	fread(&g_nUseBlock, sizeof(int), 1, pFile);

	//	//�u���b�N�̎g�p�����A�u���b�N�̏��ǂݍ���
	//	fread(&g_BlockInfo[0], sizeof(BlockInfo), g_nUseBlock, pFile);

	//	//�t�@�C�������
	//	fclose(pFile);

	//}

	//else
	//{
	//	return;
	//}

	////nFrame++;
	////int nAnswer = nFrame / 60;
	////if (nAnswer == 1)
	////{
	//	for (int nCnt = 0; nCnt < g_nUseBlock; nCnt++)
	//	{
	//		Setblock(g_BlockInfo[nCnt].pos, g_BlockInfo[nCnt].nType);
	//	}
	////	nFrame = 0;
	////}
}

//�G�f�B�b�g�̎擾
bool GetEdit(void)
{
	return g_bEdit;
}