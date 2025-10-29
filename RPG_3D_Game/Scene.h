#pragma once

class Scene
{
private:

public:
	Scene() {}
	virtual ~Scene(){}

public:
	// シーン開始時に初期化を行う
	virtual void Init() {}
	// シーン開始時に呼ばれる
	virtual void Start() {}
	// シーン中に呼ばれる
	virtual void Update() {}
	// シーンの最後に呼ばれる
	virtual void End() {}



};