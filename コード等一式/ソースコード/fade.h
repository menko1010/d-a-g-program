#pragma once
#include"main.h"
#include"manager.h"
#include"scene.h"
#include"scene.h"

class Fade : public Scene {
private:

	static FadeTexture* m_fadein;
public:

	void Init() override;//���z�֐�

	void Update() override;//���z�֐�
	void Draw() override;//���z�֐�

};