//**************************************************
// 
// enemy.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_H_	//���̃}�N����`������ĂȂ�������
#define _ENEMY_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "object3D.h"

//==================================================
// ��`
//==================================================
class CEnemy : public CObject3D
{
	/* ��` */
public:

	/* ���ÓI�����o�֐��� */
public:
	static CEnemy* Create(const D3DXVECTOR3& pos, float rot);	// ����

	/* �������o�֐��� */
public:
	CEnemy();			// �f�t�H���g�R���X�g���N�^
	~CEnemy() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

private:
	void Set(const D3DXVECTOR3& pos, float rot);	// �ݒ�
	void Move();	// �ړ�

	/* �����o�ϐ� */
private:
	D3DXVECTOR3 m_move;	// �ړ���
};

#endif // !_ENEMY_H_
