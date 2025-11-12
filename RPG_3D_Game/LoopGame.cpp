// ゲームののmain関数

#include "DxLib.h"
#include "GameInfo.h"
#include "TIme.h"
#include "Player.h"

#include "BoxCollider.h"
#include "ColliderManager.h"
#include "Transform.h"

//class Kumo
//{
//public:
//    int i; 
//    ColliderManager cm;
//    BoxCollider bColl;
//
//    Transform transform;
//
//    // Kumo ku;
//
//
//public:
//
//    Kumo(VECTOR pos, VECTOR rot, VECTOR scle)
//        : bColl(/*ここにはboxColliderの分を書き込む*/),
//        transform(VGet(0,0,0), VGet(0,0,0), VGet(1,1,1))
//    {
//        i = MV1LoadModel("C:/model/x/model.x");
//    }
//
//    void Update() 
//    {
//        DrawFormatString(0, 70, GetColor(255, 255, 255), "%d", MV1GetMaterialNum(i));
//        DrawFormatString(0, 85, GetColor(255, 255, 255), "%d", i);
//
//        MV1SetPosition(i, VGet(0, 0, 100));
//
//        MV1SetScale(i, transform.GetScale());
//
//        MV1SetRotationXYZ(i, transform.GetRot());
//
//        MV1SetPosition(i, transform.GetTrans());
//
//        MV1DrawModel(i);
//
//        bColl.DrawAABB();
//
//
//    }
//};

// 初期化時などで一度呼ぶ(ライティング関係)
void SetupDefaultLight()
{
    // 方向ライトの有効化
    VECTOR lightDir = VNorm(VGet(.0f, -20.0f, 15.0f));
    SetLightDirection(lightDir);

    // 環境光
    SetLightAmbColor(GetColorF(0.7f, 0.7f, 0.7f, 1.0f));

    // ディフューズカラー
    SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));

    SetUseLighting(TRUE);			// ライティングの有効
    SetUseZBuffer3D(TRUE);			// Zバッファ有効化
    SetWriteZBuffer3D(TRUE);		// Zバッファ書き込み
    SetLightEnable(TRUE);			 // ライティング全体を有効化
}

// Y軸上向きの固定カメラを設定する
void SetFixedCamera()
{
    VECTOR m_camPos = VGet(0.0f, 100.0f, -300.0f); // カメラ位置
    VECTOR m_target = VGet(0.0f, 0.0f, 0.0f);      // 注視点（原点を見る）

    SetCameraNearFar(0.1f, 1000.0f); // 視錐台の調整
    SetCameraPositionAndTarget_UpVecY(m_camPos, m_target);
}

// XYZのライン描画
void DrawVectorLine()
{
    DrawLine3D(VGet(0, 5, 0), VGet(100, 5, 0), GetColor(255, 0, 0));   // X軸
    DrawLine3D(VGet(0, 5, 0), VGet(0, 105, 0), GetColor(0, 255, 0));   // Y軸
    DrawLine3D(VGet(0, 5, 0), VGet(0, 5, 100), GetColor(0, 0, 255));   // Z軸
}

// グラウンドの表示
void DrawGround()
{
    const int num = 10;         // マスの数（10×10）
    const double size = 500.0;  // 全体のサイズ
    const double cell = size / num; // 1マスronの大きさ（50.0）

    int color1 = GetColor(180, 180, 180); // 明るいグレー
    int color2 = GetColor(120, 120, 120); // 暗いグレー

    for (int z = 0; z < num; ++z)
    {
        for (int x = 0; x < num; ++x)
        {
            // 左下の座標を計算（中心を原点にする）
            double startX = -size / 2 + x * cell;
            double startZ = -size / 2 + z * cell;

            VECTOR p1 = VGet((float)startX, -1.3f, (float)startZ);       // 左奥
            VECTOR p2 = VGet((float)startX + (float)cell, -1.3f, (float)startZ);       // 右奥
            VECTOR p3 = VGet((float)startX + (float)cell, -1.3f, (float)startZ + (float)cell);  // 右前
            VECTOR p4 = VGet((float)startX, -1.3f, (float)startZ + (float)cell);  // 左前

            int color = ((x + z) % 2 == 0) ? color1 : color2;

            DrawTriangle3D(p1, p2, p3, color, TRUE);
            DrawTriangle3D(p1, p3, p4, color, TRUE);
        }
    }

}

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

    // ~~~~~ てすと ~~~~~
    SetupDefaultLight(); // テスト

    // Kumo kumo(VGet(0,0,0), VGet(0,0,0), VGet(1, 1,1));

    // ~~~~~~~~~~~~~~~~~~~~~~~~

    // 描画先画面を裏画面にセット
    SetDrawScreen(DX_SCREEN_BACK);
    
    // ESCを押したら画面が落ちる
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        clsDx();
        ClearDrawScreen();
    
        time.Update();

        // ~~~~~~~ テスト　~~~~~~~~~

        // kumo.Update();

        DrawGround(); // テスト

        SetFixedCamera(); // テスト

        DrawVectorLine(); // テスト

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~
    
        DrawFormatString(0, 0, 0xFFFFFF, "%lf", time.DeltaTime());
    
        ScreenFlip();
    }
    
    DxLib_End();        // ＤＸライブラリ使用の終了処理
    
    return 0;        // ソフトの終了
}


