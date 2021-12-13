#include "DxLib.h"
#include "app.h"
#include "Source.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(FALSE);	//ウィンドウモードにする
	SetGraphMode(1024, 900, 32);	//ウィンドウサイズを設定する

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);	//裏画面を描画対象へ

	//Init処理
	AppInit();
	//メイン処理
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){

		//Update処理
		AppUpdate();
		//Draw処理
		AppDraw();
		ScreenFlip();		//裏画面と表画面の入替
		ClearDrawScreen();	//裏画面の描画を全て消去
	}
	AppRelease();
	DxLib_End();			// ＤＸライブラリ使用の終了処理

  	return 0;				// ソフトの終了 
}