//**************************************************
// 
// snake_head.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _SNAKE_HEAD_H_	//���̃}�N����`������ĂȂ�������
#define _SNAKE_HEAD_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "object3D.h"

//==================================================
// �O���錾
//==================================================
class CSnakeBody;

//==================================================
// ��`
//==================================================
class CSnakeHead : public CObject3D
{
	/* ��` */
public:

	/* ���ÓI�����o�֐��� */
public:
	static CSnakeHead* Create(const D3DXVECTOR3& pos);	// ����

	/* �������o�֐��� */
public:
	CSnakeHead();			// �f�t�H���g�R���X�g���N�^
	~CSnakeHead() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

public:
	const D3DXVECTOR3& GetPosOld() const;	// �O��̈ʒu�̎擾

private:
	void Set(const D3DXVECTOR3& pos, CSnakeBody** pBody);	// �ݒ�
	void SetMove();		// �ړ��ʂ̐ݒ�
	void PlayerCollision();	// �����蔻��
	void CircleCollision();	// �����蔻��

	/* �����o�ϐ� */
private:
	int m_time;				// �^�C��
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
	CSnakeBody** m_pBody;	// �̂̏��
};

#endif // !_ENEMY_SNAKE_HEAD_H_
