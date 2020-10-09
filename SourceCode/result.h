//*************************************************************************************************************
//
// ���U���g���� [result.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
#ifndef _RESULT_H_
#define _RESULT_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "mode.h"

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class C2DUi;
class CScore;

class CResult : public CMode
{
public:
	CResult() {};					// �R���X�g���N�^
	~CResult() {};					// �f�X�g���N�^

	static void SetWinPlayer(const int nPlayer) { m_nWinPlayer = nPlayer; }
	static int GetWinPlayer(void)				{ return m_nWinPlayer; }

	static CResult *Create(void);	// ����
	void Init(void);				// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��

private:
	C2DUi *pPienDistance[MAX_PLAYER];					// �QDUI�|�C���^
	C2DUi *pPienIcon[MAX_PLAYER];						// �҂���̃A�C�R��
	C2DUi *pJudgeText[MAX_PLAYER];						// ���s�̕���
	CScore *m_pScore[MAX_PLAYER];						// �v���C���[�̃X�R�A
	static int m_nWinPlayer;							// �������v���C���[�̃C���f�b�N�X
	static D3DXVECTOR3 m_posScore[MAX_PLAYER];			// �X�R�A�̍��W
	static D3DXVECTOR2 m_sizeScore[MAX_PLAYER];			// �X�R�A�̃T�C�Y
	static D3DXVECTOR3 m_posPien[MAX_PLAYER];			// �҂���̍��W
	static D3DXVECTOR3 m_posText[MAX_PLAYER];			// ���͂̍��W
};

#endif