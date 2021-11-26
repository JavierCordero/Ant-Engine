#include "AntFarm.h"
#include "MeshComponent.h"
#include "Cube.h"
#include "WorkerAnt.h"
#include "WarriorAnt.h"
#include "PhysicLib.h"

#ifdef _DEBUG
#include "checkML.h"
#endif // _DEBUG
AntFarm::AntFarm(glm::vec3 _position, glm::vec3 _size, glm::vec4 _foodColor, glm::vec3 _textPosition) : antFarmColor(_foodColor), textPosition(_textPosition), Entity(_position, _size) {

	MeshComponent* cube = new MeshComponent(new Cube(glm::vec3(_size.x - 100, _size.y - 100, _size.z - 100), _foodColor, this), this);
	entityComponents.push_back(cube);

	CollisionComponent* collision = new CollisionComponent(this, _position, glm::vec3(_size.x - 100, _size.y - 100, _size.z - 100));
	collision->checkCollision = true;
	collision->isTrigger = true;
	entityComponents.push_back(collision);
	collisionLayer = (int)PhysicLayer::AntFarm;

}

void AntFarm::Init(Scene* _currentScene) {

	currentScene = _currentScene;

	farmTrail = new Trail(GetPosition(), glm::vec3(2.0f, 2.0f, 2.0f), glm::dvec4(0.0f, 0.0f, 0.0f, 1.0f));
	farmTrail->isVisible = false;
	farmTrail->strenght = 100;
	farmTrail->enabled = true;
	farmTrail->trailState = Ant::AntState::SEARCHING_FOOD;
	farmTrail->SetPosition(GetPosition());
	EngineCore::GetScene()->sceneObjects.push_back(farmTrail);

	for (int i = 0; i < 10; ++i) {
		CreateWorkerAnt();
	}
}

void AntFarm::Update(double timeElapsed)
{
	numWorkerAnts = workerAnts.size();
	numWarriorAnts = warriorAnts.size();
	Text3D text; text.position = glm::vec3(textPosition.x, textPosition.y, textPosition.z); text.color = antFarmColor; text.text = "Workers: " + std::to_string(numWorkerAnts) + " Warriors: " + std::to_string(numWarriorAnts) + " Killed: " + std::to_string(numKilledAnts);
	LogicLib::text3D.push_back(text);

	text.position = glm::vec3(textPosition.x, textPosition.y - 40.0f, textPosition.z); text.color = antFarmColor; text.text = "Food: " + std::to_string(numFood);
	LogicLib::text3D.push_back(text);

	if (numFood > 10) {

		if (rand() % 101 <= 20) {
			CreateWarriorAnt();
		}
		else {
			CreateWorkerAnt();
		}
		
		numFood -= 10;
	}
}

void AntFarm::CreateWarriorAnt() {
	Ant* c = new WarriorAnt(GetPosition(), glm::vec3(8.0f, 8.0f, 1.0f), antFarmColor, this);
	c->thisAntState = Ant::AntState::SEARCHING_FOOD;
	LogicLib::Spawn(c);
	warriorAnts.push_back(c);
}

void AntFarm::CreateWorkerAnt() {
	Ant* c = new WorkerAnt(GetPosition(), glm::vec3(4.0f, 4.0f, 1.0f), antFarmColor, this);
	c->thisAntState = Ant::AntState::SEARCHING_FOOD;
	LogicLib::Spawn(c);
	workerAnts.push_back(c);
}

void AntFarm::OnTriggerEnter(Object* _otherObject)
{
	Entity::OnTriggerEnter(_otherObject);

	Ant* ant = dynamic_cast<Ant*>(_otherObject);

	if (ant) {
		//LogicLib::Destroy(food);
		//Ojo, ahora también hay que comprobar que se dirige a nuestro hormiguero
		if (ant->antFarmReference == this && ant->thisAntState == Ant::AntState::MOVING_FOOD_TO_FARM) {
			numFood++;
			ant->thisAntState = Ant::AntState::SEARCHING_FOOD;
			//ant->meshComponent->GetMesh()->ChangeColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
			ant->knownPath = 0;
		}
	}

}

AntFarm::~AntFarm() {

}