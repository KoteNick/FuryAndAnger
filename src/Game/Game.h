#pragma once
#include "Core/Entity.h"
#include <vector>

class Game {
private:
	static Game* instance;
public:
	Game() {
		instance = this;
	}
	~Game() {
		instance = nullptr;
	}
	static Game& Get() { return *instance; }
public:
	Entity triangle, triangle2;

	void Init();
	void OnUpdate(float deltaTime);
	void Close();
};