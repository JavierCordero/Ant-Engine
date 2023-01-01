#pragma once

#include <freeglut.h>
#include <glm.hpp>

class Object
{
public:
	Object(glm::vec3 _position, glm::vec3 _scale) : m_ModelMat(1.0), m_ObjectSpeed(glm::dvec3(0,0,0)), m_Position(_position), m_PrevPosition(_position), m_Scale(_scale) {};
	virtual ~Object() {}

	inline float GetX() { return m_Position.x; };
	inline float GetY() { return m_Position.y; };
	inline float GetZ() { return m_Position.z; };
	inline glm::vec3 GetPosition() { return m_Position; }
	inline glm::vec3 GetPrevPosition() { return m_PrevPosition; }
	inline glm::vec3 GetDirection() { return m_Direction; }

	inline double GetWidth() { return m_Scale.x; }
	inline double GetHeight() { return m_Scale.y; }
	inline double GetDepth() { return m_Scale.z; }
	inline glm::vec3 GetSize() { return m_Scale; }

	inline void SetPosition(glm::vec3 _vector) { m_Position.x = _vector.x; m_Position.y = _vector.y; m_Position.z = _vector.z;}
	inline void SetPrevPosition(glm::vec3 _vector) { m_PrevPosition.x = _vector.r; m_PrevPosition.y = _vector.g; m_PrevPosition.z = _vector.b; }
	inline void SetX(float _x) { m_Position.x = _x; }
	inline void SetY(float _y) { m_Position.y = _y; }
	inline void SetZ(float _z) { m_Position.z = _z; }

	inline void SetDirection(glm::vec3 _direction) { m_Direction = _direction; };

	void SetModelMat(glm::dmat4 const& mMat) { m_ModelMat = mMat; }

	void Update(double elapsedTime);
	void PostUpdate(double elapsedTime);

	virtual void OnCollision(Object* _otherObject) {};
	virtual void OnTriggerEnter(Object* _otherObject) {};

	glm::vec3 GetObjectSpeed() { return m_ObjectSpeed; };
	void SetObjectSpeed(glm::vec3 _objectSpeed) { m_ObjectSpeed = _objectSpeed; };

	bool GetObjectCanMove() { return m_ObjectCanMove; };
	void SetObjectCanMove(bool _objectCanMove) { m_ObjectCanMove = _objectCanMove; };

	int GetObjectCollisionLayer() { return m_ObjectCollisionLayer; }
	void SetObjectCollisionLayer(int _newCollisionLayer) { m_ObjectCollisionLayer = _newCollisionLayer; };

	bool IsObjectMarkedForDestroy() { return m_ObectMarkedForDestroy; };
	void MarkObjectForDestroy() { m_ObectMarkedForDestroy = true; };

protected:
	glm::dmat4 m_ModelMat;
	void SetModelViewMat(glm::dmat4 const& modelViewMat);

private: 

	int m_ObjectCollisionLayer = 0;
	bool m_ObjectCanMove = true;

	glm::vec3 m_ObjectSpeed;
	glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_PrevPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_Direction = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 m_Scale = glm::vec3(0.0f, 0.0f, 0.0f);	

	bool m_ObectMarkedForDestroy = false;
};

