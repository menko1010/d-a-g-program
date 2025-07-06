#pragma once
#include "scene.h"
#include "fadetexture.h"
//�Q�[���̊Ǘ�
class Manager
{
private: 
	static Scene* m_Scene;
	static Scene* m_Nextscene;//��ʑJ�ڗ\��
	static FadeTexture* m_fade;
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static Scene* GetScene() { return m_Scene; }

	template <typename T>//�e���v���[�g�֐�
	static void SetScene() 
	{ 
		m_Nextscene = new T();
	}
};