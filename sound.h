//**************************************************
//
// sound.h
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _SOUND_H_	//���̃}�N����`������ĂȂ�������
#define _SOUND_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �N���X
//==================================================
class CSound
{
	/* ����`�� */
public:
	enum ELabel
	{
		LABEL_NONE = -1,
		LABEL_BGM_Title = 0,	// �^�C�g��
		LABEL_BGM_Game,			// �Q�[��
		LABEL_BGM_Result,		// ���U���g
		LABEL_BGM_Ranking,		// �����L���O
		LABEL_BGM_Tutorial,		// �`���[�g���A��
		LABEL_SE_Enter,			// ����
		LABEL_SE_Select,		// �I��
		LABEL_SE_Hit,			// ���������Ƃ��̔���
		LABEL_SE_Waring,		// ���Ԑ���
		LABEL_SE_Danger,		// �댯�M��
		LABEL_MAX,
	};

	/* �������o�֐��� */
public:
	CSound();	// �f�t�H���g�R���X�g���N�^
	~CSound();	// �f�X�g���N�^

public:
	HRESULT Init(HWND hWnd);	// ������
	void Uninit();				// �I��
	HRESULT Play(ELabel sound);	// �Đ�
	void Stop(ELabel label);	// �w�肵����~
	void Stop();				// �S�Ă̒�~

public:
	void SetVolume(ELabel label, float fVolume);		// ���ʂ̐ݒ�
	void SetRate(ELabel label, float rate);				// �s�b�`����

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);	// �`�����N�̃`�F�b�N
	HRESULT LoadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	// �`�����N�f�[�^�̓ǂݍ���

	/* �������o�ϐ��� */
private: 
	IXAudio2* m_pXAudio2;							// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice;		// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_pSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	BYTE* m_pDataAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_sizeAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	float m_fVol;									// �T�E���h�̉��ʂ�ω�������ϐ�
	float m_fPitch;									// �T�E���h�̉�����ω�������ϐ�
};

#endif // !_SOUND_H_
