//===================================================
//
// �v���C���[�w�b�_�[
// Author:Teruto Sato
//
//===================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_	//��d�C���N���[�h�h�~

//--------------------------------
// �C���N���[�h
//--------------------------------
#include "object3D.h"

//================================
// �v���C���[�N���X�̒�`
//================================
class CPlayer : public CObject3D
{
public:
	CPlayer();				//�R���X�g���N�^
	~CPlayer() override;	//�f�X�g���N�^

	//--------------------
	// �����o�֐�
	//--------------------
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

	//--------------------
	// �ÓI�����o�ϐ�
	//--------------------
	static CPlayer* Create();	//����
	static void SetKill(bool kill);	// �L���̐ݒ�
	static bool GetKill();	// �L�����ꂽ���ǂ���

private:
	//--------------------
	// �v���C�x�[�g�֐�
	//--------------------
	D3DXVECTOR3 Move(int nUp, int nDown, int nLeft, int nRight);	//�ړ�

private:
	//--------------------
	// �ÓI�����o�ϐ�
	//--------------------
	static bool m_kill;	// �L�����ꂽ��

	//--------------------
	// �����o�ϐ�
	//--------------------
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_move;	//�ړ���
	D3DXVECTOR3 m_size;	//�傫��
};

#endif