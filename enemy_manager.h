//**************************************************
// 
// enemy_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_MANAGER_H_	// ���̃}�N����`������ĂȂ�������
#define _ENEMY_MANAGER_H_	// ��d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "object.h"

//==================================================
// �N���X
//==================================================
class CEnemyManager : public CObject
{
	/* ����`�� */
private:
	
	/* ���ÓI�����o�֐��� */
public:
	static CEnemyManager* Create();	// ����

	/* �������o�֐��� */
public:
	CEnemyManager();			// �f�t�H���g�R���X�g���N�^
	~CEnemyManager() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

private:
	void Game();	// �Q�[��

	/* �������o�ϐ��� */
private:
	int m_time;		// ����
	int m_pop;		// �o����
	int m_interval;	// �Ԋu
};

#endif // !_ENEMY_MANAGER_H_