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
	void Init() override;//仮想関数
	void Uninit() override;//仮想関数
	void Update() override;
};