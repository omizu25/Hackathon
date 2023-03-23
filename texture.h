//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �N���X
//==================================================
class CTexture
{
	/* ����`�� */
public:
	enum ELabel
	{
		LABEL_NONE = -1,			// �g�p���Ȃ�
		LABEL_Effect = 0,			// �G�t�F�N�g
		LABEL_Cursor,				// �J�[�\��
		LABEL_Number,				// ����
		LABEL_Enemy,				// �G
		LABEL_Enemy_ver2,			// �Gver2
		LABEL_Enemy_ver3_inside,	// �Gver3_����
		LABEL_Enemy_ver3_outside,	// �Gver3_�O��
		LABEL_Player,				// �v���C���[
		LABEL_UI_Stake,				// �ւ̐�(UI)
		LABEL_Shape_Circle,			// �}�`(�~)
		LABEL_Shape_Square,			// �}�`(�l�p)
		LABEL_Shape_Triangle,		// �}�`(�O�p)
		LABEL_Time,					// �^�C��
		LABEL_Life,					// ���C�t
		LABEL_Frame_Space,			// �F���t���[��
		LABEL_circle,				// �T�[�N��

		/* ���^�C�g���� */
		LABEL_TITLE_BG,			// �w�i
		LABEL_TITLE_Snake,		// ��
		LABEL_TITLE_PressEnter,	// PressEnter
		LABEL_TITLE_LOGO,		// ���S

		/* ���^�C�g���� */
		LABEL_RANKING_LOGO,		// ���S
		LABEL_RANKING_RETURN_LOGO,		// ���^�[�����S
		LABEL_RANKING_GO_LOGO,		// ���^�[�����S

		/* �����U���g�� */
		LABEL_RESULT_SnakeAnim,		//�A�j���[�V������
		LABEL_MAX
	};

	/* �������o�֐��� */
public:
	CTexture();		// �f�t�H���g�R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

public:
	void LoadAll();				// �S�Ă̓ǂݍ���
	void Load(ELabel label);	// �w��̓ǂݍ���
	void ReleaseAll();			// �S�Ă̔j��
	void Release(ELabel label);	// �w��̔j��
	LPDIRECT3DTEXTURE9 Get(ELabel label);	// ���̎擾

	/* �������o�ϐ��� */
private:
	LPDIRECT3DTEXTURE9 m_pTexture[LABEL_MAX];	// �e�N�X�`���̏��
};

#endif // !_TEXTURE_H_
