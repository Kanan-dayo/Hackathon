//*************************************************************************************************************
//
// ���C�g���� [light.h]
// Author : IKUTO SEKINE
//
//*************************************************************************************************************
#ifndef _LIGHT_H_
#define _LIGHT_H_

#define _CRT_SECURE_NO_WARNINGS

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "main.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------
#define LIGHT_MAX		(3)		// ���C�g�̍ő吔

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class CLight
{
public:
	void Init(void);				// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	static CLight *Create(void);	// ����
	// ���C�g�̕����̐ݒ�
	void SetDirection(void);
	// ���C�g���̎擾
	D3DLIGHT9 *GetLight(int nNumLight = 0);
private:
	D3DLIGHT9 m_aLight[LIGHT_MAX];		// ���C�g���
};

#endif