#pragma once
#include "scene.h"
#include "fadetexture.h"
//ƒQ[ƒ€‚ÌŠÇ—
class Manager
{
private: 
	static Scene* m_Scene;
	static Scene* m_Nextscene;//‰æ–Ê‘JˆÚ—\–ñ
	static FadeTexture* m_fade;
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static Scene* GetScene() { return m_Scene; }

	template <typename T>//ƒeƒ“ƒvƒŒ[ƒgŠÖ”
	static void SetScene() 
	{ 
		m_Nextscene = new T();
	}
};