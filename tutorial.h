//**************************************************
// 
// Tutorial.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TUTORIAL_H_	//���̃}�N����`������ĂȂ�������
#define _TUTORIAL_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "mode.h"

//==================================================
// �O���錾
//==================================================
class CMenu;

//==================================================
// �N���X
//==================================================
class CTutorial : public CMode
{
	/* ��` */
public:

	/* �������o�֐��� */
public:
	CTutorial();			// �f�t�H���g�R���X�g���N�^
	~CTutorial() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

private:
	void Input();	// ����

					/* �����o�ϐ� */
private:
	CMenu* m_pMenu;	// ���j���[�̏��
};

#endif // !_TUTORIAL_H_
