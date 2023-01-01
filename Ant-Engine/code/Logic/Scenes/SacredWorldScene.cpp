#include "SacredWorldScene.h"
#include "../Entities/Map/SacredMap.h"
#include "../../EngineCore/Texture/Texture.h"
#include "../../EngineCore/Texture/Sprite.h"
#include <iostream>

SacredWorldScene::SacredWorldScene()
	: Scene()
{
	m_SceneMap = new SacredMap();

	Sprite* sprite = new Sprite("test.png", 512, 512, 0, 0);
	GetSceneObjects().push_back(sprite);
}