#pragma once
#include <vector>
#include "..\LogicEngine\Object.h"
#include "..\EngineComponents\CollisionComponent.h"
#include "Quad.h"

static enum class PhysicLayer { Static = 0, WorkerAnts = 1, WarriorAnts = 2, AntFarm = 3};

static class PhysicLib
{
public:
	static bool CheckCollision(CollisionComponent * _objectToCheck);

	static std::vector<CollisionComponent*> colliders;

	static void Init();
	static void Destroy();

	static Quad* quadTree;

private: 
	static bool FinalCheck(CollisionComponent* _collider, CollisionComponent* _objectToCheck);
};

