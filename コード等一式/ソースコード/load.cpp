#include "main.h"
#include "manager.h"
#include "gameobject.h"
#include "input.h"
#include "renderer.h"
#include "load.h"
#include "gamescene.h"
#include "loadrogo.h"
#include "load.h"
#include "audio.h"
#include "fade.h"
#include <thread>

void Load::Init() 
{
	AddGameObject<Loadrogo>(2)->SetPosition(XMFLOAT3(560.0f, 450.0f, 0.0f));//関数をテンプレートでまとめられる
	AddGameObject<FadeTexture>(2);

	std::thread th(&Game::Load);//スレッド
	th.detach();
}

void Load::Uninit()
{
}

void Load::Update()
{
	Scene::Update();

	if (Game::GetLoadFinish()) 
	{
		Manager::SetScene<Game>();
	}
}



