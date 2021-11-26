#include "Map.h"
#include "Wall.h"

#ifdef _DEBUG
#include "checkML.h"
#endif // _DEBUG

Map::Map(Scene* _mainScene) : mainScene(_mainScene) {

}

Map::~Map() {
	//int arrayX = 0;
	//int arrayY = 0;

	//for (int i = -50; i < 50; ++i) {
	//	for (int j = -50; j < 50; ++j) {
	//		if (antHomeWalls[arrayX][arrayY] != nullptr) {
	//			delete antHomeWalls[arrayX][arrayY];
	//			antHomeWalls[arrayX][arrayY] = nullptr;
	//		}
	//		arrayY++;
	//	}
	//	arrayY = 0;
	//	++arrayX;
	//}
}

void Map::InitNormalMap() {

	mainScene->sceneObjects.push_back(new Wall(glm::vec3(-5,-5, -15), glm::vec3(1000,1000,10), glm::vec3(73.0f / 255.0f, 58.0f / 255.0f, 54.0f / 255.0f)));

	int arrayX = 0;
	int arrayY = 0;
	for (int i = -50; i < 50; ++i) {
		for (int j = -50; j < 50; ++j) {

			if (i == -50 || i == 49 || j == 49 || j == -50) {
				antHomeWalls[arrayX][arrayY] = new Wall(glm::vec3(i * 10.0f, j * 10.0f, 0.0f), glm::vec3(10.0, 10.0, 10.0));
				mainScene->sceneObjects.push_back(antHomeWalls[arrayX][arrayY]);
			}

			/*else if (rand() % 100 + 1 <= 10) {

				antHomeWalls[arrayX][arrayY] = new Wall(glm::vec3(i * 10.f, j * 10.f, 0.0), glm::vec3(10.0, 10.0, 10.0));
				mainScene->sceneObjects.push_back(antHomeWalls[arrayX][arrayY]);
			}

			else {
				antHomeWalls[arrayX][arrayY] = nullptr;
			}*/

			++arrayY;
		}
		arrayY = 0;
		++arrayX;
	}
}

void Map::InitLifeGenerationMap() {

	InitNormalMap();

	int arrayX = 0;
	int arrayY = 0;

	for (int i = -50; i < 50; ++i) {
		for (int j = -50; j < 50; ++j) {
			if (i != -50 && i != 49 && j != 49 && j != -50) {

				int aliveNeighbours = 0;
				if (antHomeWalls[arrayX + 1][arrayY]) aliveNeighbours++;
				if (antHomeWalls[arrayX - 1][arrayY]) aliveNeighbours++;
				if (antHomeWalls[arrayX][arrayY + 1]) aliveNeighbours++;
				if (antHomeWalls[arrayX][arrayY - 1]) aliveNeighbours++;
				if (antHomeWalls[arrayX + 1][arrayY + 1]) aliveNeighbours++;
				if (antHomeWalls[arrayX - 1][arrayY - 1]) aliveNeighbours++;
				if (antHomeWalls[arrayX - 1][arrayY + 1]) aliveNeighbours++;
				if (antHomeWalls[arrayX + 1][arrayY - 1]) aliveNeighbours++;

				if (antHomeWalls[arrayX][arrayY] != nullptr)
				{
					if (aliveNeighbours > 3 || aliveNeighbours < 2) {
						//auto it = std::find(mainScene->sceneObjects.begin(), mainScene->sceneObjects.end(), antHomeWalls[arrayX][arrayY]);

						//if (it != mainScene->sceneObjects.end()) {
						//	int index = it - mainScene->sceneObjects.begin();
						//	mainScene->sceneObjects.erase(mainScene->sceneObjects.begin() + index);
						antHomeWalls[arrayX][arrayY]->Destroy();
						delete antHomeWalls[arrayX][arrayY];
						antHomeWalls[arrayX][arrayY] = nullptr;
						//}
					}
				}

				else {
					if (aliveNeighbours == 3) {
						antHomeWalls[arrayX][arrayY] = new Wall(glm::vec3(i * 10.0f, j * 10.0f, 0.0), glm::vec3(10.0, 10.0, 10.0));
						mainScene->sceneObjects.push_back(antHomeWalls[arrayX][arrayY]);
					}
				}

			}
			++arrayY;
		}
		arrayY = 0;
		++arrayX;
	}
}