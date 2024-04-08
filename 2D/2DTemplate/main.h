//=============================================
//
//2DTemplate[main.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MAIN_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MAIN_H_
//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib") //�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib") //���̊g�����C�u����
#pragma comment(lib,"dxguid.lib")
#pragma	comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")

//�}�N����`
#define SCREEN_WIDTH	(1280) //�E�B���h�E�̕�
#define SCREEN_HEIGHT	(720) //�E�B���h�E�̍���
#define VERTEX	(4) //���_��
#define NUM_TYPE_ENEMY (4) //�G�̎��
#define WORLD_WIDTH	(111280) //�E�B���h�E�̕�
#define WORLD_HEIGHT	(1440) //�E�B���h�E�̍���
#define MAX_ENEMY	(128) //�G�̍ő吔
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE |D3DFVF_TEX1) //���W�ƃJ���[�ƃe�N�X�`��
#define FILE_NAME	"data\\enemydata.bin" //�t�@�C����
#define EFFECT_TIME	(10) //�G�t�F�N�g�̎�������
#define TIME	(60) //��������


//���_���(2D)�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	float rhw; //���W�ϊ��p�W���i1.0f�j
	D3DCOLOR col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`��
}VERTEX_2D;

//��ʃ��[�h�̎��
typedef enum
{
	MODE_TITLE = 0, //�^�C�g�����
	MODE_MENU, //���j���[���
	MODE_TUTORIAL, //�`���[�g���A�����
	MODE_GAME, //�Q�[�����
	MODE_PICK, //�s�b�N���
	MODE_RESULT, //���U���g���
	MODE_MAX,
}MODE;

//=============================================
//�v���g�^�C�v�錾
//=============================================
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
LPD3DXFONT GetFont(void);
#endif // !_MAIN_H_ //���ꂪ��`����ĂȂ��Ƃ�x