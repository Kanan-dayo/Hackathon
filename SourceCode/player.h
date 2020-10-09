//*************************************************************************************************************
//
// �v���C���[���� [player.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "Scene.h"

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class C2DUi;
class CScene2D;
class CPlayer : public CScene
{
public:

	typedef enum
	{
		STATE_NOEN = -1,
		STATE_STANDBY,
		STATE_THROW,
		STATE_EXPOSURE,
		STATE_NOTEXPOSURE,
		STATE_MAX,
	}STATE;


	CPlayer():CScene(PRIORITY_PLAYER){};		// �R���X�g���N�^
	~CPlayer() {};								// �f�X�g���N�^

	static CPlayer *Create(D3DXVECTOR3 &pos, D3DXVECTOR2 &size);				// ����
	void Init(D3DXVECTOR3 &pos, D3DXVECTOR2 &size);							// ������
	void Init(void) {};							// ������
	void Uninit(void);							// �I��
	void Update(void);							// �X�V
	void Draw(void);							// �`��

	void UpdateStandby(void);
	void UpdateThrow(void);

	void SetState(STATE state) { m_State = state; }
	STATE & GetState(void) { return m_State; }

	CScene2D *GetScene2D(void) { return m_pScene2D; }

	D3DXVECTOR3 &GetPos(void);
private:
	CScene2D *m_pScene2D;					// �V�[���QD�|�C���^
	STATE     m_State;						// ���
};

#endif