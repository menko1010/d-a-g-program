#pragma once

#include"main.h"
#include"manager.h"
#include"scene.h"
#include"scene.h"

class Title : public Scene 
{
private:
	class Audio* m_BGM{};

public:
	void Init() override;//���z�֐�
	void Uninit() override;//���z�֐�
	void Update() override;
};