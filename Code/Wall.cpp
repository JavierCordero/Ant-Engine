#include "Wall.h"
#include "CollisionComponent.h"
#include "MeshComponent.h"
#include "PhysicLib.h"

#ifdef _DEBUG
#include "checkML.h"
#endif // _DEBUG
Wall::Wall(glm::vec3 _position, glm::vec3 _size, glm::vec3 _color) : Entity(_position, _size)
{
	//meshes.push_back(new Cube(_x, _y, _z, _width));
	entityComponents.push_back(new CollisionComponent(this, _position,_size, false));
	entityComponents.push_back(new MeshComponent(new Cube(_size, _color, this), this));
	collisionLayer = (int)PhysicLayer::Static;
}

Wall::~Wall() {
	//Entity::~Entity();
}