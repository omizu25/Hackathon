//**************************************************
// 
// return.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RETURN_H_	//���̃}�N����`������ĂȂ�������
#define _RETURN_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "object3D.h"

//==================================================
// �N���X
//==================================================
class CReturn : public CObject3D
{
	/* ����`�� */
public:

	/* ���ÓI�����o�֐��� */
private:
	static float m_move;	// �ړ���
	static int m_count;		// �J�E���g

	/* ���ÓI�����o�֐��� */
public:
	static float GetMove();
	static void AddMove();		// ���x�̉��Z
	static void CreateAll();	// �S�Ă̐���
	static CReturn* Create(const D3DXVECTOR3& pos);	// ����

	/* �������o�֐��� */
public:
	CReturn();				// �f�t�H���g�R���X�g���N�^
	~CReturn() override;	// �f�X�g���N�^

public: 
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

	/* �������o�ϐ��� */
private:
	int m_time;
	D3DXVECTOR2 u;
	bool m_effect;
};

#endif // !_RETURN_H_
