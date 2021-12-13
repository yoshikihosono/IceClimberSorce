#include "Whitebear.h"
#include "Player.h"
#include "DxLib.h"
#include "assert.h"
#include "PlayScene.h"
#include "Map.h"
#include "Seal.h"
#include "Knit picker.h"
#include "Wall.h"
#include "Cloud.h"
#include "Timer.h"
#include "Condor.h"
#include "Eggplant.h"
#include "Floor.h"
#include "app.h"

/*�ŏI�X�V�F2020/8/30*/
/*�V���N�}�̃\�[�X*/

Whitebear::Whitebear(PlayScene * _scene)
{
	scene = _scene;
	image = LoadGraph("data\\texture\\Whitebare.png");
	x = 0;
	y = 0;
	RefY = 65;
	alive = false;
	action = false;
	rightward = true;
	AppearCount = 2100;
}

Whitebear::~Whitebear()
{
}

void Whitebear::Update()
{
	//�{�[�i�X�X�e�[�W����Ȃ���
	if (!scene->Getplayer()->BonusStage)
	{
		//�����ĂȂ���
		if (!alive)
		{
			//�v���C���[��Y�l���A�U���V6�̖ڂ̕��A�ʒu��荂����
			if (scene->Getplayer()->y > scene->Getseal()->RefY[5])
			{
				//�o������܂ł̃J�E���g��0�����Ȃ�
				if (AppearCount < 0)
				{
					y = RefY;	
					x = 0 - bearWidth;
					alive = true;
					rightward = true;
				}
			}
		}
		//�����Ă�
		else
		{
			//1�}�X�悪�n�ʂ�
			if (!scene->Getmap()->MapChip[150 - (33 - ((y + bearHeight) / 27))][(x + bearWidth) / 32] == 0)
			{
				//�A�N�V�������ĂȂ���
				if (!action)
				{
					//�E�����Ȃ�
					if (rightward)
					{
						x++;
						moveCount++;
						animCounter++;
					}
					//�������Ȃ�
					else
					{
						x--;
						moveCount++;
						animCounter++;
					}
				}
				//�A�N�V�����t���O��true�Ȃ�
				else
				{
					moveCount++;

					/*�^���W�����v*/
					if (moveCount > 600 && moveCount < 605)
					{
						y--;
					}

					if (moveCount > 605 && moveCount < 610)
					{
						y++;
					}
					/*�^���W�����v*/

					/*��ʓ��O�̕����ׂĂ�������*/
					if (moveCount > 610)
					{
						/*�}�b�v*/
						for (int y = MapY - 1; y > 6; y--)
						{
							for (int x = 0; x < MapX; x++)
							{
								scene->Getmap()->MapChip[y][x] = scene->Getmap()->MapChip[y - 8][x];
							}
						}
						/*�}�b�v*/

						/*�A�U���V*/
						for (int i = 0; i < 6; i++)
						{
							scene->Getseal()->y[i] += 216;
							scene->Getseal()->RefY[i] += 216;
							scene->Getseal()->iceY[i] += 216;
							/*��*/
							scene->Getwall()->LeftY[i] += 216;
							scene->Getwall()->RightY[i] += 216;
							/*��*/
						}
						/*�A�U���V*/

						/*�_*/
						for (int i = 0; i < 2; i++)
						{
							scene->Getcloud()->y[i] += 216;
						}
						/*�_*/

						/*�i�X*/
						for (int i = 0; i < 4; i++)
						{
							scene->Geteggplant()->y[i] += 216;
						}
						/*�i�X*/

						/*�w�i�̂��*/
						for (int i = 0; i < 8; i++)
						{
							scene->Getfloor()->LeftY[i] += 216;
							scene->Getfloor()->RightY[i] += 216;
						}
						/*�w�i�̂��*/

						scene->Getplayer()->TempY += 216;		//�v���C���[
						scene->Getknitpicker()->RefY += 216;	//��
						scene->Getknitpicker()->y += 216;		//��
						y += 216;	//�V���N�}���g
						scene->Getwall()->LeftY[6] += 216;	//�{�[�i�X�X�e�[�W�̕�
						scene->Getwall()->RightY[6] += 216;	//�{�[�i�X�X�e�[�W�̕�
						scene->Getcondor()->y += 216;	//�R���h��
						scene->Gettimer()->y += 216;	//�^�C�}�[
						scene->Gettimer()->y2 += 216;	//�^�C�}�[2
						scene->Getplayer()->ScrollCount++;	//�v���C���[�̃X�N���[���񐔂�1���₷
						action = false;	//�A�N�V�����t���O��false��
						moveCount = 620;	//�ړ��p�J�E���g��620�ɌŒ�
						AppearCount = 2500;	//�o������܂ł̃J�E���g��2500��
					}
					/*��ʓ��O�̕����ׂĂ�������*/
				}
			}
			//1�}�X�悪�n�ʂ���Ȃ�
			else
			{
				if (!hit)
				{
					//�E�����Ȃ�
					if (rightward)
					{
						rightward = false;
						x -= 10;
					}
					//�������Ȃ�
					else
					{
						rightward = true;
					}
				}
				//����ꂽ��
				else
				{
					y++;
				}
			}
		}
	}
	//�{�[�i�X�X�e�[�W�Ȃ�
	else
	{
		alive = false;	//���낷
	}

	//���[�ɍs������
	if (x < 0 - bearWidth)
	{
		//movecount��620�ȏ�Ȃ�
		if (moveCount > 620)
		{
			alive = false;	//���낷
		}
		else
		{
			x = 1024;	//�E�[��
		}
	}

	//�E�[�ɂ���
	if (x > 1024)
	{
		//movecount��620�ȏ�Ȃ�
		if (moveCount > 620)
		{
			alive = false;	//���낷
		}
		else
		{
			x = 0 - bearWidth;	//���[��
		}
	}

	//movecount��600�Ȃ�
	if (moveCount == 600)
	{
		action = true;	//�W�����v�A�N�V������true��
	}

	AppearCount--;
}

void Whitebear::Draw()
{
	int tx;

	if (hit)
	{
		tx = 0;
		pattern = 1 * bearHeight;
	}
	else
	{
		tx = animCounter % 3 * bearWidth;
		pattern = 0 * bearHeight;
	}

	if (alive)
		DrawRectGraph(x, y, tx, pattern, bearWidth, bearHeight, image, true, rightward);
}

bool Whitebear::Collision(int px, int py, int pw, int ph, int sx, int sy, bool sHit)
{
	if (!sHit)
	{
		if (px > sx + width)
		{
			return false;
		}


		if (px + pw < sx)
		{
			return false;
		}

		if (py > sy + height)
		{
			return false;
		}

		if (py + ph < sy)
		{
			return false;
		}

		return true;

	}
	else
	{
		return false;
	}
}
