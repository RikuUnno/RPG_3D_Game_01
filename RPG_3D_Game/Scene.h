#pragma once

class Scene
{
private:

public:
	Scene() {}
	virtual ~Scene(){}

public:
	// �V�[���J�n���ɏ��������s��
	virtual void Init() {}
	// �V�[���J�n���ɌĂ΂��
	virtual void Start() {}
	// �V�[�����ɌĂ΂��
	virtual void Update() {}
	// �V�[���̍Ō�ɌĂ΂��
	virtual void End() {}



};