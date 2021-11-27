#include "Wall.h"
#include "..\..\..\EngineCore\EngineComponents\CollisionComponent.h"
#include "..\..\..\EngineCore\EngineComponents\MeshComponent.h"
#include "..\..\..\EngineCore\PhysicEngine\PhysicLib.h"

#ifdef _DEBUG
#include "..\..\..\EngineCore\checkML.h"
#endif // _DEBUG

Wall::Wall(glm::vec3 _position, glm::vec3 _size, glm::vec3 _color) : Entity(_position, _size)
{
	//meshes.push_back(new Cube(_x, _y, _z, _width));
	entityComponents.push_back(new CollisionComponent(this, _position,_size, false));
	//entityComponents.push_back(new MeshComponent(new Cube(_size, _color, this), this));
	Mesh* m = new Mesh(this);
	m->LoadObjFile("../../resources/models/Cube.obj");
	entityComponents.push_back(new MeshComponent(new Mesh(this), this));
	collisionLayer = (int)PhysicLayer::Static;
}

Wall::~Wall() {
	//Entity::~Entity();
}