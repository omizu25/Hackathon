//**************************************************
// 
// circle.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _CIRCLE_H_	//���̃}�N����`������ĂȂ�������
#define _CIRCLE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "object3D.h"

//==================================================
// ��`
//==================================================
class CCircle : public CObject3D
{
	/* ��` */
public:
	static const int COUNTDOWN_TIME;	// �J�E���g�_�E���̎���

private:
	static const int MAX_LIFE;			// �����̍ő�l
	static const D3DXCOLOR STD_COLOR;	// �W���̐F
	static const D3DXCOLOR START_COLOR;	// �n�܂�̐F
	static const D3DXCOLOR END_COLOR;	// �I���̐F
	static const D3DXCOLOR DIFF_COLOR;	// �F�̍���

	/* ���ÓI�����o�֐��� */
public:
	static CCircle* Create();	// ����

	/* �������o�֐��� */
public:
	CCircle();				// �f�t�H���g�R���X�g���N�^
	~CCircle() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

public:
	bool GetCollision();

private:
	void Appear();		// �o��
	void DisAppear();	// ����

	/* �������o�ϐ��� */
private:
	int m_time;	// �^�C��
	bool m_appear;	// �o�����Ă��邩�ǂ���
	D3DXCOLOR m_changeCol;	// �F�̕ω���
};

#endif // !_CIRCLE_H_
