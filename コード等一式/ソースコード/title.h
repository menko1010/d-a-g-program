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
	void Init() override;//âºëzä÷êî
	void Uninit() override;//âºëzä÷êî
	void Update() override;
};