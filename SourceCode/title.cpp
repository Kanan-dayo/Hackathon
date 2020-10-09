//*************************************************************************************************************
//
// �^�C�g������ [title.h]
// Author:KOKI NISHIYAMA
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "title.h"
#include "2DUI.h"
#include "keyboard.h"
#include "renderer.h"
#include "fade.h"
#include "3Dparticle.h"
#include "2Deffect.h"
#include "ui.h"

//-------------------------------------------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------------------------------------------
CTitle * CTitle::Create(void)
{
	CTitle *pTitle = new CTitle;
	pTitle->Init();
	return pTitle;
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
void CTitle::Init(void)
{
	// �ϐ��錾
	C2DUi::SETING2DUI set[TITLEUI_MAX];	// UI�ݒ�p�ϐ�
	// 2D�G�t�F�N�g����
	C2DEffect::Create();
	// UI�̎擾
	std::vector<CUi::UI_LOAD> Ui_Load = CUi::GetUi(CUi::UITYPE_TITLEUI);
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
	// �^�C�g���̐ݒ�
	set[TITLEUI_NAME].mask.unMask = C2DUi::MASK_FADE | C2DUi::MASK_FLASHING;
	// �^�C�g���̐���
	pC2dui[TITLEUI_NAME] = C2DUi::Create(set[TITLEUI_NAME]);
	pC2dui[TITLEUI_NAME]->GetFade()->bLoop = true;
	pC2dui[TITLEUI_NAME]->GetFade()->nTiming = 90;
	pC2dui[TITLEUI_NAME]->GetFade()->fChangeValue = 1.0f / pC2dui[TITLEUI_NAME]->GetFade()->nTiming;
	pC2dui[TITLEUI_NAME]->GetFade()->nAddSign = 1;

	// �v���X�G���^�[�̐ݒ�
	set[TITLEUI_PRESSENTERNAME].mask.unMask = C2DUi::MASK_FADE | C2DUi::MASK_FLASHING;
	// �v���X�G���^�[�̐���
	pC2dui[TITLEUI_PRESSENTERNAME] = C2DUi::Create(set[TITLEUI_PRESSENTERNAME]);
	pC2dui[TITLEUI_PRESSENTERNAME]->GetFade()->bLoop = true;
	pC2dui[TITLEUI_PRESSENTERNAME]->GetFade()->nTiming = 30;
	pC2dui[TITLEUI_PRESSENTERNAME]->GetFade()->fChangeValue = 1.0f / pC2dui[TITLEUI_PRESSENTERNAME]->GetFade()->nTiming;
	pC2dui[TITLEUI_PRESSENTERNAME]->GetFade()->nAddSign = 1;
	// �v���X�G���^�[�A�C�R���̐ݒ�
	set[TITLEUI_PRESSENTERICON].mask.unMask = C2DUi::MASK_FADE | C2DUi::MASK_FLASHING;
	// �v���X�G���^�[�̃A�C�R������
	pC2dui[TITLEUI_PRESSENTERICON] = C2DUi::Create(set[TITLEUI_PRESSENTERICON]);
	pC2dui[TITLEUI_PRESSENTERICON]->GetFade()->bLoop = true;
	pC2dui[TITLEUI_PRESSENTERICON]->GetFade()->nTiming = 30;
	pC2dui[TITLEUI_PRESSENTERICON]->GetFade()->fChangeValue = 1.0f / pC2dui[TITLEUI_PRESSENTERICON]->GetFade()->nTiming;
	pC2dui[TITLEUI_PRESSENTERICON]->GetFade()->nAddSign = 1;
	this->m_State = STATE_NORMAL;

	CMode::Init(STATE_NORMAL, 30);
}

//-------------------------------------------------------------------------------------------------------------
// �I��
//-------------------------------------------------------------------------------------------------------------
void CTitle::Uninit(void)
{
}

//-------------------------------------------------------------------------------------------------------------
// �X�V
//-------------------------------------------------------------------------------------------------------------
void CTitle::Update(void)
{
	if (this->m_State == STATE_NORMAL)
	{
		pC2dui[TITLEUI_NAME]->GetFade()->Update(pC2dui[TITLEUI_NAME]->GetImage());
		pC2dui[TITLEUI_PRESSENTERNAME]->GetFade()->Update(pC2dui[TITLEUI_PRESSENTERNAME]->GetImage());
		pC2dui[TITLEUI_PRESSENTERICON]->GetFade()->Update(pC2dui[TITLEUI_PRESSENTERICON]->GetImage());
	}
	else if (this->m_State == STATE_OUT)
	{
		pC2dui[TITLEUI_NAME]->GetFlashing()->Update(pC2dui[TITLEUI_NAME]);
		pC2dui[TITLEUI_PRESSENTERNAME]->GetFlashing()->Update(pC2dui[TITLEUI_PRESSENTERNAME]);
		pC2dui[TITLEUI_PRESSENTERICON]->GetFlashing()->Update(pC2dui[TITLEUI_PRESSENTERICON]);
		if (this->m_nCntState == this->m_nMaxCntState)
		{
			CManager::GetRenderer().GetFade()->SetFade(CManager::MODE_TUTORIAL);
		}
		this->m_nCntState++;
	}
	if (CManager::GetKeyboard().GetTrigger(DIK_RETURN))
	{
		this->SetState(STATE_OUT);
	}
#ifdef _DEBUG
	// �e�X�g�p�[�e�B�N��
	if (CManager::GetKeyboard().GetTrigger(DIK_SPACE))
	{
		C3DParticle::Create(C3DParticle::PARTICLE_ID_EXPLOSION, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
#endif // _DEBUG

}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void CTitle::Draw(void)
{
}
