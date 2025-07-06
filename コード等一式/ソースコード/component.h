#pragma once
class Component {
protected:

	class GameObject* m_Gamebject = nullptr;
	class Scene* m_Scene = nullptr;
	class Collision* m_Collision = nullptr;

public:
	Component() {}
	Component(GameObject* Object) { m_Gamebject = Object; }
	Component(Scene* scene) { m_Scene = scene; }
	Component(Collision* collision) { m_Collision = collision; }

	virtual ~Component() {};


	virtual void Init(){};//âºëzä÷êî
	virtual void Uninit(){};
	virtual void Update(){};
	virtual void Draw(){};

};