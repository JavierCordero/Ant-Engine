#include "Food.h"
#include "MeshComponent.h"
#include "Cube.h"
#include "CollisionComponent.h"
#ifdef _DEBUG
#include "checkML.h"
#endif // _DEBUG
Food::Food(glm::vec3 _position, glm::vec3 _size, glm::vec3 _foodColor) : Entity(_position, _size) {

	MeshComponent* cube = new MeshComponent(new Cube(_size, _foodColor, this), this);
	entityComponents.push_back(cube);

	CollisionComponent* collision = new CollisionComponent(this, _position, _size);
	collisionLayer = 2;
	entityComponents.push_back(collision);

	//GetRandomDirection(dirX, dirY);
}

Food::~Food() {

}


