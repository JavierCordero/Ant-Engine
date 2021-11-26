#pragma once

#include "..\..\..\EngineCore\LogicEngine\Entity.h"
#include "..\..\Scenes\Scene.h"
#include "..\Ants\Ant.h"
#include "..\..\..\EngineCore\LogicEngine\Object.h"
#include "..\Ants\Trail.h"

class AntFarm : public Entity
{
public:
	AntFarm(glm::vec3 _position, glm::vec3 _size, glm::vec4 _antColor, glm::vec3 _textPosition);
	virtual ~AntFarm();

	void Init(Scene* _currentScene);
	void Update(double timeElapsed);
	//void PostUpdate(double timeElapsed);

	void OnTriggerEnter(Object* _otherObject);

	std::vector<Ant*> workerAnts;
	std::vector<Ant*> warriorAnts;

	uint16_t numFood = 0;
	uint16_t numWorkerAnts = 0;
	uint16_t numWarriorAnts = 0;
	uint16_t numKilledAnts = 0;


	Trail* farmTrail = nullptr;

private:
	void CreateWorkerAnt();
	void CreateWarriorAnt();

	Scene* currentScene = nullptr;

	int numAntsToCreate = 0;

	glm::vec3 textPosition;

	glm::vec4 antFarmColor;

};

