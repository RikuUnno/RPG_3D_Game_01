#pragma once
#include <vector>
#include "Scene.h"

enum class Scenes
{
	// Noneを入れるか入れないか考えどころ
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
	// std::vector<Scene> //シーンを入れる変数(InitSceneで代入する)
public:
	SceneManager();
	virtual ~SceneManager();

public:
	void SetScene(); // これの変数に値を入れるとそのSceneに遷移する

private:
	void InitScene(); // シーンの初期化(上記のenum classの順番に入れる)


};