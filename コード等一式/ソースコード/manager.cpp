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

//static�����o�ϐ��͐錾���K�v
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

	if (m_Nextscene != nullptr)//null����Ȃ���Ή�ʗ\�񂪓����Ă���̂ŗ\������s����
	{
		m_Scene->Uninit();
		delete m_Scene;//��ʑJ�ڂ���O�ɑO�̉�ʂ�����

		ModelRenderer::UnloadAll();

		m_Scene = m_Nextscene;
		m_Scene->Init();

		m_Nextscene = nullptr;
	}
}
