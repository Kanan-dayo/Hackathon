//*************************************************************************************************************
//
// �Q�[������ [game.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
#ifndef _GAME_H_
#define _GAME_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "mode.h"

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class C2DUi;
class CPlayer;
class CBomb;
class CGame : public CMode
{
public:
	enum
	{
		UI_BG = 0,
		UI_TIMER,

		UI_P1_GAGE_X,
		UI_P1_GAGE_Y,
		UI_P2_GAGE_X,
		UI_P2_GAGE_Y,

		UI_P1_FRAME_X,
		UI_P1_FRAME_Y,
		UI_P2_FRAME_X,
		UI_P2_FRAME_Y,

		UI_MAX,
	};

	enum
	{
		SCAL_P1_GAGE_X,
		SCAL_P1_GAGE_Y,
		SCAL_P2_GAGE_X,
		SCAL_P2_GAGE_Y,
		SCAL_P2_GAGE_MAX,
	};

	enum
	{
		PLAYER_NONE = -1,
		PLAYER_1,
		PLAYER_2,
		PLAYER_MAX,
	};


	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR2 size;
	} PLAYEROFFSET;

	CGame() {};					// �R���X�g���N�^
	~CGame() {};					// �f�X�g���N�^

	static CGame *Create(void);	// ����
	void Init(void);				// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��

private:
	void UpdateNormal(void);		// �ʏ�X�V
	void UpdateOut(void);			// �A�E�g�X�V

	void GageUpdate(void);
	void GageScaForceShuffle(float *pGageScalForce);
	bool GageScalClamp(float *pGageScal,int *pSign);

	C2DUi *pC2dui[UI_MAX];					// �QDUI�|�C���^
	CPlayer *m_pPlayer[PLAYER_MAX];				// �v���C���|�C���^
	CBomb *m_pBomb[PLAYER_MAX];				// ���e�|�C���^
	static PLAYEROFFSET m_offset[PLAYER_MAX];

	float m_fGageScal[SCAL_P2_GAGE_MAX];
	float m_fGageScaForce[SCAL_P2_GAGE_MAX];
	int m_fGageScaSign[SCAL_P2_GAGE_MAX];
	bool m_bMoveGage[SCAL_P2_GAGE_MAX];
};

#endif