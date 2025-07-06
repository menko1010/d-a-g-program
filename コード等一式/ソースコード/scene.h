#pragma once

#include <list>
#include <vector>
#include "gameobject.h"
#include "polygon2D.h"
#include "renderer.h"
#include "field3D.h"
#include "camera.h"
#include "player.h"
#include "tree.h"
#include "sky.h"
#include "box.h"
#include "titletexture.h"
#include "time.h"


class Scene{
protected:

	std::list<GameObject*> m_GameObject[3];//�z��ɂ��邱�ƂŃ��X�g�\����z��̏��ԂōX�V���邱�Ƃ��ł���
	//0�ԃJ�����Ȃǂ̌����Ȃ��t�h
	//1��3D���f����I�u�W�F�N�g
	//2��2D�e�N�X�`���A�|���S��

public:

	virtual ~Scene() {}
	virtual void Init() {};

	template <typename T>//�e���v���[�g�֐�
	T* AddGameObject(int layer)
	{
		T* gameObject = new T();
		gameObject->Init();
		m_GameObject[layer].push_back(gameObject);

		return gameObject;
	}

	template <typename T>//�e���v���[�g�֐�
	T* GetGameObject()
	{
		for (int i = 0; i < 3; i++) {

			for (GameObject* Object : m_GameObject[i])
			{
				T* ret = dynamic_cast<T*>(Object);

				if (ret != nullptr) {
					return ret;
				}
			}
		}
		return nullptr;
	}

	template <typename T>//�e���v���[�g�֐�
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*>objectList;

		for (int i = 0; i < 3; i++) {

			for (GameObject* Object : m_GameObject[i])
			{
				T* ret = dynamic_cast<T*>(Object);

				if (ret != nullptr) {
					objectList.push_back(ret);
				}
			}
		}
		return objectList;
	}

	virtual void Uninit() {
	
		for (int i = 0; i < 3; i++) {

			for (GameObject* Object : m_GameObject[i])
			{
				Object->Uninit();
				delete Object;
			}

			m_GameObject[i].clear();
		}
	};

	virtual void Update() {
	
		for (int i = 0; i < 3; i++) {

			for (GameObject* Object : m_GameObject[i])
			{
				Object->Update();
			}

			m_GameObject[i].remove_if
			(
				[](GameObject* object)
				{return object->Destroy(); }
			);
		}
	};

	virtual void Draw() {
		for (int i = 0; i < 3; i++) {

			for (GameObject* Object : m_GameObject[i])
			{
				Object->Draw();
			}
		}
	}
};