// �Q�[���̂�main�֐�

#include "DxLib.h"
#include "GameInfo.h"
#include "TIme.h"
#include "Player.h"

#include "BoxCollider.h"
#include "ColliderManager.h"
#include "Transform.h"

class Kumo
{
public:
    int i; 
    ColliderManager cm;
    BoxCollider bColl;

    Transform transform;

    // Kumo ku;


public:

    Kumo(VECTOR pos, VECTOR rot, VECTOR scle)
        : bColl(VGet(-100, 0, 0), VGet(100, 100, 100), &cm, true),
        transform(VGet(0,0,0), VGet(0,0,0), VGet(1,1,1))
    {
        i = MV1LoadModel("C:/model/x/model.x");
    }

    void Update() 
    {
        DrawFormatString(0, 70, GetColor(255, 255, 255), "%d", MV1GetMaterialNum(i));
        DrawFormatString(0, 85, GetColor(255, 255, 255), "%d", i);

        MV1SetPosition(i, VGet(0, 0, 100));

        MV1SetScale(i, transform.GetScale());

        MV1SetRotationXYZ(i, transform.GetRot());

        MV1SetPosition(i, transform.GetTrans());

        MV1DrawModel(i);

        bColl.DrawAABB();


    }
};

// ���������Ȃǂň�x�Ă�(���C�e�B���O�֌W)
void SetupDefaultLight()
{
    // �������C�g�̗L����
    VECTOR lightDir = VNorm(VGet(.0f, -20.0f, 15.0f));
    SetLightDirection(lightDir);

    // ����
    SetLightAmbColor(GetColorF(0.7f, 0.7f, 0.7f, 1.0f));

    // �f�B�t���[�Y�J���[
    SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));

    SetUseLighting(TRUE);			// ���C�e�B���O�̗L��
    SetUseZBuffer3D(TRUE);			// Z�o�b�t�@�L����
    SetWriteZBuffer3D(TRUE);		// Z�o�b�t�@��������
    SetLightEnable(TRUE);			 // ���C�e�B���O�S�̂�L����
}

// Y��������̌Œ�J������ݒ肷��
void SetFixedCamera()
{
    VECTOR m_camPos = VGet(0.0f, 100.0f, -300.0f); // �J�����ʒu
    VECTOR m_target = VGet(0.0f, 0.0f, 0.0f);      // �����_�i���_������j

    SetCameraNearFar(0.1f, 1000.0f); // ������̒���
    SetCameraPositionAndTarget_UpVecY(m_camPos, m_target);
}

// XYZ�̃��C���`��
void DrawVectorLine()
{
    DrawLine3D(VGet(0, 5, 0), VGet(100, 5, 0), GetColor(255, 0, 0));   // X��
    DrawLine3D(VGet(0, 5, 0), VGet(0, 105, 0), GetColor(0, 255, 0));   // Y��
    DrawLine3D(VGet(0, 5, 0), VGet(0, 5, 100), GetColor(0, 0, 255));   // Z��
}

// �O���E���h�̕\��
void DrawGround()
{
    const int num = 10;         // �}�X�̐��i10�~10�j
    const double size = 500.0;  // �S�̂̃T�C�Y
    const double cell = size / num; // 1�}�Xron�̑傫���i50.0�j

    int color1 = GetColor(180, 180, 180); // ���邢�O���[
    int color2 = GetColor(120, 120, 120); // �Â��O���[

    for (int z = 0; z < num; ++z)
    {
        for (int x = 0; x < num; ++x)
        {
            // �����̍��W���v�Z�i���S�����_�ɂ���j
            double startX = -size / 2 + x * cell;
            double startZ = -size / 2 + z * cell;

            VECTOR p1 = VGet((float)startX, -1.3f, (float)startZ);       // ����
            VECTOR p2 = VGet((float)startX + (float)cell, -1.3f, (float)startZ);       // �E��
            VECTOR p3 = VGet((float)startX + (float)cell, -1.3f, (float)startZ + (float)cell);  // �E�O
            VECTOR p4 = VGet((float)startX, -1.3f, (float)startZ + (float)cell);  // ���O

            int color = ((x + z) % 2 == 0) ? color1 : color2;

            DrawTriangle3D(p1, p2, p3, color, TRUE);
            DrawTriangle3D(p1, p3, p4, color, TRUE);
        }
    }

}

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

    // ~~~~~ �Ă��� ~~~~~
    SetupDefaultLight(); // �e�X�g

    Kumo kumo(VGet(0,0,0), VGet(0,0,0), VGet(1, 1,1));

    // ~~~~~~~~~~~~~~~~~~~~~~~~

    // �`����ʂ𗠉�ʂɃZ�b�g
    SetDrawScreen(DX_SCREEN_BACK);
    
    // ESC�����������ʂ�������
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        clsDx();
        ClearDrawScreen();
    
        time.Update();

        // ~~~~~~~ �e�X�g�@~~~~~~~~~

        kumo.Update();

        DrawGround(); // �e�X�g

        SetFixedCamera(); // �e�X�g

        DrawVectorLine(); // �e�X�g

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~
    
        DrawFormatString(0, 0, 0xFFFFFF, "%lf", time.DeltaTime());
    
        ScreenFlip();
    }
    
    DxLib_End();        // �c�w���C�u�����g�p�̏I������
    
    return 0;        // �\�t�g�̏I��
}


