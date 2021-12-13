#include "Player.h"
#include "DxLib.h"
#include "assert.h"
#include "PlayScene.h"
#include "Map.h"
#include "Seal.h"
#include "Knit picker.h"
#include "Whitebear.h"
#include "Wall.h"
#include "Cloud.h"
#include "Timer.h"
#include "Condor.h"
#include "Eggplant.h"
#include "Floor.h"
#include "app.h"
#include "ResultScene.h"

/*�ŏI�X�V�F2020/8/30*/
/*�v���C���[�̃\�[�X*/

static const float G = 9.8f * 3.0f / 60.0f;


Player::Player(PlayScene* _scene)
{
	scene = _scene;
	image = LoadGraph("data\\texture\\Player4.png");	//�v���C���[�̉摜
	Lifeimage = LoadGraph("data\\texture\\Life.png");	//�c�@�̉摜
	GameOverimage = LoadGraph("data\\texture\\Gameover.png");	//�Q�[���I�[�o�[�̃O���t
	Life = 3;	//�c�@
	LifeX = 224;	//�c�@�̕\���ʒu
	LifeY = 80;		//�c�@�̕\���ʒu
	x = 400;	//���@�̏����ʒu
	y = 700;	//���@�̏����ʒu
	TempX = x;	//���@�̈ꎞ�I���W
	TempY = y;	//���@�̈ꎞ�I���W
	HummerX = x;	//�n���}�[�̍��W
	HummerY = y;	//�n���}�[�̍��W
	beforeJump = y;	//�W�����v�O�̍��W
	OverX = 100;	//�Q�[���I�[�o�[�̉摜�̍��W
	OverY = 1000;	//�Q�[���I�[�o�[�̉摜�̍��W
	velX = 0.0f;	//�ړ��X�s�[�h
	velY = 0.0f;	//�������x
	jumping = false;	//�W�����v�t���O
	PushJump = false;	//�W�����v�{�^���������ꂽ��
	RestTime = 0;	//���G����
	ScrollCount = 0;	//�X�N���[��������
	BonusStage = false;	//�{�[�i�X�X�e�[�W�ɓ�������
	Clear = false;	//�{�[�i�X�X�e�[�W���N���A������
	Failed = false;	//�{�[�i�X�X�e�[�W�����s������
	Scrolling = false;	//�X�N���[�����Ă�r�����H
	RefY = 715;
	Accel = 0;
}

Player::~Player()
{
	DeleteGraph(image);
}

