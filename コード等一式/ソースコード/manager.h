#pragma once
#include "scene.h"
#include "fadetexture.h"
//ゲームの管理
class Manager
{
private: 
	static Scene* m_Scene;
	static Scene* m_Nextscene;//画面遷移予約
	static FadeTexture* m_fade;
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static Scene* GetScene() { return m_Scene; }

	template <typename T>//テンプレート関数
	static void SetScene() 
	{ 
		m_Nextscene = new T();
	}
};