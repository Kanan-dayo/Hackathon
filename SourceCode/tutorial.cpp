//*************************************************************************************************************
//
// �`���[�g���A������ [tutorial.h]
// Author:KOKI NISHIYAMA
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "tutorial.h"
#include "2DUI.h"
#include "keyboard.h"
#include "renderer.h"
#include "fade.h"
#include "ui.h"

//-------------------------------------------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------------------------------------------
CTutorial * CTutorial::Create(void)
{
	CTutorial *pTitle = new CTutorial;
	pTitle->Init();
	return pTitle;
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
void CTutorial::Init(void)
{
	C2DUi::SETING2DUI set[TUTORIALUI_MAX];
	// UI�̎擾
	std::vector<CUi::UI_LOAD> Ui_Load = CUi::GetUi(CUi::UITYPE_TUTORIALUI);
	// UI�S�̂̐ݒ�
	for (int nCntUi = 0; nCntUi < (signed)Ui_Load.size(); nCntUi++)
	{
		set[nCntUi].bDisp = true;
		set[nCntUi].col = Ui_Load[nCntUi].col;
		set[nCntUi].fRotation = Ui_Load[nCntUi].fRot;
		set[nCntUi].nTextureID = Ui_Load[nCntUi].nTexType;
		set[nCntUi].pos = Ui_Load[nCntUi].pos;
		set[nCntUi].size = Ui_Load[nCntUi].size;
	}

	set[TUTORIALUI_DISCRIPTION].mask.unMask = C2DUi::MASK_FLASHING;
	pC2dui[TUTORIALUI_DISCRIPTION] = C2DUi::Create(set[TUTORIALUI_DISCRIPTION]);
	pC2dui[TUTORIALUI_DISCRIPTION]->GetFlashing()->m_nTiming = 3;

	this->m_State = STATE_NORMAL;

	CMode::Init(STATE_NORMAL, 30);
}

//-------------------------------------------------------------------------------------------------------------
// �I��
//-------------------------------------------------------------------------------------------------------------
void CTutorial::Uninit(void)
{
}

//-------------------------------------------------------------------------------------------------------------
// �X�V
//-------------------------------------------------------------------------------------------------------------
void CTutorial::Update(void)
{
	if (this->m_State == STATE_NORMAL)
	{
	}
	else if (this->m_State == STATE_OUT)
	{
		pC2dui[TUTORIALUI_DISCRIPTION]->GetFlashing()->Update(pC2dui[TUTORIALUI_DISCRIPTION]);
		if (this->m_nCntState == this->m_nMaxCntState)
		{
			CManager::GetRenderer().GetFade()->SetFade(CManager::MODE_GAME);
		}
		this->m_nCntState++;
	}
	if (CManager::GetKeyboard().GetTrigger(DIK_RETURN))
	{
		this->SetState(STATE_OUT);
	}
}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void CTutorial::Draw(void)
{
}
