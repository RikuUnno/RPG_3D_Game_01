#include "DxLib.h"
#include "GameInfo.h"
#include "TIme.h"

#include "Player.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    ChangeWindowMode(TRUE); // ウインドウモードで起動
    
    SetGraphMode((int)WIN_SIZE_X, (int)WIN_SIZE_Y, 32); // 画面サイズのセット
    
    SetWindowText("3D_RPG_GAME"); // ウィンドウの名前（現在は仮）
    
    if (DxLib_Init() == -1) // DXライブラリの初期化
    {
        return -1; // エラーが起きたら直ちに終了
    }
    
    Time time;

    Player player;

    // 描画先画面を裏画面にセット
    SetDrawScreen(DX_SCREEN_BACK);
    
    // ESCを押したら画面が落ちる
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        clsDx();
        ClearDrawScreen();
    
        time.Update();
    
        DrawFormatString(0, 0, 0xFFFFFF, "%lf", time.DeltaTime());
    
        ScreenFlip();
    }
    
    DxLib_End();        // ＤＸライブラリ使用の終了処理
    
    return 0;        // ソフトの終了
}


