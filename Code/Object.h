#pragma once

#include <GL/freeglut.h>
#include <glm.hpp>

class Object
{
public:
	Object(glm::vec3 _position, glm::vec3 _size) : modelMat(1.0), speed(glm::dvec3(0,0,0)), position(_position), prevPosition(_position), size(_size) {};
	virtual ~Object() {}

	inline float GetX() { return position.x; };
	inline float GetY() { return position.y; };
	inline float GetZ() { return position.z; };
	inline glm::vec3 GetPosition() { return position; }
	inline glm::vec3 GetPrevPosition() { return prevPosition; }
	inline glm::vec3 GetDirection() { return direction; }

	inline double GetWidth() { return size.x; }
	inline double GetHeight() { return size.y; }
	inline double GetDepth() { return size.z; }
	inline glm::vec3 GetSize() { return size; }

	inline void SetPosition(glm::vec3 _vector) { position.x = _vector.x; position.y = _vector.y; position.z = _vector.z;}
	inline void SetPrevPosition(glm::vec3 _vector) { prevPosition.x = _vector.r; prevPosition.y = _vector.g; prevPosition .z = _vector.b; }
	inline void SetX(float _x) { position.x = _x; }
	inline void SetY(float _y) { position.y = _y; }
	inline void SetZ(float _z) { position.z = _z; }

	inline void SetDirection(glm::vec3 _direction) { direction = _direction; };

	void SetModelMat(glm::dmat4 const& mMat) { modelMat = mMat; }

	void Update(double elapsedTime);
	void PostUpdate(double elapsedTime);

	virtual void OnCollision(Object* _otherObject) {};
	virtual void OnTriggerEnter(Object* _otherObject) {};

	glm::vec3 speed;

	bool canMove = true;

	int collisionLayer = 0;

	bool markedForDestroy = false;

protected:
	glm::dmat4 modelMat;
	void SetModelViewMat(glm::dmat4 const& modelViewMat);

private: 
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 prevPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 size = glm::vec3(0.0f, 0.0f, 0.0f);	
};

