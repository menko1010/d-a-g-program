#pragma once
#include"main.h"
#include"manager.h"
#include"scene.h"
#include"scene.h"

class Fade : public Scene {
private:

	static FadeTexture* m_fadein;
public:

	void Init() override;//仮想関数

	void Update() override;//仮想関数
	void Draw() override;//仮想関数

};