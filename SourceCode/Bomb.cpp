//*************************************************************************************************************
//
// �v���C���[���� [player.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "Bomb.h"
#include "Scene2D.h"
#include "texture.h"
#include "game.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------
#define BOMB_BASEFORCE 20.0f


//-------------------------------------------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------------------------------------------
CBomb * CBomb::Create(D3DXVECTOR3 & pos, D3DXVECTOR2 & size, int nPlayer_ID)
{
	CBomb *pPlayer = new CBomb;
	pPlayer->Init(pos, size, nPlayer_ID);
	pPlayer->SetObjectTyoe(TYPE_BULLET);
	return pPlayer;
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
void CBomb::Init(D3DXVECTOR3 & pos, D3DXVECTOR2 & size, int &nPlayer_ID)
{
	m_nPlayer_ID = nPlayer_ID;
	m_pScene2D = CScene2D::Create(PRIORITY::PRIORITY_PLAYER, pos, ORIGINVERTEXTYPE::ORIGINVERTEXTYPE_ROTCENTER, size);
	m_pScene2D->BindTexture(CTexture::GetTextureInfo(CTexture::NAME_PLAYER));
	m_State = STATE_STANDBY;
}

//-------------------------------------------------------------------------------------------------------------
// �I��
//-------------------------------------------------------------------------------------------------------------
void CBomb::Uninit(void)
{
}

//-------------------------------------------------------------------------------------------------------------
// �X�V
//------------------------------------------------------------------------------------------------------------
void CBomb::Update(void)
{
	switch (m_State)
	{
		MLB_CASE(STATE_STANDBY)UpdateStandby();
		MLB_CASE(STATE_MOVEING)UpdateMoveing();
		MLB_CASE(STATE_LANDING)UpdateLanding();
	default:
		break;
	}
}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void CBomb::Draw(void)
{
	if (m_pScene2D != nullptr)
	{
		m_pScene2D->Draw();
	}
}

void CBomb::UpdateStandby(void)
{
}

void CBomb::UpdateMoveing(void)
{
	// �ʒu�̎擾
	D3DXVECTOR3 *pos = 	m_pScene2D->GetPosition();

	*pos += m_move;
	m_move.y += 0.5f;


	//if (pos->y >= 600.0f)
	//{
	//	pos->y = 600.0f;
	//	m_State = STATE_LANDING;
	//}

	m_pScene2D->UpdateVatexPosition();
}

void CBomb::UpdateLanding(void)
{
}

void CBomb::Fire(float & fForce, float & fForceY)
{
	if (m_nPlayer_ID == CGame::PLAYER_1)
	{
		m_move.x = BOMB_BASEFORCE*fForce;
	}
	else
	{
		m_move.x = BOMB_BASEFORCE*-fForce;
	}
	m_move.y = -BOMB_BASEFORCE*fForceY;

	m_State = STATE_MOVEING;
}