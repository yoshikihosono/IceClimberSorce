#include "Knit picker.h"
#include "DxLib.h"
#include "time.h"
#include "assert.h"

/*�ŏI�X�V�F2020/8/30*/
/*���̃\�[�X*/

Knitpicker::Knitpicker(PlayScene * _scene)
{
	image = LoadGraph("data\\texture\\Knitpicker.png");
	RefY = -320;
	x = 0.0f;
	y = RefY;
	alive = false;
	Hit = false;
	Count = 30;
	MoveCounter = 0;
	animCounter = 0;
	spawn = 0;
}

Knitpicker::~Knitpicker()
{
}

void Knitpicker::Update()
{
	srand((unsigned int)time(NULL));

	if (RefY > 0)
	{
		if (!alive)
		{
			if (Count <= 0)
			{
				spawn = rand() % 2;	//���E�ǂ�������o�邩���߂܂�
				x = 1024 * spawn;
				y = RefY;
				MoveCounter = 0;
				Hit = false;
				alive = true;	//���������܂�
				if (spawn == 0)		//���܂ꂽ�ꏊ�ŉE�������ǂ����ݒ肷���
				{
					rightward = true;
				}
				else
				{
					rightward = false;
				}
			}
		}
		else
		{
			if (!Hit)	//�����ĂȂ���
			{
				if (spawn == 0)	//�E�����Ȃ�
				{
					/*�ړ�����*/
					if (MoveCounter < 150 || MoveCounter > 170 && MoveCounter < 190 || MoveCounter > 840)
					{
						y += 1.25f;
					}

					if (MoveCounter > 150 && MoveCounter < 170)
					{
						y -= 0.75;
					}

					if (MoveCounter > 190 && MoveCounter < 400)
					{
						y += 0.5;
					}

					if (MoveCounter > 400 && MoveCounter < 620)
					{
						y -= 0.5;
					}

					if (MoveCounter > 650 && MoveCounter < 840)
					{
						y -= 1.25f;
					}

					if (MoveCounter < 150 || MoveCounter > 180 && MoveCounter < 620)
					{
						x += 1.5f;
					}

					if (MoveCounter > 670)
					{
						x -= 2.0f;
					}

					if (MoveCounter == 620)
					{
						rightward = false;
					}

					if (MoveCounter == 1000)
					{
						MoveCounter = 150;
						rightward = true;
					/*�ړ�����*/
					}


					animCounter++;
					MoveCounter++;
				}
				else if(spawn == 1)	//�������Ȃ�
				{
					/*�ړ�����*/
					if (MoveCounter < 150 || MoveCounter > 170 && MoveCounter < 190 || MoveCounter > 840)
					{
						y += 1.25f;
					}

					if (MoveCounter > 150 && MoveCounter < 170)
					{
						y -= 0.75;
					}

					if (MoveCounter > 190 && MoveCounter < 400)
					{
						y += 0.5;
					}

					if (MoveCounter > 400 && MoveCounter < 620)
					{
						y -= 0.5;
					}

					if (MoveCounter > 650 && MoveCounter < 840)
					{
						y -= 1.25f;
					}

					if (MoveCounter < 150 || MoveCounter > 180 && MoveCounter < 620)
					{
						x -= 1.5f;
					}

					if (MoveCounter > 670)
					{
						x += 2.0f;
					}

					if (MoveCounter == 620)
					{
						rightward = true;
					}

					if (MoveCounter == 1000)
					{
						MoveCounter = 150;
						rightward = false;
					}
					/*�ړ�����*/


					animCounter++;
					MoveCounter++;
				}

			}
			else
			{
				y += 3;
			}
		}
	}

	if (y > 900)
	{
		alive = false;
		Count = 300;
	}

	Count--;
}

//�`��
void Knitpicker::Draw()
{
	int tx;

	if (Hit)	//����ꂽ��
	{
		tx = 0 * 60;
		pattern = 1 * 60;
	}
	else
	{
		tx = (animCounter / 6) % 2 * 60;
		pattern = 0;
	}


	if (alive)	//�����Ă���Ȃ�
		DrawRectGraph(x, y, tx, pattern, 60, 60, image, true, rightward);
}

//�����蔻��
bool Knitpicker::Collision(int px, int py, int pw, int ph)
{
	if (!Hit)
	{
		if (px > x + Knitwidth)
		{
			return false;
		}


		if (px + pw < x)
		{
			return false;
		}

		if (py > y + Knitheight)
		{
			return false;
		}

		if (py + ph < y)
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
