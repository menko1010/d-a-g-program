#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "gamescene.h"
#include "OBB.h"
#include "result.h"
#include "clear.h"
#include "particleemitter.h"
#include "meshField.h"
#include "hp.h"
#include "stamina.h"
#include "titleparticle.h"
#include "ryuu.h"
#include "playershadow.h"
#include "audio.h"
#include "wave.h"

bool Game::m_LoadFinish = false;

void Game::Load()
{
	Player::Load();
	PlayerShadow::Load();
	//ロード終了
	m_LoadFinish = true;
}

void Game::Init()  {

	AddGameObject<Camera>(0);//関数をテンプレートでまとめられる
	
	AddGameObject<Sky>(1)->SetScale(XMFLOAT3(150.0f, 150.0f, 150.0f));//関数をテンプレートでまとめられる

	AddGameObject<MeshField>(1);//関数をテンプレートでまとめられる
	{
		Player* player = AddGameObject<Player>(1);
		player->SetScale(XMFLOAT3(0.04f, 0.04f, 0.04f));
		player->SetRotation(XMFLOAT3(0.0f, 0.0f, 0.0f));
		player->SetPosition(XMFLOAT3(0.0f, 2.0f, 0.0f));
	}

	{
		Ryuu* ryuu = AddGameObject<Ryuu>(1);
		ryuu->SetPosition(XMFLOAT3(0.0f, 2.0f, 20.0f));
		ryuu->SetScale(XMFLOAT3(0.4f, 0.4f, 0.4f));
		ryuu->SetRotation(XMFLOAT3(0.0f, 3.14f, 0.0f));
	}
	AddGameObject<Wave>(1)->SetPosition(XMFLOAT3(0.0f, 0.2f, 0.0f));
	{
		PlayerShadow* shadow = AddGameObject<PlayerShadow>(1);
		shadow->SetPosition(XMFLOAT3(0.0f, 0.0f, 5.0f));
		shadow->SetScale(XMFLOAT3(8.0f, 5.0f, 8.0f));
		shadow->SetRotation(XMFLOAT3(0.0f, -10.0f, 0.0f));

		AddGameObject<Polygon2D>(1);
	}
	for (int p = 0; p < 20; p++)
	{
		//メッシュフィールド高さ取得
		MeshField* field =
			Manager::GetScene()->GetGameObject<MeshField>();

		Tree tree;
		XMFLOAT3 pos;
		pos.x = (float)(rand() % 10 - 5) * 15;
		pos.z = (float)(rand() % 10 - 5) * 15;
		pos.y = field->GetHeight(pos) - 0.5f;//戻り値、セットに入れている変数を入れて戻り値で場所指定をする

		AddGameObject<Tree>(2)->SetPosition(XMFLOAT3(pos.x, pos.y, pos.z));//関数をテンプレートでまとめられる
	}
	AddGameObject<Camera>(1);//関数をテンプレートでまとめられる

	AddGameObject<Polygon2D>(2);//関数をテンプレートでまとめられる
	AddGameObject<Score>(2);//関数をテンプレートでまとめられる
	AddGameObject<Hp>(2);//関数をテンプレートでまとめられる
	AddGameObject<Stamina>(2);//関数をテンプレートでまとめられる
	AddGameObject<FadeTexture>(2);//関数をテンプレートでまとめられる

	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(XMFLOAT3(0.0f, 2.0f, -55.0f));
		box->SetScale(XMFLOAT3(0.2f, 0.2f, 0.05f));
		box->SetRotation(XMFLOAT3(0.0f, 0.0f, 0.0f));
	}
	m_SE = new Audio(this);
	m_SE->Load("asset\\BGM\\戦闘メイン.wav");
	m_SE->Play(true);//trueを入れてループ再生
}

void Game::Uninit()
{
	Scene::Uninit();

	PlayerShadow::Unload();
	m_LoadFinish = false;
	m_SE->Uninit();
}


void Game::Update()
{
	Scene::Update();//overrideで継承されているgamesceneのupdateが優先されるためこっちでSceneのupdateを呼ぶことで、ゲームが動く

	std::vector<Ryuu*>enemyList = GetGameObjects<Ryuu>();
	std::vector<Player*>playerList = GetGameObjects<Player>();

	if (enemyList.size() == 0) 
	{
		//敵が全滅したら
		Manager::SetScene<Clear>();
	}
	if (playerList.size() == 0)
	{
		Manager::SetScene<Result>();
	}
	
}


