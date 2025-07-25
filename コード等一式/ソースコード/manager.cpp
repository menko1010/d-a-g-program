#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Input.h"
#include "Scene.h"
#include "gamescene.h"
#include "title.h"
#include "titletexture.h"
#include "modelRenderer.h"
#include "audio.h"

//staticメンバ変数は宣言が必要
Scene* Manager::m_Scene{};
Scene* Manager::m_Nextscene{};

void Manager::Init()
{
	Renderer::Init();
	Input::Init();
	Audio::InitMaster();

	m_Scene = new Title;
	m_Scene->Init();
}

void Manager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	ModelRenderer::UnloadAll();

	Audio::UninitMaster();
	Input::Uninit();
	Renderer::Uninit();
}

void Manager::Update()
{
	Input::Update();

	m_Scene->Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	m_Scene->Draw();

	Renderer::End();

	if (m_Nextscene != nullptr)//nullじゃなければ画面予約が入っているので予約を実行する
	{
		m_Scene->Uninit();
		delete m_Scene;//画面遷移する前に前の画面を消す

		ModelRenderer::UnloadAll();

		m_Scene = m_Nextscene;
		m_Scene->Init();

		m_Nextscene = nullptr;
	}
}
