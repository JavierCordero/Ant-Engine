#pragma once
#include "..\..\..\EngineCore\LogicEngine\Entity.h"
#include "..\..\..\EngineCore\EngineComponents\CollisionComponent.h"

class Ant;

class VisionCone : public Entity
{
public:
	VisionCone(glm::vec3 _position, double _baseRadious, float _height, glm::vec4 _color, Ant* _antReference);
	virtual ~VisionCone() {};
private:
	CollisionComponent* collision;
	Ant* antReference = nullptr;
protected:
	void Render(glm::dmat4 const& modelViewMat);
	void Update(double elapsedTime);
	void OnTriggerEnter(Object* _otherObject);

};

