//*************************************************************************************************************
//
// �^�C�g������ [title.h]
// Author:IKUTO SEKINE
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
	C2DUi::SETING2DUI set[2];	// UI�ݒ�p�ϐ�
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
	// �^�C�g���̐���
	C2DUi::Create(set[0]);

	// �v���X�G���^�[�̐ݒ�
	set[1].mask.unMask = C2DUi::MASK_FADE | C2DUi::MASK_FLASHING;
	set[1].nValue = 123456789;
	// �v���X�G���^�[�̐���
	pC2dui = C2DUi::Create(set[1]);
	pC2dui->GetFade()->bLoop = true;
	pC2dui->GetFade()->nTiming = 30;
	pC2dui->GetFade()->fChangeValue = 1.0f / pC2dui->GetFade()->nTiming;
	pC2dui->GetFade()->nAddSign = 1;
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
		pC2dui->GetFade()->Update(pC2dui->GetImage());
	}
	else if (this->m_State == STATE_OUT)
	{
		pC2dui->GetFlashing()->Update(pC2dui);
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