void Player::Update()
{
	if (!Clear && !Failed)
	{
		/*���@����*/
		/*�W�����v*/
		if (CheckHitKey(KEY_INPUT_Z) && PushJump == false && !Hit)
		{
			reverse = false;
			jumping = true;
			PushJump = true;
			beforeJump = y;
			Accel = 0;
		}
		/*�W�����v*/
		/*�n���}�[*/
		else if (CheckHitKey(KEY_INPUT_X) && PushJump == false && !Hit)
		{
			Attacking = true;
			animCounter++;
			velX = 0;
		}
		/*�n���}�[*/
		/*�E�ړ�*/
		else if (CheckHitKey(KEY_INPUT_RIGHT) && !Hit)
		{
			//�W�����v���Ă��Ȃ��Ȃ�
			if (!PushJump)
			{
				animCounter++;
			}
			velX = 5;

			//�X�̏��Ȃ�
			if (scene->Getmap()->MapChip[150 - (33 - ((TempY + 20 + PHeight) /  BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] == 9 ||
				scene->Getmap()->MapChip[150 - (33 - ((TempY + 20 + PHeight) /  BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] == 10)
			{
				if (Accel < 7)
					Accel += 0.3;
			}
			Rightward = true;
		}
		/*�E�ړ�*/
		/*���ړ�*/
		else if (CheckHitKey(KEY_INPUT_LEFT) && !Hit)
		{
			//�W�����v���Ă��Ȃ��Ȃ�
			if (PushJump == false)
			{
				animCounter++;
			}
			velX = 5;

			//�X�̏��Ȃ�
			if (scene->Getmap()->MapChip[150 - (33 - ((TempY + 20 + PHeight) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] == 9 ||
				scene->Getmap()->MapChip[150 - (33 - ((TempY + 20 + PHeight) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] == 10)
			{
				if (Accel < 7)
					Accel += 0.3;
			}
			Rightward = false;
		}
		/*���ړ�*/
		//�ǂ���ł��Ȃ�
		else
		{
			//�G�ɂ��������Ă��Ȃ�
			if (!Hit)
			{
				animCounter = 0;
			}

			velX = 0;
			pattern = 0 * 120;
			Attacking = false;
		}

		//�U���p�̃L�[��������Ă��Ȃ��Ȃ�
		if (!CheckHitKey(KEY_INPUT_X))
		{
			Attacking = false;
		}
		/*���@����*/

		/*����*/
		if (!jumping)
		{
			velY += G;
		}
		/*����*/

		/*�ړ�*/
		//�E�����̂Ƃ�
		if (Rightward)
		{
			TempX += velX;
			if (Accel > 0)
			{
				TempX += Accel;
				Accel -= 0.1;
			}
		}
		else
		{
			TempX -= velX;

			if (Accel > 0)
			{
				TempX -= Accel;
				Accel -= 0.1;
			}
		}
		/*�ړ�*/

		/*�[�܂ōs�����甽�΂���*/
		if (TempX > 1024)
		{
			TempX = -68;
		}
		if (TempX < -68)
		{
			TempX = 1024;
		}
		/*�[�܂ōs�����甽�΂���*/

		/*��ʊO�ɗ�������*/
		if (TempY > 900)
		{
			if (BonusStage)
			{
				Failed = true;
			}
			else
			{
				if (Life > 0)
				{
					if (Hit)
					{
						RestTime = 60;
						TempX = 50;
						Life--;
						Hit = false;
					}
					TempY = RefY;
				}
				else if (Life <= 0)
				{
					if (OverY > 100)
					{
						OverY -= 5;
					}
				}
			}
		}
		/*��ʊO�ɗ�������*/

		/*���G����*/
		if (RestTime > 0)
		{
			RestTime--;
		}

		if (Hit == true)
		{
			velX = 0;
			Accel = 0;
			animCounter++;
			TempY += 4;
		}
		/*���G����*/

		/*�W�����v*/
		if (jumping == true)
		{
			if (TempY >= beforeJump - 220)
			{
				TempY -= 10;
			}
			else
			{
				jumping = false;
			}
		}
		/*�W�����v*/


		/*�u���b�N�Ƃ̓����蔻��*/
		for (int i = 0; i < 7; i += 3)
		{
			/*�G�ɓ������ĂȂ���*/
			if (!Hit)
			{
				//�����̓����蔻��
				if (scene->Getmap()->MapChip[150 - (33 - ((TempY + 20 + PHeight) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] == 4 + i ||
					scene->Getmap()->MapChip[150 - (33 - ((TempY + 20 + PHeight) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] == 3 + i)	
				{
					if (reverse == false)
					{
						reverse = true;
						TempY -= velY;
					}

					/*�X�N���[��*/
					if (ScrollCount < 6 || ScrollCount > 7)
					{
						if (TempY + 20 + PHeight < 410)
						{
							if (!Scrolling)
							{
								ScrollCount++;
								Scrolling = true;
							}
						}

						if (TempY + 20 + PHeight < 603)
						{
							if (Scrolling)
							{
								/*�}�b�v*/
								for (int y = MapY - 1; y > 6; y--)
								{
									for (int x = 0; x < MapX; x++)
									{
										scene->Getmap()->MapChip[y][x] = scene->Getmap()->MapChip[y - 1][x];
									}
								}
								/*�}�b�v*/

								/*�A�U���V*/
								for (int i = 0; i < 6; i++)
								{
									scene->Getseal()->y[i] += BHeight;
									scene->Getseal()->RefY[i] += BHeight;
									scene->Getseal()->iceY[i] += BHeight;
									/*��*/
									scene->Getwall()->LeftY[i] += BHeight;
									scene->Getwall()->RightY[i] += BHeight;
									/*��*/
								}
								/*�A�U���V*/

								for (int i = 0; i < 2; i++)
								{
									scene->Getcloud()->y[i] += BHeight;
								}

								for (int i = 0; i < 4; i++)
								{
									scene->Geteggplant()->y[i] += BHeight;
								}

								for (int i = 0; i < 8; i++)
								{
									scene->Getfloor()->LeftY[i] += BHeight;
									scene->Getfloor()->RightY[i] += BHeight;
								}

								TempY += BHeight;	//���@
								scene->Getknitpicker()->RefY += BHeight;	//��
								scene->Getknitpicker()->y += BHeight;		//��
								scene->Getwhitebear()->AppearCount = 2100;	//�V���N�}
								scene->Getwhitebear()->moveCount = 620;	//�V���N�}
								scene->Getwhitebear()->y += BHeight;
								scene->Getwall()->LeftY[6] += BHeight;
								scene->Getwall()->RightY[6] += BHeight;
								scene->Getcondor()->y += BHeight;
								scene->Gettimer()->y += BHeight;
								scene->Gettimer()->y2 += BHeight;
								RefY = 599;
							}
						}
						else
						{
							Scrolling = false;
						}
					}
					else if (ScrollCount == 6)
					{
						if (TempY + 20 + PHeight < 125)
						{
							ScrollCount++;
							BonusStage = true;
							Scrolling = true;
						}
					}
					else if (ScrollCount == 7)
					{
						if (TempY + 20 + PHeight < 819)
						{
							if (Scrolling)
							{
								/*�}�b�v*/
								for (int y = MapY - 1; y > 6; y--)
								{
									for (int x = 0; x < MapX; x++)
									{
										scene->Getmap()->MapChip[y][x] = scene->Getmap()->MapChip[y - 1][x];
									}
								}
								/*�}�b�v*/

								/*�A�U���V*/
								for (int i = 0; i < 6; i++)
								{
									scene->Getseal()->alive[i] = false;
									scene->Getseal()->iceExist[i] = false;
									/*��*/
									scene->Getwall()->LeftY[i] += BHeight;
									scene->Getwall()->RightY[i] += BHeight;
									/*��*/
								}
								/*�A�U���V*/

								/*�_*/
								for (int i = 0; i < 2; i++)
								{
									scene->Getcloud()->y[i] += BHeight;
								}
								/*�_*/

								/*�i�X*/
								for (int i = 0; i < 4; i++)
								{
									scene->Geteggplant()->y[i] += BHeight;
								}
								/*�i�X*/

								for (int i = 0; i < 8; i++)
								{
									scene->Getfloor()->LeftY[i] += BHeight;
									scene->Getfloor()->RightY[i] += BHeight;
								}

								TempY += BHeight;	//���@
								scene->Getknitpicker()->alive = false;	//��
								scene->Getwhitebear()->alive = false;	//�V���N�}
								scene->Getwall()->LeftY[6] += BHeight;	//���̂��	
								scene->Getwall()->RightY[6] += BHeight;	//���̂��
								scene->Gettimer()->y += BHeight;	//�^�C�}�[
								scene->Gettimer()->y2 += BHeight;	//�^�C�}�[2
								scene->Getcondor()->y += BHeight;	//�R���h��
								RefY = 599;	//���X�|�[���ʒu
							}
						}
						else
						{
							ScrollCount++;
							Scrolling = false;
						}
					}
					/*�X�N���[��*/
					velY = 0;
					jumping = false;
					PushJump = false;
				}
				else
				{
					TempY += velY;
				}

				if (jumping)	//��
				{

					if (scene->Getmap()->MapChip[150 - (33 - ((TempY + 20) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] == 3 + i)	//��
					{
						jumping = false;
					}

					if (scene->Getmap()->MapChip[150 - (33 - ((TempY + 20) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] == 4 + i)	//��
					{
						jumping = false;
						scene->Getresult()->HaveBlock++;
						/*�u���b�N����*/
						scene->Getmap()->MapChip[150 - (33 - ((TempY + 20) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] = 0;
						/*�u���b�N����*/
					}

					if (scene->Getmap()->MapChip[150 - (33 - ((TempY + 20) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] == 5 + i)	//��
					{
						if (TempY < 10 + scene->Getmap()->MY[150 - (33 - ((TempY + 20) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth])
						{
							jumping = false;
							scene->Getresult()->HaveBlock++;
							scene->Getmap()->MapChip[150 - (33 - ((TempY + 20) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] = 0;
						}
					}
				}
			}
			/*�G�ɓ������ĂȂ���*/
		}
		/*�u���b�N�Ƃ̓����蔻��*/

		/*�_�Ƃ̓����蔻��*/
		int cx[2] = { scene->Getcloud()->x[0],scene->Getcloud()->x[1] };
		int cy[2] = { scene->Getcloud()->y[0],scene->Getcloud()->y[1] };
		if (scene->Getcloud()->Collision(TempX + 20, TempY + 20, PWidth, PHeight, cx[0], cy[0]))
		{
			if (TempY + 20 - 1 < cy[0] + CloudHeight)
			{
				jumping = false;
			}

			if (TempY + 20 + PHeight < cy[0] + CloudHeight)
			{
				TempX++;
				PushJump = false;
				/*if (!velY == 0)
				{
					TempY -= velY;
				}*/
				if (reverse == false)
				{
					reverse = true;
					TempY -= velY;
				}
				velY = 0;
			}
		}

		if (scene->Getcloud()->Collision(TempX + 20, TempY + 20, PWidth, PHeight, cx[1], cy[1]))
		{
			if (TempY + 20 - 1 < cy[1] + CloudHeight)
			{
				jumping = false;
			}

			if (TempY + 20 + PHeight < cy[1] + CloudHeight)
			{
				TempX--;
				PushJump = false;
				/*if (!velY == 0)
				{
					TempY -= velY;
				}*/
				if (reverse == false)
				{
					reverse = true;
					TempY -= velY;
				}
				//velY = 0;
			}
		}
		/*�_�Ƃ̓����蔻��*/

		/*�R���h���̓����蔻��*/
		if (scene->Getcondor()->Collision(TempX + 20, TempY + 20, PWidth, PHeight))
		{
			WaitTimer(5000);
			Clear = true;
			scene->Getresult()->score += 3000;
		}
		/*�R���h���̓����蔻��*/

		/*�i�X�Ƃ̓����蔻��*/
		int ex[4], ey[4];
		if (BonusStage)
		{

			for (int i = 0; i < 4; i++)
			{
				ex[i] = scene->Geteggplant()->x[i];
				ey[i] = scene->Geteggplant()->y[i];
				if (scene->Geteggplant()->collision(TempX + 20, TempY + 20, PWidth, PHeight, ex[i], ey[i]))
				{
					if (scene->Geteggplant()->exist[i])
					{
						scene->Geteggplant()->exist[i] = false;
						scene->Getresult()->HaveEgg++;
					}
				}
			}
		}
		/*�i�X�Ƃ̓����蔻��*/

		if (!BonusStage)
		{
			/*�A�U���V?�Ƃ̓����蔻��*/
			for (int i = 0; i < 6; i++)
			{
				int sx[6];
				int sy[6];
				bool sHit[6];

				sx[i] = scene->Getseal()->x[i];
				sy[i] = scene->Getseal()->y[i];
				sHit[i] = scene->Getseal()->Hit[i];
				/*�n���}�[�ƃA�U���V*/
				if (Attacking)
				{
					if (scene->Getseal()->Collision(HummerX, TempY, HummerWidth, 108, sx[i], sy[i], sHit[i]))
					{
						if (x > sx[i] && !scene->Getseal()->HummerLeft[i] && !scene->Getseal()->HummerRight[i])
						{
							scene->Getseal()->HummerRight[i] = true;
						}
						if (x < sx[i] && !scene->Getseal()->HummerLeft[i] && !scene->Getseal()->HummerRight[i])
						{
							scene->Getseal()->HummerLeft[i] = true;
						}

						scene->Getseal()->Hit[i] = true;
						sHit[i] = true;

					}
				}
				/*�n���}�[�ƃA�U���V*/

				/*�|�|�ƃA�U���V*/
				if (RestTime <= 0)
				{
					if (x > 128 && x + PWidth < 896)
					{
						if (scene->Getseal()->Collision(TempX + 20, TempY + 20, PWidth, PHeight, sx[i], sy[i], sHit[i]))
						{
							if (!Hit)
							{
								WaitTimer(500);
								Hit = true;
							}
						}
					}
				}
				/*�|�|�ƃA�U���V*/
			}
			/*�A�U���V?�Ƃ̓����蔻��*/

			/*�n���}�[�ƒ�*/
			if (Attacking || jumping)
			{
				if (scene->Getknitpicker()->Collision(HummerX, HummerY, HummerWidth, HummerHeight))
				{
					scene->Getknitpicker()->Hit = true;
					scene->Getresult()->HaveBird++;
				}
			}
			/*�n���}�[�ƒ�*/

			/*�|�|�ƒ�*/
			if (scene->Getknitpicker()->Collision(TempX + 20, TempY + 20, PWidth, PHeight))
			{
				if (!Hit)
				{
					WaitTimer(500);
				}
				Hit = true;
			}
			/*�|�|�ƒ�*/

			/*�X�Ƃ̓����蔻��*/
			int ix[8], iy[8];
			bool iexist[8];
			for (int i = 0; i < 8; i++)
			{
				ix[i] = scene->Getseal()->iceX[i];
				iy[i] = scene->Getseal()->iceY[i];
				iexist[i] = scene->Getseal()->iceExist[i];

				if (scene->Getseal()->IceCollision(TempX + 20, TempY + 20, PWidth, PHeight, ix[i], iy[i], iexist[i]))
				{
					WaitTimer(1000);
					Hit = true;
				}

				if (scene->Getseal()->IceCollision(HummerX, HummerY, HummerWidth, HummerHeight, ix[i], iy[i], iexist[i]))
				{
					scene->Getseal()->iceExist[i] = false;
					scene->Getresult()->HaveIce++;
				}
			}
			/*�X�Ƃ̓����蔻��*/
		}
		else
		{
			/*�ǂƂ̓����蔻��*/
			int lwx[7], rwx[7], lwy[7], rwy[7];
			for (int i = 0; i < 7; i++)
			{
				lwx[i] = scene->Getwall()->LeftX[i];
				rwx[i] = scene->Getwall()->RightX[i];
				lwy[i] = scene->Getwall()->LeftY[i];
				rwy[i] = scene->Getwall()->RightY[i];

				if (scene->Getwall()->LeftWallCollision(TempX + 20, TempY + 20, PWidth, PHeight, lwx[i], lwy[i]))
				{
					TempX += velX;
					Rightward = true;
				}

				if (scene->Getwall()->RightWallCollision(TempX + 20, TempY + 20, PWidth, PHeight, rwx[i], rwy[i]))
				{
					TempX -= velX;
					Rightward = false;
				}
			}
			/*�ǂƂ̓����蔻��*/
		}


		x = TempX;
		y = TempY;

		if (!jumping)	//�W�����v���ĂȂ�������
		{
			HummerX = TempX + (40 * Rightward) + (width * Rightward);
			HummerY = TempY;
			HummerWidth = 20;
			HummerHeight = 108;
		}
		else //�W�����v���Ă���
		{
			HummerX = TempX + 20;
			HummerY = TempY - 40;
			HummerWidth = 48;
			HummerHeight = 40;
		}
	}
}

void Player::Draw()
{
	int tx = 0;

	if (!Clear && !Failed)
	{
		if (Hit)
		{
			pattern = 5 * 120;
			tx = (animCounter / 2) % 4 * 92;
		}
		else if (PushJump)
		{
			pattern = 2 * 120;
			if (animCounter < 2)
			{
				animCounter++;
			}
			tx = animCounter % 2 * 92;
		}
		else if (Attacking)
		{
			pattern = 1 * 120;
			tx = ((animCounter / 6) % 3) * 92;
		}
		else
		{
			pattern = 0 * 120;
			tx = animCounter % 4 * 92;
		}

		if (RestTime % 2 == 0)
		{
			DrawRectGraph(x, y, tx, pattern, 92, 120, image, true, Rightward);
		}

		DrawGraph(OverX, OverY, GameOverimage, true);

		if (!BonusStage)
		{
			if (Life >= 1)
			{
				DrawGraph(LifeX, LifeY, Lifeimage, true);
			}

			if (Life >= 2)
			{
				DrawGraph(LifeX + 40, LifeY, Lifeimage, true);
			}

			if (Life >= 3)
			{
				DrawGraph(LifeX + 80, LifeY, Lifeimage, true);
			}
		}
	}
}
