#include "DxLib.h"
#include "app.h"
#include "Source.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(FALSE);	//�E�B���h�E���[�h�ɂ���
	SetGraphMode(1024, 900, 32);	//�E�B���h�E�T�C�Y��ݒ肷��

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);	//����ʂ�`��Ώۂ�

	//Init����
	AppInit();
	//���C������
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){

		//Update����
		AppUpdate();
		//Draw����
		AppDraw();
		ScreenFlip();		//����ʂƕ\��ʂ̓���
		ClearDrawScreen();	//����ʂ̕`���S�ď���
	}
	AppRelease();
	DxLib_End();			// �c�w���C�u�����g�p�̏I������

  	return 0;				// �\�t�g�̏I�� 
}