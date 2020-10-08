//*************************************************************************************************************
//
// 2DUI����[2DUI.cpp]
// Author : Sekine Ikuto
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "2DUI.h"
#include "Scene2D.h"
#include "number.h"
#include "NumericString.h"
#include "texture.h"

//-------------------------------------------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------------------------------------------
C2DUi * C2DUi::Create(SETING2DUI &seting)
{
	C2DUi * pC2dui = new C2DUi;
	pC2dui->Init(seting);
	return pC2dui;
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
void C2DUi::Init(SETING2DUI & seting)
{
	m_Mask = seting.mask;

	if (Mybfunc_bit_comp(m_Mask.unMask, FLAG_NUMBER))
	{
		m_pNumber = CNumericString::Create(seting.pos, seting.col, seting.size, seting.fRotation, seting.nValue);
		m_pNumber->BindTexture(CTexture::GetTextureInfo(seting.nTextureID));
	}
	else
	{
		m_pImage = CScene2D::Create(PRIORITY::PRIORITY_2DUI, seting.pos, seting.col, ORIGINVERTEXTYPE_ROTCENTER, seting.size, 0.0f, seting.fRotation);
		m_pImage->BindTexture(CTexture::GetTextureInfo(seting.nTextureID));
	}

	if (Mybfunc_bit_comp(m_Mask.unMask, FLAG_FLASHING))
	{
		m_pFlashing = new C2DUi::FLASHING;
	}
	if (Mybfunc_bit_comp(m_Mask.unMask, FLAG_FADE))
	{
		m_pFade = new C2DUi::FADE;
	}
	m_nTextureID = 0;
	m_bDisp = true;
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
void C2DUi::Init(void)
{
}

//-------------------------------------------------------------------------------------------------------------
// �I��
//-------------------------------------------------------------------------------------------------------------
void C2DUi::Uninit(void)
{
	if (m_pFlashing != nullptr)
	{
		delete m_pFlashing;
		m_pFlashing = nullptr;
	}
	if (m_pFade != nullptr)
	{
		delete m_pFade;
		m_pFade = nullptr;
	}
	if (m_pNumber != nullptr)
	{
		m_pNumber->Uninit();
		delete m_pNumber;
		m_pNumber = nullptr;
	}
	if (m_pImage != nullptr)
	{
		m_pImage->Release();
	}
}

//-------------------------------------------------------------------------------------------------------------
// �X�V
//-------------------------------------------------------------------------------------------------------------
void C2DUi::Update(void)
{
}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void C2DUi::Draw(void)
{
	if (m_bDisp == true)
	{
		if (m_pNumber != nullptr)
		{
			m_pNumber->Draw();
		}
		if (m_pImage != nullptr)
		{
			m_pImage->Draw();
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
// �A���t�@�l��͈͓��ɐ�������
//-------------------------------------------------------------------------------------------------------------
bool C2DUi::AlphaLimitRange(D3DXCOLOR &col)
{
	if (col.a <= 0.0f)
	{
		col.a = 0.0f;
		return true;
	}
	else if (col.a >= 1.0f)
	{
		col.a = 1.0f;
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------------------
// �t�F�[�h�̍X�V
//-------------------------------------------------------------------------------------------------------------
void C2DUi::FADE::Update(CScene2D *pImage)
{
	// �F�̎擾
	D3DXCOLOR *pCol = pImage->GetColor();

	// �F�̕ω�
	pCol->a += fChangeValue * nAddSign;

	// �A���t�@�l��͈͓��ɐ�������
	if (C2DUi::AlphaLimitRange(*pCol) == true)
	{// �����ꂽ�Ƃ�
		nAddSign *= -1;
	}

	// ���_�J���[���X�V����
	pImage->UpdateVatexColor();
}

//-------------------------------------------------------------------------------------------------------------
// �t�F�[�h�̍X�V
//-------------------------------------------------------------------------------------------------------------
void C2DUi::FADE::Update(CNumericString * pNumber)
{
	if (pNumber == nullptr)
	{
		return;
	}

	for (int nCntNumber = 0; nCntNumber < pNumber->m_nNumNumber; nCntNumber++)
	{
		// �����N���X�̎擾
		CNumber *pNumClass = &pNumber->m_pNumber[nCntNumber];
		if (pNumClass == nullptr)
		{
			continue;
		}
		// �F�̎擾
		D3DXCOLOR *pCol = pNumClass->GetColor();

		// �F�̕ω�
		pCol->a += fChangeValue * nAddSign;

		// �A���t�@�l��͈͓��ɐ�������
		if (C2DUi::AlphaLimitRange(*pCol) == true)
		{// �����ꂽ�Ƃ�
			nAddSign *= -1;
		}

		// ���_�J���[���X�V����
		pNumClass->SetVeatexColor();
	}
}

//-------------------------------------------------------------------------------------------------------------
// �_�ł̍X�V
//-------------------------------------------------------------------------------------------------------------
void C2DUi::FLASHING::Update(C2DUi * pThis)
{
	UINT *pTime = &pThis->GetTime();

	*pTime += 1;

	if (pThis->m_pFlashing->IsEqual(*pTime))
	{
		pThis->ChangeDispFlag();
		pTime = 0;
	}
}
