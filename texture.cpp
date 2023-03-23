//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "texture.h"
#include "application.h"

//==================================================
// ��`
//==================================================
namespace
{
const string FILE_PATH[] =
{// �e�N�X�`���̃p�X
	"data/TEXTURE/effect.png",				// �G�t�F�N�g
	"data/TEXTURE/Cursor.png",				// �J�[�\��
	"data/TEXTURE/Number.png",				// ����
	"data/TEXTURE/Enemy.png",				// �G
	"data/TEXTURE/Enemy_ver2.png",			// �Gver.2
	"data/TEXTURE/Enemy_ver3_inside.png",	// �Gver.3_����
	"data/TEXTURE/Enemy_ver3_outside.png",	// �Gver.3_�O��
	"data/TEXTURE/Player.png",				// �v���C���[
	"data/TEXTURE/UI_Snake.png",			// �ւ̐�(UI)
	"data/TEXTURE/Shape_Circle.png",		// �}�`(�~)
	"data/TEXTURE/Shape_Square.png",		// �}�`(�l�p)
	"data/TEXTURE/Shape_Triangle.png",		// �}�`(�O�p)
	"data/TEXTURE/Time.png",				// �^�C��
	"data/TEXTURE/Life.png",				// ���C�t
	"data/TEXTURE/Frame_Space.png",			// �F���t���[��
	"data/TEXTURE/circle.png",				// �T�[�N��

	/* ���^�C�g���� */
	"data/TEXTURE/Title/BG.png",			// �w�i
	"data/TEXTURE/Title/Snake.png",			// ��
	"data/TEXTURE/Title/PressEnter.png",	// PressEnter
	"data/TEXTURE/Title/Logo.png",			// ���S

	/* �������L���O�� */
	"data/TEXTURE/Ranking/RankingLogo.png",			// ���S
	"data/TEXTURE/Ranking/RankingReturnLogo.png",	// ���S
	"data/TEXTURE/Ranking/RankingGoLogo.png",	// ���S

	/* �����U���g�� */
	"data/TEXTURE/Result/Snake_Anim.png",	//�A�j���[�V������
};
}

static_assert(sizeof(FILE_PATH) / sizeof(FILE_PATH[0]) == CTexture::LABEL_MAX, "aho");

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTexture::CTexture()
{
	memset(m_pTexture, 0, sizeof(m_pTexture));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------
void CTexture::LoadAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		// �ǂݍ���
		Load((ELabel)i);
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CTexture::Load(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pTexture[label] != nullptr)
	{// �e�N�X�`���̓ǂݍ��݂�����Ă���
		return;
	}

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		FILE_PATH[label].c_str(),
		&m_pTexture[label]);
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CTexture::ReleaseAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		// �j��
		Release((ELabel)i);
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CTexture::Release(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pTexture[label] != nullptr)
	{// �e�N�X�`���̉��
		m_pTexture[label]->Release();
		m_pTexture[label] = nullptr;
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::Get(ELabel label)
{
	if (label == LABEL_NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return nullptr;
	}

	assert(label > LABEL_NONE && label < LABEL_MAX);

	// �ǂݍ���
	Load(label);

	return m_pTexture[label];
}
