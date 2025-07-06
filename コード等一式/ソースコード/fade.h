#pragma once
#include"main.h"
#include"manager.h"
#include"scene.h"
#include"scene.h"

class Fade : public Scene {
private:

	static FadeTexture* m_fadein;
public:

	void Init() override;//‰¼‘zŠÖ”

	void Update() override;//‰¼‘zŠÖ”
	void Draw() override;//‰¼‘zŠÖ”

};