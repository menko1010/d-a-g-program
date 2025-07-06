#include "main.h"
#include "manager.h"
#include "gameobject.h"
#include "input.h"
#include "renderer.h"
#include "title.h"
#include "gamescene.h"
#include "titletexture.h"
#include "audio.h"
#include "fade.h"
#include "titlecamera.h"
#include "titleplayer.h"
#include "titleparticle.h"
#include "titlerogo.h"
#include "titleryuu.h"
#include "fire.h"
#include "load.h"

void Title::Init() {

	AddGameObject<TitleCamera>(0)->SetPosition(XMFLOAT3(0.0f, 0.0f, -5.0f));

	AddGameObject<TitleTexture>(1);//関数をテンプレートでまとめられる
	{
		Fire* fire = AddGameObject<Fire>(2);
		fire->SetPosition(XMFLOAT3(50.0f, 510.0f, 0.0f));
		fire->SetScale(XMFLOAT3(2.5f, 2.5f, 1.0f));
	}
	{
		Fire* fire = AddGameObject<Fire>(2);
		fire->SetPosition(XMFLOAT3(920.0f, 260.0f, 0.0f));
		fire->SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));
	}

	{//左下
		TitleParticle* particle = AddGameObject<TitleParticle>(1);
		particle->SetPosition(XMFLOAT3(-20.0f, -14.0f, 10.0f));
		particle->SetRotation(XMFLOAT3(0.0f, 0.0f, 0.0f));
		particle->SetScale(XMFLOAT3(0.5f, 0.5f, 1.0f));

	}
	{//右上

		TitleParticle* particle = AddGameObject<TitleParticle>(1);
		particle->SetPosition(XMFLOAT3(15.0f, 1.0f, 10.0f));
		particle->SetRotation(XMFLOAT3(0.0f, 0.0f, 3.0f));
		particle->SetScale(XMFLOAT3(0.3f, 0.3f, 1.0f));
	}
	{//右下

		TitleParticle* particle = AddGameObject<TitleParticle>(1);
		particle->SetPosition(XMFLOAT3(25.0f, -14.0f, 10.0f));
		particle->SetRotation(XMFLOAT3(0.0f, 0.0f, 3.0f));
		particle->SetScale(XMFLOAT3(0.5f, 0.5f, 1.0f));
	}

	{
		TitleRogo* rogo = AddGameObject<TitleRogo>(1);
		rogo->SetPosition(XMFLOAT3(1.0f, 3.0f, 10.0f));
	}

	{
		TitleRyuu* ryuu = AddGameObject<TitleRyuu>(1);
		ryuu->SetPosition(XMFLOAT3(-1.0f, -3.0f, 20.0f));
		ryuu->SetScale(XMFLOAT3(0.7f, 0.7f, 0.5f));
		ryuu->SetRotation(XMFLOAT3(0.0f, 3.0f, 0.0f));

	}
	{ 
		TitlePlayer* player = AddGameObject<TitlePlayer>(1);
		player->SetScale(XMFLOAT3(0.05f, 0.05f, 0.05f));
		player->SetRotation(XMFLOAT3(0.0f, 3.0f, 0.0f));
		player->SetPosition(XMFLOAT3(1.0f, -8.0f, 10.0f));
	}

	m_BGM = new Audio(this);//コンポーネントだから引数にthisを入れる
	m_BGM->Load("asset\\BGM\\タイトル.wav");
	m_BGM->Play(true);//trueを入れてループ再生

}

void Title::Uninit()
{
	m_BGM->Uninit();
	delete m_BGM;

}

void Title::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_SPACE)) {

		AddGameObject<FadeTexture>(2);
		Manager::SetScene<Load>();

	}
}



