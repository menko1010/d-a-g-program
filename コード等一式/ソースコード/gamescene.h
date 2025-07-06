#pragma once

#include"main.h"
#include"manager.h"
#include"scene.h"

class Game : public Scene {
private:
	
	static bool m_LoadFinish;

	class Audio* m_SE{};

public:

	static void Load();
	static bool GetLoadFinish() { return m_LoadFinish; }


	void Init() override;//���z�֐�
	void Uninit() override;
	void Update() override;//���z�֐�

};