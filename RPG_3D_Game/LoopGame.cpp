#include "DxLib.h"
#include "GameInfo.h"
#include "TIme.h"

#include "Player.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    ChangeWindowMode(TRUE); // �E�C���h�E���[�h�ŋN��
    
    SetGraphMode((int)WIN_SIZE_X, (int)WIN_SIZE_Y, 32); // ��ʃT�C�Y�̃Z�b�g
    
    SetWindowText("3D_RPG_GAME"); // �E�B���h�E�̖��O�i���݂͉��j
    
    if (DxLib_Init() == -1) // DX���C�u�����̏�����
    {
        return -1; // �G���[���N�����璼���ɏI��
    }
    
    Time time;

    Player player;

    // �`����ʂ𗠉�ʂɃZ�b�g
    SetDrawScreen(DX_SCREEN_BACK);
    
    // ESC�����������ʂ�������
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        clsDx();
        ClearDrawScreen();
    
        time.Update();
    
        DrawFormatString(0, 0, 0xFFFFFF, "%lf", time.DeltaTime());
    
        ScreenFlip();
    }
    
    DxLib_End();        // �c�w���C�u�����g�p�̏I������
    
    return 0;        // �\�t�g�̏I��
}


