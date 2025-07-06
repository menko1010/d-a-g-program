#include "main.h"
#include "manager.h"
#include "gameobject.h"
#include "input.h"
#include "renderer.h"
#include "result.h"
#include "title.h"
#include "resulttexture.h"

void Result::Init() {

	AddGameObject<ResultTexture>(2);//関数をテンプレートでまとめられる

}
void Result::Update()
{
	if (Input::GetKeyTrigger(VK_SPACE)) {
		Manager::SetScene<Title>();
	}
}
