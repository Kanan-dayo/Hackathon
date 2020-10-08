//*************************************************************************************************************
//
// タイトル処理 [title.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// インクルードファイル
//-------------------------------------------------------------------------------------------------------------
#include "title.h"
#include "2DUI.h"

//-------------------------------------------------------------------------------------------------------------
// 生成
//-------------------------------------------------------------------------------------------------------------
CTitle * CTitle::Create(void)
{
	CTitle *pTitle = new CTitle;
	pTitle->Init();
	return pTitle;
}

//-------------------------------------------------------------------------------------------------------------
// 初期化
//-------------------------------------------------------------------------------------------------------------
void CTitle::Init(void)
{
	C2DUi::SETING2DUI set;
	set.bDisp = true;
	set.col = MYLIB_D3DXCOR_SET;
	set.fRotation = 0.0f;
	set.mask.unMask = C2DUi::MASK_FADE | C2DUi::MASK_NUMBER;
	set.nTextureID = 1;
	set.nValue = 123456789;
	set.pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	set.size = D3DXVECTOR2(60.0f, 120.0f);
	pC2dui = C2DUi::Create(set);

	pC2dui->GetFade()->bLoop = true;
	pC2dui->GetFade()->nTiming = 30;
	pC2dui->GetFade()->fChangeValue = 1.0f / pC2dui->GetFade()->nTiming;
	pC2dui->GetFade()->nAddSign = 1;

	//pC2dui->GetFlashing()->m_nTiming = 20;
}

//-------------------------------------------------------------------------------------------------------------
// 終了
//-------------------------------------------------------------------------------------------------------------
void CTitle::Uninit(void)
{
}

//-------------------------------------------------------------------------------------------------------------
// 更新
//-------------------------------------------------------------------------------------------------------------
void CTitle::Update(void)
{
	pC2dui->GetFade()->Update(pC2dui->GetNumericString());
	//pC2dui->GetFlashing()->Update(pC2dui);
}

//-------------------------------------------------------------------------------------------------------------
// 描画
//-------------------------------------------------------------------------------------------------------------
void CTitle::Draw(void)
{
}
