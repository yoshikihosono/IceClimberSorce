#include "MovieScene.h"
#include "DxLib.h"
#include "assert.h"

/*�ŏI�X�V�F2020/8/30*/
/*���[�r�[�̃\�[�X*/

MovieScene::MovieScene()
{
	// ���[�r�[�t�@�C�������[�h���܂��B
	MovieGraphHandle = LoadGraph("data\\texture\\Ice.mp4");

}

MovieScene::~MovieScene()
{
}

void MovieScene::Update()
{
	// ���[�r�[���Đ���Ԃɂ��܂�
	PlayMovieToGraph(MovieGraphHandle);

	// ���[�r�[�f������ʂ����ς��ɕ`�悵�܂�
	DrawGraph(-125, 210, MovieGraphHandle, TRUE);

}