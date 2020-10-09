// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// ���[�U�[�C���^�[�t�F�[�X���� [ui.cpp]
// Author : KOKI NISHIYAMA
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ui.h"
/* �`�� */
#include "fade.h"
#include "game.h"
#include "Calculation.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define UI_MANAGER_FILE "data/LOAD/UI/ui_manager.txt"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::vector<CUi::UI_LOAD> CUi::m_vec_UiLoad[CUi::UITYPE_MAX] = {};	// Ui�ǂݍ��ݗp�ϐ�
std::vector<std::string> CUi::m_vec_String = {};					// �t�@�C�����ǂݏ����p

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CUi::CUi()
{

}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CUi::~CUi()
{
}

#ifdef _DEBUG
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�o�b�O
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CUi::Debug(void)
{

}
#endif // _DEBUG

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �e�L�X�g�̓ǂݍ��ݏ���
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CUi::Load(void)
{
	// �ϐ��錾
	HRESULT hr;
	// UI�}�l�[�W���[�̓ǂݍ���
	hr = UiManagerLoad();
	// UI�X�N���v�g�̓ǂݍ���
	hr = UiScriptLoad();
	// ���ʂ�Ԃ�
	return hr;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// UI�}�l�[�W���[�̓ǂݍ���
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CUi::UiManagerLoad(void)
{
	// �ϐ��錾
	// �t�@�C���̒��g�i�[�p
	std::vector<std::vector<std::string>> vsvec_Contens;
	// �t�@�C���̒��g���擾����
	vsvec_Contens = CCalculation::FileContens(UI_MANAGER_FILE, '\0');
	// �s���Ƃɉ�
	for (int nCntLine = 0; nCntLine < (signed)vsvec_Contens.size(); nCntLine++)
	{
		// ���ڂ��Ƃɉ�
		for (int nCntItem = 0; nCntItem < (signed)vsvec_Contens.at(nCntLine).size(); nCntItem++)
		{
			switch (nCntItem)
			{
				// �p�X���
			case 0:
				m_vec_String.emplace_back(vsvec_Contens.at(nCntLine).at(nCntItem));
				break;
			default:
				break;
			}
		}
	}
	// �t�@�C���̒��g�̊J��
	for (int nCntLine = 0; nCntLine < (signed)vsvec_Contens.size(); nCntLine++)
	{
		vsvec_Contens[nCntLine].clear();
		vsvec_Contens[nCntLine].shrink_to_fit();
	}
	vsvec_Contens.clear();
	vsvec_Contens.shrink_to_fit();

	return S_OK;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// UI�X�N���v�g�̓ǂݍ���
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CUi::UiScriptLoad(void)
{
	// �t�@�C���|�C���g
	FILE *pFile;

	// �ϐ��錾
	int  nCntError = 0;				// �J�E���g���[�h
	int	nCntUi = 0;					// �J�E���gUI
	char cComp[128];				// ����̕�����̔�r
	char cRaedText[128];			// �����Ƃ��ēǂݎ��p
	char cHeadText[128];			// ��r����悤
	char cDie[128];					// �s�K�v�ȕ���

	for (int nCntLoad = 0; nCntLoad < (signed)m_vec_String.size(); nCntLoad++)
	{
		// �ǂݍ���UI�t�@�C���̏���𒴂����Ƃ�
		// ->���[�v�𔲂���
		if (nCntLoad >= UITYPE_MAX)
		{
			break;
		}
		nCntUi = 0;
		cHeadText[0] = '\0';
		cHeadText[0] = '\0';
		// �t�@�C�����J����Ă��Ȃ�������
		if ((pFile = fopen(m_vec_String[nCntLoad].c_str(), "r")) == NULL)
		{// ���b�Z�[�W�̕\��
#ifdef _DEBUG
			CCalculation::Messanger("UI�̃e�L�X�g�t�@�C����������܂���ł���");
#endif // _DEBUG
			continue;
		}
		// �X�N���v�g�����݂��Ă��邩�`�F�b�N
		if (!CCalculation::Existenceofscript(pFile))
		{
#ifdef _DEBUG
			CCalculation::Messanger("UI��[SCRIP]��������܂���\n�I�����Ă�������");
#endif // _DEBUG
			fclose(pFile);
			continue;
		}
		// �G���h�X�N���v�g������܂Ń��[�v
		while (strcmp(cHeadText, "END_SCRIPT") != 0)
		{
			fgets(cRaedText, sizeof(cRaedText), pFile);
			sscanf(cRaedText, "%s", &cHeadText);

			// ���s��������
			if (strcmp(cHeadText, "\n") == 0)
			{
			}

			// ���f���Z�b�g��������
			else if (strcmp(cHeadText, "SET") == 0)
			{
				// �i�[����
				m_vec_UiLoad[nCntLoad].emplace_back(UI_LOAD());
				// ��r�̏�����
				cComp[0] = '\0';
				// �ǂݍ���Ǖ�������
				sscanf(cRaedText, "%s %s", &cDie, &cComp);
				// �G���h���f���Z�b�g������܂Ń��[�v
				while (strcmp(cHeadText, "END_SET") != 0)
				{
					fgets(cRaedText, sizeof(cRaedText), pFile);
					sscanf(cRaedText, "%s", &cHeadText);

					// �ʒu���ǂݍ���
					if (strcmp(cHeadText, "POS") == 0)
					{
						sscanf(cRaedText, "%s %s %f %f %f", &cDie, &cDie,
							&m_vec_UiLoad[nCntLoad].at(nCntUi).pos.x,
							&m_vec_UiLoad[nCntLoad].at(nCntUi).pos.y,
							&m_vec_UiLoad[nCntLoad].at(nCntUi).pos.z);
					}
					// �ʒu���ǂݍ���
					else if (strcmp(cHeadText, "COL") == 0)
					{
						sscanf(cRaedText, "%s %s %f %f %f %f", &cDie, &cDie,
							&m_vec_UiLoad[nCntLoad].at(nCntUi).col.r,
							&m_vec_UiLoad[nCntLoad].at(nCntUi).col.g,
							&m_vec_UiLoad[nCntLoad].at(nCntUi).col.b,
							&m_vec_UiLoad[nCntLoad].at(nCntUi).col.a
						);
					}
					// �T�C�Y���ǂݍ���
					else if (strcmp(cHeadText, "SIZE") == 0)
					{
						sscanf(cRaedText, "%s %s %f %f", &cDie, &cDie,
							&m_vec_UiLoad[nCntLoad].at(nCntUi).size.x,
							&m_vec_UiLoad[nCntLoad].at(nCntUi).size.y);
					}
					// �p�x���ǂݍ���
					else if (strcmp(cHeadText, "ROT") == 0)
					{
						sscanf(cRaedText, "%s %s %f", &cDie, &cDie,
							&m_vec_UiLoad[nCntLoad].at(nCntUi).fRot);
					}
					// �e�N�X�`���[�^�C�v���ǂݍ���
					else if (strcmp(cHeadText, "TEXTYPE") == 0)
					{
						sscanf(cRaedText, "%s %s %d", &cDie, &cDie,
							&m_vec_UiLoad[nCntLoad].at(nCntUi).nTexType);
					}
					// �G���[�J�E���g���C���N�������g
					nCntError++;
					if (nCntError > FILELINE_ERROW)
					{// �G���[
						nCntError = 0;
						fclose(pFile);
						CCalculation::Messanger("UI�Z�b�g������܂���");
						return E_FAIL;
					}
				}
				// UI�J�E���g�A�b�v
				nCntUi++;
			}
			// �G���[�J�E���g���C���N�������g
			nCntError++;
			if (nCntError > FILELINE_ERROW)
			{// �G���[
				nCntError = 0;
				fclose(pFile);
				CCalculation::Messanger("�G���h�X�N���v�g������܂���");
				return E_FAIL;
			}
		}
		fclose(pFile);
	}
	return S_OK;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �S�\�[�X�̊J������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CUi::UnLoad(void)
{
	// �SUI�^�C�v�̃��[�v
	for (int nCntLoad = 0; nCntLoad < UITYPE_MAX; nCntLoad++)
	{
		// std::vector�̊J��
		std::vector<UI_LOAD>().swap(m_vec_UiLoad[nCntLoad]);
	}
	m_vec_String.clear();
	m_vec_String.shrink_to_fit();
}
