//**************************************************
// 
// ranking_ui.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RANKING_UI_H_	//���̃}�N����`������ĂȂ�������
#define _RANKING_UI_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "object.h"

//==================================================
// �O���錾
//==================================================
class CNumberManager;
class CNumber;
class CObject2D;

//==================================================
// ��`
//==================================================
class CRankingUI : public CObject
{
	/* ���ÓI�����o�֐��� */
public:
	static const int MAX_RANKING = 5;	// �����L���O�̍ő吔

	/* ���ÓI�����o�֐��� */
public:
	static CRankingUI* Create(const D3DXVECTOR3& pos, float length);	// ����
	static void SetScore(int score);	// �ݒ�
	static int Get(int rank);	// �擾

private:
	static void Load();		// �ǂݍ���
	static void Save();		// �ۑ�
	static void Change();	// �ύX

	/* ���ÓI�����o�ϐ��� */
private:
	static int m_score;	// ����̃X�R�A
	static int m_ranking[MAX_RANKING];	// �����L���O

	/* �������o�֐��� */
public:
	CRankingUI();			// �f�t�H���g�R���X�g���N�^
	~CRankingUI() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

private:
	void Set(const D3DXVECTOR3& pos, float length);	// �ݒ�

	/* �������o�ϐ��� */
private:
	CNumberManager* m_pRanking[MAX_RANKING];	// �����L���O
	CNumber* m_pNumber[MAX_RANKING];	// ����
	CObject2D* m_pRank[MAX_RANKING];	// ��
	int m_newRank;	// �V�����X�R�A
	int m_time;		// �^�C��
};

#endif // !_RANKING_UI_H_
