//**************************************************
// 
// game.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _GAME_H_	//���̃}�N����`������ĂȂ�������
#define _GAME_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "mode.h"

//==================================================
// �O���錾
//==================================================
class CPlayer;	//�v���C���[
class CCircle;

//==================================================
// �N���X
//==================================================
class CGame : public CMode
{
	/* ��` */
public:

	/* ���ÓI�����o�֐��� */
public:
	CPlayer* GetPlayer();	// �v���C���[�̎擾
	CCircle* GetCircle();	// �v���C���[�̎擾

	/* �������o�֐��� */
public:
	CGame();			// �f�t�H���g�R���X�g���N�^
	~CGame() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

	/* �������o�ϐ��� */
private:
	static CPlayer* m_pPlayer;	//�v���C���[
	static CCircle* m_pCircle;	//�v���C���[
};

#endif // !_GAME_H_
