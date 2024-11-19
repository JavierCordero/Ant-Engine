#include "SacredWorldScene.h"
#include "../Entities/Map/SacredMap.h"
#include "../../EngineCore/Texture/Sprite.h"
#include "../Sudoku/SudokuSolver.h"
#include "../../EngineCore/Interface/Interface.h"
#include <thread>
#include <iostream>

SacredWorldScene::SacredWorldScene()
	: Scene()
{
	m_SceneMap = new SacredMap();

	Sprite* sprite = new Sprite("sudokuBG.png", 900, 900, 0, 0, 0);
	GetSceneObjects().push_back(sprite);

	Interface* sudokuBGInterface = new Interface("test.png", 100, 100, 100, 200);
	GetInterfaceObjects().push_back(sudokuBGInterface);

	m_Sudoku = new Sudoku("sudoku.txt");
}

void SacredWorldScene::Update(float _elapsedTime)
{
	Scene::Update(_elapsedTime);

	m_currentTime -= _elapsedTime;

	m_Sudoku->PrintTable();
}

void SacredWorldScene::HandleInput(unsigned char _key)
{
	Scene::HandleInput(_key);

	switch (_key)
	{
	case 'y':
		m_Sudoku->SolveSudoku();
		break;
	default:
		break;
	}
}