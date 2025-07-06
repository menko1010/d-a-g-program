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
	//���[�h�I��
	m_LoadFinish = true;
}

void Game::Init()  {

	AddGameObject<Camera>(0);//�֐����e���v���[�g�ł܂Ƃ߂���
	
	AddGameObject<Sky>(1)->SetScale(XMFLOAT3(150.0f, 150.0f, 150.0f));//�֐����e���v���[�g�ł܂Ƃ߂���

	AddGameObject<MeshField>(1);//�֐����e���v���[�g�ł܂Ƃ߂���
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
		//���b�V���t�B�[���h�����擾
		MeshField* field =
			Manager::GetScene()->GetGameObject<MeshField>();

		Tree tree;
		XMFLOAT3 pos;
		pos.x = (float)(rand() % 10 - 5) * 15;
		pos.z = (float)(rand() % 10 - 5) * 15;
		pos.y = field->GetHeight(pos) - 0.5f;//�߂�l�A�Z�b�g�ɓ���Ă���ϐ������Ė߂�l�ŏꏊ�w�������

		AddGameObject<Tree>(2)->SetPosition(XMFLOAT3(pos.x, pos.y, pos.z));//�֐����e���v���[�g�ł܂Ƃ߂���
	}
	AddGameObject<Camera>(1);//�֐����e���v���[�g�ł܂Ƃ߂���

	AddGameObject<Polygon2D>(2);//�֐����e���v���[�g�ł܂Ƃ߂���
	AddGameObject<Score>(2);//�֐����e���v���[�g�ł܂Ƃ߂���
	AddGameObject<Hp>(2);//�֐����e���v���[�g�ł܂Ƃ߂���
	AddGameObject<Stamina>(2);//�֐����e���v���[�g�ł܂Ƃ߂���
	AddGameObject<FadeTexture>(2);//�֐����e���v���[�g�ł܂Ƃ߂���

	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(XMFLOAT3(0.0f, 2.0f, -55.0f));
		box->SetScale(XMFLOAT3(0.2f, 0.2f, 0.05f));
		box->SetRotation(XMFLOAT3(0.0f, 0.0f, 0.0f));
	}
	m_SE = new Audio(this);
	m_SE->Load("asset\\BGM\\�퓬���C��.wav");
	m_SE->Play(true);//true�����ă��[�v�Đ�
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
	Scene::Update();//override�Ōp������Ă���gamescene��update���D�悳��邽�߂�������Scene��update���ĂԂ��ƂŁA�Q�[��������

	std::vector<Ryuu*>enemyList = GetGameObjects<Ryuu>();
	std::vector<Player*>playerList = GetGameObjects<Player>();

	if (enemyList.size() == 0) 
	{
		//�G���S�ł�����
		Manager::SetScene<Clear>();
	}
	if (playerList.size() == 0)
	{
		Manager::SetScene<Result>();
	}
	
}


