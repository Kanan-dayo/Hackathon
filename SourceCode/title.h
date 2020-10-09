//*************************************************************************************************************
//
// �^�C�g������ [title.h]
// Author:KOKI NISHIYAMA
//
//*************************************************************************************************************
#ifndef _TITLE_H_
#define _TITLE_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "mode.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class C2DUi;
class CTitle : public CMode
{
public:
	/* �񋓌^ */
	// �^�C�g��UI
	typedef enum
	{
		TITLEUI_BG = 0,			// �w�i
		TITLEUI_NAME,			// ���O
		TITLEUI_PRESSENTERNAME,	// �v���X�G���^�[��
		TITLEUI_PRESSENTERICON,	// �v���X�G���^�[�A�C�R��
		TITLEUI_PLAYER1ICON,	// �v���C���[1�A�C�R��
		TITLEUI_PLAYER2ICON,	// �v���C���[2�A�C�R��
		TITLEUI_PIEN1,			// �s�G��1
		TITLEUI_PIEN2,			// �s�G��2
		TITLEUI_MAX
	} TITLEUI;

	// �g�嗦���
	typedef struct SCALING
	{
		SCALING()
		{
			OriginSize = D3DXVECTOR2(0.0f,0.0f);
			fScal = 1.0f;
			fScalChange = 0.0f;
			fScalDiff = 0.0f;
			nTimeChange = 0;
			nCntTimeChange = 0;
			bChange = false;
		}
		D3DXVECTOR2 OriginSize;			// ���̃T�C�Y
		float fScal;					// �g�嗦
		float fScalChange;				// �ڕW�g�嗦
		float fScalDiff;				// �g�嗦�㏸��
		int nTimeChange;				// �؂�ւ�鎞��
		int nCntTimeChange;				// �؂�ւ�鎞�ԃJ�E���g
		bool bChange;					// �؂�ւ�蒆
	} SCALING, *P_SCALING;

	/* �֐� */
	CTitle() {};					// �R���X�g���N�^
	~CTitle() {};					// �f�X�g���N�^

	static CTitle *Create(void);	// ����
	void Init(void);				// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��

private:
	/* �֐� */
	// �T�C�Y�ύX�̍X�V����
	void Update_SizeChange(void);
	// �p�x�ύX�̍X�V����
	void Update_RotChange(void);
	/* �ϐ� */
	C2DUi *pC2dui[TITLEUI_MAX];					// �QDUI�|�C���^
	SCALING m_Scal;								// �g�嗦
	float m_fRotChange[2];						// �p�x�ύX�l
};

#endif