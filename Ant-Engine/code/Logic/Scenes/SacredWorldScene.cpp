#include "SacredWorldScene.h"
#include "../Entities/Map/SacredMap.h"

SacredWorldScene::SacredWorldScene()
	: Scene()
{
	m_SceneMap = new SacredMap();
}