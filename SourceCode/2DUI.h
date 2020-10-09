//*************************************************************************************************************
//
// 2DUI����[2DUI.h]
// Author : Sekine Ikuto
//
//*************************************************************************************************************
#ifndef _2DUI_H_
#define _2DUI_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "Scene.h"

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class CNumericString;
class CScene2D;
class C2DUi : public CScene
{
public:
	enum
	{
		MASK_NONE = 0b00000000,
		MASK_NUMBER = 0b00000001,
		MASK_FLASHING = 0b00000010,
		MASK_FADE = 0b00000100,
		MASK_MAX = 0b00000111,
	};
	enum
	{
		FLAG_NONE = -1,
		FLAG_NUMBER,
		FLAG_FLASHING,
		FLAG_FADE,
		FLAG_MAX
	};
	typedef struct
	{
		unsigned int bNumber : 1;
		unsigned int bFlashing : 1;
		unsigned int bFade : 1;
	} _MASK;

	typedef union MASK
	{
		MASK(int n = 0) : unMask(n) {}
		unsigned int unMask;
		_MASK field;
	} MASK;
	typedef struct FLASHING
	{
		UINT m_nTiming;															// �_��
		bool IsEqual(UINT &nTiming) { return (nTiming >= m_nTiming); }
		void Update(C2DUi *pThis);

	} FLASHING;

	typedef struct FADE
	{
		bool  bLoop;															// ���[�v
		float fChangeValue;														// �A���t�@�l��1�t���̕ύX�l
		int   nTiming;															// �^�C�~���O
		int   nAddSign;															// ���Z���镄��

		inline void   SetChangeValue(float fChangeValue) { fChangeValue = fChangeValue; }											// 1�t���̕ύX�l�̐ݒ�
		inline float& GetChangeValue(void) { return fChangeValue; }																	// 1�t���̕ύX�l�̎擾
		inline void   SetAddSign(int nAddSign) { if (nAddSign != 0)nAddSign = (nAddSign / nAddSign) * (nAddSign > 0) ? 1 : -1; }	// ���Z���镄���̐ݒ�
		inline int&   GetAddSign(void) { return nAddSign; }																			// ���Z���镄���̎擾

		void Update(CScene2D *pImage);
		void Update(CNumericString *m_pNumber);
	} FADE;

	typedef struct SETING2DUI
	{
		SETING2DUI() {}
		SETING2DUI(MASK mask, int  nTextureID, bool bDisp, D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR2 size, float fRotation, int nValue)
		{
			this->mask = mask;
			this->nTextureID = nTextureID;
			this->bDisp = bDisp;
			this->pos = pos;
			this->col = col;
			this->size = size;
			this->fRotation = fRotation;
			this->nValue =nValue;
		}
		MASK        mask;			// �}�X�N
		int         nTextureID;		// �e�N�X�`��ID
		bool        bDisp;			// �`��t���O
		D3DXVECTOR3 pos;			// �ʒu
		D3DXCOLOR   col;			// �F
		D3DXVECTOR2 size;			// �T�C�Y
		float       fRotation;		// ��]��
		int         nValue;			// �l
	} SETING2DUI;

	C2DUi(PRIORITY pri) : CScene(pri) {}																							// �R���X�g���N�^
	~C2DUi() {}																													// �f�X�g���N�^

	static C2DUi * Create(SETING2DUI &seting, PRIORITY pri = PRIORITY_2DUI);																					// ����
	void Init(SETING2DUI &seting, PRIORITY pri);																								// ������
	void Init(void);																											// ������
	void Uninit(void);																											// �I��
	void Update(void);																											// �X�V
	void Draw(void);																											// �`��

	static bool   AlphaLimitRange(D3DXCOLOR &col);																						// �A���t�@�l��͈͓��ɐ�������
	inline void   ChangeDispFlag(void) { this->m_bDisp ^= 1; }																	// �`��t���O�̐؂�ւ�

	inline void   SetTime(UINT nChangeTime) { m_nTime = nChangeTime; }													// ���Ԃ̐ݒ�
	inline UINT&  GetTime(void) { return m_nTime; }																		// ���Ԃ̎擾
	inline void   SetTextureID(int nTextureID) { m_nTextureID = nTextureID; }													// �e�N�X�`��ID�̐ݒ�
	inline int&   GetTextureID(void) { return m_nTextureID; }																	// �e�N�X�`��ID�̎擾
	inline void   SetDisp(bool bDisp) { m_bDisp = bDisp; }																		// �`��t���O�̐ݒ�
	inline bool&  GetDisp(void) { return m_bDisp; }																				// �`��t���O�̎擾

	inline FLASHING *GetFlashing(void) { return m_pFlashing; }
	inline FADE *GetFade(void) { return m_pFade; }
	inline CNumericString *GetNumericString(void) { return m_pNumber; }
	inline CScene2D *GetImage(void) { return m_pImage; }


protected:
	// ����
	int   m_nTextureID;															// �e�N�X�`��ID
	UINT  m_nTime;																// ����
	bool  m_bDisp;																// �`��t���O

	MASK m_Mask;																// �}�X�N

	FLASHING *m_pFlashing;														// �_��
	FADE* m_pFade;																// �t�F�[�h
	CNumericString *m_pNumber;													// ����
	CScene2D *m_pImage;															// �摜
};


#endif