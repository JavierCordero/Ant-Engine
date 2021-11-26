#include "MathLib.h"

#ifdef _DEBUG
#include "..\checkML.h"
#endif // _DEBUG

glm::vec3 MathLib::ClampMagnitude(glm::vec3 _vector, float magnitude) {

	glm::vec3 norm = glm::normalize(_vector);
	glm::vec3 minimun = glm::min(norm, magnitude);

	float auxX = 0, auxY = 0, auxZ = 0;

	if (minimun.x != 0) {
		auxX = minimun.x / norm.x;
	}

	if (minimun.y != 0) {
		auxY = minimun.y / norm.y;
	}

	if (minimun.z != 0) {
		auxZ = minimun.z / norm.z;
	}

	glm::vec3 normalizedResult = glm::vec3(auxX, auxY, auxZ);

	return _vector * normalizedResult;
}

glm::vec3 MathLib::RandomVectorInsideSphere(float _radious)
{
	float r = _radious * sqrt((float)rand() / (RAND_MAX));
	float theta = (float)rand() / (RAND_MAX) * 2 * PI;
	float phi = (float)rand() / (RAND_MAX) * PI;

	float x = r * sin(phi) * cos(theta);
	float y = r * sin(phi)* sin(theta);
	float z = r * cos(phi);

	return glm::vec3(x, y, z);
}

bool MathLib::IsPointInsideCone(glm::vec3 _conePosition, glm::vec3 _forwardVector, float _height, float _baseRadious, glm::vec3 _point)
{
	float coneDistance = glm::dot(_point - _conePosition, _forwardVector);
	float coneDistanceB = glm::length(_point - _conePosition);

	//float heightDistance = glm::distance(_point, _forwardVector * _height);

	//if ( heightDistance > coneDistance || heightDistance <= 0)
	//{
	//	return false;
	//}

	if (coneDistanceB > _height)
	{
		return false;
	}

	float radious = (coneDistance / _height) * _baseRadious;

	float orthDistance = glm::length((_point - _conePosition) - coneDistance * _forwardVector);

	return orthDistance < radious;
}
