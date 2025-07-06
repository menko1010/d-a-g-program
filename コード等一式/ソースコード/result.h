#pragma once

#include"main.h"
#include"manager.h"
#include"scene.h"

class Result : public Scene 
{
public:
	void Init() override;
	void Update() override;
};