#include "main.h"
#include "manager.h"
#include "gameobject.h"
#include "input.h"
#include "renderer.h"
#include "clear.h"
#include "title.h"
#include "cleartexture.h"

void Clear::Init() {

	AddGameObject<ClearTexture>(2);//関数をテンプレートでまとめられる

}
void Clear::Update()
{
	if (Input::GetKeyTrigger(VK_SPACE)) {
		Manager::SetScene<Title>();
	}
}
