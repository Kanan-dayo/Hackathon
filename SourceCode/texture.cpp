//*************************************************************************************************************
//
// �e�N�X�`������[texture.h]
// Author : Sekine Ikuto
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "texture.h"
#include "renderer.h"

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏�����
//-------------------------------------------------------------------------------------------------------------
int								CTexture::m_nNumTextureMax = 0;		// �ő�e�N�X�`����
MyVector<LPDIRECT3DTEXTURE9>	CTexture::m_pTexture = {};			// �e�N�X�`�����̃|�C���^
MyVector<CString>				CTexture::m_pFileName = {};			// �t�@�C�����̃|�C���^

//-------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CTexture::CTexture()
{
}

//-------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CTexture::~CTexture()
{
}

//-------------------------------------------------------------------------------------------------------------
// �ǂݍ���
//-------------------------------------------------------------------------------------------------------------
void CTexture::Load(void)
{
	// �ϐ��錾
	DWORD start = timeGetTime();	// �v���X�^�[�g����

	// �e�N�X�`���̐���
	CreateTexture();

	DWORD end = timeGetTime();		// �v���I������
	// �������x�̕\��
	cout << "texture.cpp == �e�N�X�`���ǂݍ��� �������x = " << (end - start) << "�@[" << (end - start) * 0.001f << "sec.]\n\n";
}

//-------------------------------------------------------------------------------------------------------------
// �J��
//-------------------------------------------------------------------------------------------------------------
void CTexture::Unload(void)
{
	// �e�N�X�`�����̊J��
	for (int nCntTexture = 0; nCntTexture < m_nNumTextureMax; nCntTexture++)
	{
		m_pTexture[nCntTexture]->Release();
		m_pTexture[nCntTexture] = nullptr;
	}
	// �e�N�X�`�����R���e�i�̃N���A
	m_pTexture.clear();

	// �t�@�C�����̊J��
	for (int nCntFileName = 0; nCntFileName < m_nNumTextureMax; nCntFileName++)
	{
		m_pFileName[nCntFileName].release();
	}
	// �t�@�C�����R���e�i�̃N���A
	m_pFileName.clear();
}

//-------------------------------------------------------------------------------------------------------------
// �e�N�X�`���̐���
//-------------------------------------------------------------------------------------------------------------
void CTexture::CreateTexture(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;						// �f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer().GetDevice();		// �f�o�C�X�̎擾

	// �����̒��B
	GetResource();

	for (int nCntTexture = 0; nCntTexture < m_nNumTextureMax; nCntTexture++)
	{
		// �ݒ�p�e�N�X�`�����
		LPDIRECT3DTEXTURE9 SetingText;
		STRING SetingStr = m_pFileName[nCntTexture].Get();
		// �e�N�X�`���̓ǂݍ���
		if (D3DXCreateTextureFromFile(pDevice, SetingStr, &SetingText) != D3D_OK)
		{
#ifdef _DEBUG
			MessageBox(NULL, "�e�N�X�`���̐����Ɏ��s���܂���", "�x���I", MB_ICONWARNING);
#endif
		}
		// �v�f�̑}��
		m_pTexture.insert(m_pTexture.end(), SetingText);
	}
}

//-------------------------------------------------------------------------------------------------------------
// �e�N�X�`�����̎擾
//-------------------------------------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTextureInfo(int nIndex)
{
	return m_pTexture[nIndex];
}

//-------------------------------------------------------------------------------------------------------------
// �e�N�X�`�����̍ő�
//-------------------------------------------------------------------------------------------------------------
int CTexture::GetNumTextureMax(void)
{
	return m_nNumTextureMax;
}

//-------------------------------------------------------------------------------------------------------------
// �t�@�C�����̎擾
//-------------------------------------------------------------------------------------------------------------
void CTexture::GetFileName(const int nIndex, STRING output)
{
	STRING pName = '\0';
	pName = strstr(m_pFileName[nIndex].Get(), "TEXTURE");
	sprintf(output, "%s", pName);
}

//-------------------------------------------------------------------------------------------------------------
// �t�@�C�����̎擾
//-------------------------------------------------------------------------------------------------------------
CONST_STRING CTexture::GetFileName(const int nIndex)
{
	STRING pName = '\0';
	pName = strstr(m_pFileName[nIndex].Get(), "TEXTURE");
	return pName;
}

//-------------------------------------------------------------------------------------------------------------
// �����̒��B
//-------------------------------------------------------------------------------------------------------------
void CTexture::GetResource(void)
{
	// �t�@�C�����珉���ݒ��ǂ݂��ރN���X�錾
	CLoadFile Load;

	// ������փt�@�C�������[�h����
	Load.LoadFileIntoString(CManager::GetFIleName(CManager::FILE_TEXTURE));

	// �����񂩂珉���ݒ��ǂݍ���
	Load.SetingfromString(ReadFromLine);

	// �t�@�C���f�[�^�̔j��
	Load.DeleteFileData();
}

//-------------------------------------------------------------------------------------------------------------
// 1�s�������ǂݎ��
//-------------------------------------------------------------------------------------------------------------
void CTexture::ReadFromLine(CONST_STRING cnpLine, CONST_STRING cnpEntryType, CONST_STRING cnpEntryData)
{
	if (strcmp("NUMBER", cnpEntryData) != 0)
	{// �t�@�C�����̓ǂݍ���
		FileNameLoad(cnpLine);
	}
	else
	{// ���̓ǂݍ���
		NumLoad(cnpLine);
	}
}

//-------------------------------------------------------------------------------------------------------------
// ���̓ǂݍ���
//-------------------------------------------------------------------------------------------------------------
void CTexture::NumLoad(CONST_STRING cnpLine)
{
	// �ϐ��錾
	int nSetingNumber = 0;	// �ݒ�p��

	if (sscanf(cnpLine, "NUMBER = %d", &nSetingNumber) == 1)
	{
		// �e�N�X�`��
		m_nNumTextureMax = nSetingNumber;
		// ���e�ʂ𑝂₷
		m_pFileName.reserve(m_nNumTextureMax);
		m_pTexture.reserve(m_nNumTextureMax);
	}
}

//-------------------------------------------------------------------------------------------------------------
// �t�@�C�����̓ǂݍ���
//-------------------------------------------------------------------------------------------------------------
void CTexture::FileNameLoad(CONST_STRING cnpLine)
{
	// �ϐ��錾
	char aSetingFileName[MYLIB_STRINGSIZE];			// �ݒ�p�t�@�C����
	aSetingFileName[0] = MYLIB_CHAR_UNSET;
	if (sscanf(cnpLine, "FILENAME = %s", aSetingFileName) == 1)
	{
		// �v�f������ɑ}��
		m_pFileName.push_back();
		// �����|�C���^�̎擾
		CString *pBack = &m_pFileName.back();
		// �����v�f�ɕ�����̐ݒ�
		pBack->Set(aSetingFileName);
	}
}
