#pragma once

#include"main.h"
#include"manager.h"
#include"scene.h"
#include"scene.h"

class Load : public Scene {
public:

	void Init() override;//���z�֐�
	void Uninit() override;//���z�֐�
	void Update() override;
};