#pragma once
#include <vector>
#include "Scene.h"

enum class Scenes
{
	// None�����邩����Ȃ����l���ǂ���
	Title,
	Mune,
	GameOver,
	GameClear,
	Stage1,
	// etc...
};

class SceneManager
{
private:
	// std::vector<Scene> //�V�[��������ϐ�(InitScene�ő������)
public:
	SceneManager();
	virtual ~SceneManager();

public:
	void SetScene(); // ����̕ϐ��ɒl������Ƃ���Scene�ɑJ�ڂ���

private:
	void InitScene(); // �V�[���̏�����(��L��enum class�̏��Ԃɓ����)


};