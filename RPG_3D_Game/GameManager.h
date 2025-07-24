#pragma once

class GameManager
{
private:
	GameManager() = default;
	~GameManager() = default;

	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

public:
	static GameManager& GetInstance() {
		static GameManager Instance;
		return Instance;
	}

	void Init();
	
	void Update();

	void Delete();
};